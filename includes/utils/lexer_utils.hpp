
/******************************************************************************/
//
//  Source Name:                lexer_utils.hpp
//
//  Description:                This file contains a number of type
//                              definitions and helper functions for
//                              the lexer to leverage.
//
//  Dependencies:               None
//
//  Classes:                    Token_T
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       is_alpha
//                              is_num
//                              is_alphanum
//                              is_whitespace
//                              is_op
//                              is_delimiter
//                              is_ctrl_struct
//                              
/******************************************************************************/

#ifndef LEXER_UTILS
#define LEXER_UTILS

/******************************************************************************/

#include <string>                       // std::string
#include <vector>                       // std::vector

/******************************************************************************/

// This enum defines the types of different tokens the
// lexer can form.
enum TOKEN_TYPE {

    // Generic
    TOKEN_SYMBOL,
    TOKEN_OP_BIN,       // binary operator
    TOKEN_DELIM,        // delimiter

    // Literals
    TOKEN_LIT_INT,
    TOKEN_LIT_FLOAT,
    TOKEN_LIT_STRING,

    // Control Structure
    TOKEN_CTRL,

    // Keywords
    TOKEN_KW,

};

/******************************************************************************/

// This defines the associated token strings for debug reporting.
static std::vector<std::string> TOKEN_STRINGS = {

    // Generic
    "SYMB",
    "OP BI",
    "DELIM",

    // Literals
    "INT",
    "FLOAT",
    "STRIN",

    // Control Structure
    "CTRL",

    // Keywords
    "KEYW",

};

/******************************************************************************/

// This struct defines the token class. It contains the
// raw token itself, along with metadata.
struct Token_T {

    std::string _token;
    TOKEN_TYPE _type;

    // The position within the source file this token occurs in.
    size_t _colnum;
    size_t _linenum;

    // Ctor.
    Token_T(const std::string& __token,
            TOKEN_TYPE __type,
            size_t __colnum, size_t __linenum)
        : _token(__token), _type(__type),
        _colnum(__colnum), _linenum(__linenum) {}

};

/******************************************************************************/

// lexer utility macros.
#define SPACE 32
#define HORIZTAB 9
#define VERTTAB 11
#define NEWLINE 10
#define COMMENT 35  // '#'

/******************************************************************************/

// This section contains various utility functions for the lexer.
// All utility functions must be non-throwing.

inline bool is_alpha(char c) noexcept {
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           (c == '_');
}

inline bool is_num(char c) noexcept {
    return (c >= '0' && c <= '9');
}

inline bool is_alphanum(char c) noexcept {
    return is_alpha(c) || is_num(c);
}

inline bool is_whitespace(char c) noexcept {
    return (int(c) == SPACE) || 
           (int(c) == HORIZTAB) ||
           (int(c) == VERTTAB) ||
           (int(c) == NEWLINE);
}

inline bool is_op(char c) noexcept {
    std::string op_string = "+*=";
    for (auto& op : op_string) {
        if (c == op) { return true; }
    }
    return false;
}

inline bool is_delimiter(char c) noexcept {
    return (c == ';');
}

inline bool is_ctrl_struct(char c) noexcept {
    return (c == '(') || (c == ')');
}

/******************************************************************************/

#endif // LEXER_UTILS
