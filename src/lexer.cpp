
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
//                              lexer_utils.hpp
//                              <parser>
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

void tokenize_src(const std::unique_ptr<Src_T>& __src) {

    // Create a deque to hold the token table.
    std::deque<std::unique_ptr<Token_T>> tokens;

    // Temporary string to hold each token.
    std::string token;

    // Index to iterate through input.
    size_t idx = 0;

    // This keeps track of the line number and column
    // number in the source.
    size_t colnum = 1;
    size_t linenum = 1;

    // Iterate through input src.
    while (idx < __src->_data.size()) {

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
            tokens.push_back(std::make_unique<Token_T>
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
            tokens.push_back(std::make_unique<Token_T>
                (token, TOKEN_OP, colnum, linenum));

            // Reset the token and continue.
            token = "";
            idx++;
            colnum++;
            continue;

        }

        // Number
        if (is_num(__src->_data[idx])) {

            // Bookmark the start column number of the number.
            size_t start_col = colnum;

            // Collect all numbers in sequence.
            while (is_num(__src->_data[idx])) {
                token += __src->_data[idx++];
                colnum++;
            }

            // Push the token into the table.
            tokens.push_back(std::make_unique<Token_T>
                (token, TOKEN_LITERAL, start_col, linenum));

            // Reset the token and continue.
            token = "";
            continue;

        }

        // Anything else is considered unexpected.
        token += __src->_data[idx];

        // Throw error (exiting program).
        throw_error(ERR_UNEXP_TOKEN, token, colnum, linenum);

    }

    // Send the token table to the parser.
    for (auto& tok : tokens) {
        std::cout << tok->_token << "\t| " << TOKEN_STRINGS[tok->_type] << "\t| " << tok->_linenum << " " << tok->_colnum << std::endl;
    }
    return;

}

/******************************************************************************/