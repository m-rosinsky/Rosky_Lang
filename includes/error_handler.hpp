
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
    ERR_UNCLOSED_QUOTE,
    ERR_INVALID_ESC_CHAR,

    // Parser errors.
    ERR_SYNTAX,
    ERR_UNEXP_EOF,
    ERR_UNCLOSED_BRACE,
    ERR_UNCLOSED_BRACKET,
    ERR_UNCLOSED_PAREN,
    ERR_TERM_BEFORE_CLOSURE,
    ERR_EMPTY_PARENS,
    ERR_RESERVED_USE,
    ERR_MISSING_BODY,
    ERR_MISSING_COND,
    ERR_BAD_COND_TYPE,

    // Evaluator errors.
    ERR_UNREC_SYM,
    ERR_OP_INCOMPAT,
    ERR_UNEXP_OP,
    ERR_ADDR_TEMP,
    ERR_BAD_ASSIGN,
    ERR_DEREF_NULLPTR,
    ERR_NON_ITERABLE,
    ERR_INDEX_OOB,

    // Function errors.
    ERR_BAD_FUNC_ARGS,
    ERR_EMPTY_ARG,
    ERR_NONMEMBER,
    ERR_UNREC_FUNC,
    ERR_NO_FUNC_ARGS,
    ERR_ASSERT,

};

/******************************************************************************/

// This vector contains the associated error message with each error
// type.
static std::vector<std::string> ERROR_STRINGS {
    
    // Lexer errors.
    "Unexpected token",
    "Unclosed quote",
    "Invalid escape character",

    // Parser errors.
    "Syntax error",
    "Missing terminator (possible missing semicolon)",
    "Unclosed curly brace",
    "Unclosed square bracket",
    "Unclosed parentheses",
    "Expression terminated before closure",
    "Empty parentheses",
    "Bad use of reserved keyword",
    "Missing statement body",
    "Expected condition before body",
    "Expected a boolean condition",

    // Evaluator errors.
    "Unrecognized symbol",
    "Operator incompatible",
    "Unexpected operator",
    "Attempt to get address of temporary",
    "Attempt to assign to r-value",
    "Attempt to dereference a nullptr",
    "Attempt to index a non-iterable object",
    "Index out of bounds",

    // Function errors.
    "Improper function arguments",
    "Empty argument",
    "Member function error",
    "Unrecognized function",
    "Expected arguments for function",
    "Assertion error",

};

/******************************************************************************/

// This function determines if the provided error type will have
// an error message surrounded in quotes.
inline bool err_has_quotes(ERROR_TYPE __err) noexcept {

    return (__err == ERR_SYNTAX) || (__err == ERR_UNREC_SYM) ||
           (__err == ERR_UNEXP_TOKEN) || (__err == ERR_INVALID_ESC_CHAR);

}

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
        if (err_has_quotes(__err)) {
            std::cerr << ": '" << __msg << "'";
        } else {
            std::cerr << ": " << __msg;
        }
    }
    std::cerr << std::endl << "Exiting..." << std::endl;

    // Exit with error status.
    exit(1);

}

/******************************************************************************/

#endif // ERROR_HANDLER
