
/******************************************************************************/
//
//  Source Name:                error_handler.hpp
//
//  Description:                This file is responsible for throwing
//                              errors. It reports the errors as well
//                              as the column and line number that the
//                              error occured on, and then terminates
//                              the program with error status.
//
//  Dependencies:               None
//
//  Classes:                    None
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       throw_error
//                              
/******************************************************************************/

#ifndef ERROR_HANDLER
#define ERROR_HANDLER

/******************************************************************************/

#include <vector>                       // std::vector
#include <string>                       // std::string
#include <iostream>                     // std::cerr

/******************************************************************************/

// This enum contains the types of errors that can be thrown.
enum ERROR_TYPE {

    // Lexer errors.
    ERR_UNEXP_TOKEN,

    // Parser errors.
    ERR_SYNTAX,
    ERR_UNEXP_EOF,
    ERR_UNCLOSED_BRACE,
    ERR_UNCLOSED_PAREN,
    ERR_EMPTY_PARENS,
    ERR_RESERVED_USE,

    // Evaluator errors.
    ERR_UNREC_SYM,
    ERR_OP_INCOMPAT,
    ERR_UNEXP_OP,
    ERR_ADDR_TEMP,
    ERR_BAD_ASSIGN,
    ERR_DEREF_NULLPTR,

    // Function errors.
    ERR_BAD_FUNC_ARGS,
    ERR_EMPTY_ARG,

};

/******************************************************************************/

// This vector contains the associated error message with each error
// type.
static std::vector<std::string> ERROR_STRINGS {
    
    // Lexer errors.
    "Unexpected token",

    // Parser errors.
    "Syntax error",
    "Unexpected EOF while parsing (possible missing semicolon)",
    "Unclosed curly brace",
    "Unclosed parentheses",
    "Empty parentheses",
    "Bad use of reserved keyword",

    // Evaluator errors.
    "Unrecognized symbol",
    "Operator incompatible",
    "Unexpected operator",
    "Attempt to get address of temporary",
    "Attempt to assign to r-value",
    "Attempt to dereference a nullptr",

    // Function errors.
    "Improper function arguments",
    "Empty argument",

};

/******************************************************************************/

// This function takes in an error type, additional message, and source
// position and throws an error to stderr.
// This terminates program execution.
inline void throw_error(ERROR_TYPE __err, const std::string& __msg,
                        size_t __colnum, size_t __linenum) {

    // Report the error.
    std::cerr << "Error [Line "<< __linenum << " Column " << __colnum << "]: ";
    std::cerr << ERROR_STRINGS[__err];
    if (__msg.size() > 0) {
        std::cerr << ": '" << __msg << "'";
    }
    std::cerr << std::endl << "Exiting..." << std::endl;

    // Exit with error status.
    exit(1);

}

/******************************************************************************/

#endif // ERROR_HANDLER
