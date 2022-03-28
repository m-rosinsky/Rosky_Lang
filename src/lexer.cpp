
/******************************************************************************/
//
//  Source Name:                lexer.cpp
//
//  Description:                This file is responsible for "tokenizing"
//                              a provided source file. Tokens are store
//                              in a table (std::deque) with each entry
//                              containing certain metadata.
//
//                              Specific lexer errors such as unrecognized
//                              or unexpected tokens can be caught and thrown
//                              here, but the lexer is not responsible for
//                              making logical or syntactic sense of the
//                              source.
//
//                              After the table is created, it will be
//                              fed into the parser.
//
//  Dependencies:               source_handler.hpp
//                              error_handler.hpp
//                              parser.hpp
//                              lexer_utils.hpp
//
//  Classes:                    None
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       tokenize_src
//                              
/******************************************************************************/

#include "../includes/lexer.hpp"

// ***DEBUG***
#include <iostream>
// ***DEBUG***

/******************************************************************************/

void tokenize_src(std::unique_ptr<Src_T>& __src) {

    // Create a deque to hold the token table.
    std::deque<std::shared_ptr<Token_T>> tokens;

    // Temporary string to hold each token.
    std::string token;

    // Index to iterate through input.
    size_t idx = 0;

    // This keeps track of the line number and column
    // number in the source.
    size_t colnum = 1;
    size_t linenum = 1;

    // Flag to indicate if we are in a comment block.
    bool in_comment = false;

    // Iterate through input src.
    while (idx < __src->_data.size()) {

        // If in comment, ignore until new line.
        if (in_comment) {
            colnum++;
            if (__src->_data[idx] == NEWLINE) {
                linenum++;
                colnum = 1;
                in_comment = false;
            }
            idx++;
            continue;
        }

        // Comment character '#'
        if (__src->_data[idx] == COMMENT) {
            in_comment = true;
            colnum++;
            idx++;
            continue;
        }

        // Ignore whitespace.
        if (is_whitespace(__src->_data[idx])) {
            colnum++;
            if (__src->_data[idx] == NEWLINE) {
                linenum++;
                colnum = 1;
            }
            idx++;
            continue;
        }

        // Delimiters.
        if (is_delimiter(__src->_data[idx])) {
            token += __src->_data[idx];

            // Add the delimiter to the token table.
            tokens.push_back(std::make_shared<Token_T>
                (token, TOKEN_DELIM, colnum, linenum));

            // Reset the token and continue.
            token = "";
            idx++;
            colnum++;
            continue;
        }

        // Operator
        if (is_op(__src->_data[idx])) {

            // Add the operator to the current token.
            token += __src->_data[idx];

            // Push the token into the table.
            tokens.push_back(std::make_shared<Token_T>
                (token, TOKEN_OP, colnum, linenum));

            // Reset the token and continue.
            token = "";
            idx++;
            colnum++;
            continue;

        }

        // Control Structures
        if (is_ctrl_struct(__src->_data[idx])) {

            // Add the operator to the current token.
            token += __src->_data[idx];

            // Push the token into the table.
            tokens.push_back(std::make_shared<Token_T>
                (token, TOKEN_CTRL, colnum, linenum));

            // Reset the token and continue.
            token = "";
            idx++;
            colnum++;
            continue;

        }

        // Number
        if (is_num(__src->_data[idx])) {

            // Bookmark the start column number of the token.
            size_t start_col = colnum;

            // This flag holds whether the number is an integer
            // or float
            bool is_int = true;

            // Collect all numbers in sequence (including '.')
            while (is_num(__src->_data[idx]) ||
                   (__src->_data[idx] == '.')) {

                // If we collect a '.', set the flag.
                // If the flag is already set, throw an error.
                if (__src->_data[idx] == '.') {
                    
                    if (is_int == false) {
                        token += '.';
                        throw_error(ERR_UNEXP_TOKEN, token, colnum, linenum);
                    }
                    is_int = false;

                }

                token += __src->_data[idx++];
                colnum++;
            }

            // If the last character in the token is a decimal,
            // throw an error.
            if (token[token.size()-1] == '.') {
                throw_error(ERR_UNEXP_TOKEN, token, colnum, linenum);
            }

            // Determine the token type based on the flag.
            TOKEN_TYPE t = is_int ? TOKEN_LIT_INT : TOKEN_LIT_FLOAT;

            // Push the token into the table.
            tokens.push_back(std::make_shared<Token_T>
                             (token, t, start_col, linenum));

            // Reset the token and continue.
            token = "";
            continue;

        }

        // Alphanumeric
        if (is_alpha(__src->_data[idx])) {

            // Bookmark the start column number of the token.
            size_t start_col = colnum;

            // Collect all the alphanumeric characters in sequence.
            while (is_alphanum(__src->_data[idx])) {
                token += __src->_data[idx++];
                colnum++;
            }

            // Determine a token type based on if the token
            // is a keyword.
            TOKEN_TYPE t = is_keyword(token) ? TOKEN_KW : TOKEN_SYMBOL;

            // Push the token into the table.
            tokens.push_back(std::make_shared<Token_T>
                             (token, t, start_col, linenum));

            // Reset the token and continue.
            token = "";
            continue;

        }

        // Anything else is considered unexpected.
        token += __src->_data[idx];

        // Throw error (exiting program).
        throw_error(ERR_UNEXP_TOKEN, token, colnum, linenum);

    }

    // ***DEBUG***
    // std::cout << "TOKEN:\t| TYPE:\t| LINE:\t| COL:" << std::endl;
    // for (auto& tok : tokens) {
    //     std::cout << tok->_token << "\t| " << TOKEN_STRINGS[tok->_type] << "\t| " << tok->_linenum << "\t| " << tok->_colnum << std::endl;
    // }
    // ***DEBUG***

    // Now that tokenizing is completed, we can unload the raw
    // source to save memory.
    __src->clean();

    // Instantiate the parser object.
    Parser_T main_parser(tokens);

    // Send the token table to the parser.
    // Start index -> 0
    // end index -> tokens.size()
    // scope -> 0
    main_parser.parse(0, tokens.size(), 0);

}

/******************************************************************************/
