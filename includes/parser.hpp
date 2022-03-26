
/******************************************************************************/
//
//  Source Name:                parser.hpp
//
//  Description:                This file is responsible for parsing a
//                              token table that is generated by the
//                              lexer. Parsing decisions are made
//                              in the main 'parse' function and subsequent
//                              parsing is handled in specific parse functions
//                              pertaining to the tokens needing to be parsed.
// 
//                              The parser will catch logical as well as
//                              syntactical errors.
//
//                              This file also owns the static instance
//                              of the variable handler backend.
//
//  Dependencies:               lexer_utils.hpp
//                              parser_utils.hpp
//                              error_handler.hpp
//                              evaluator.hpp
//                              variable_handler.hpp
//                              rosky_interface.hpp
//
//  Classes:                    None
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       parse
//                              parse_expr
//                              
/******************************************************************************/

#ifndef TOKEN_PARSER
#define TOKEN_PARSER

/******************************************************************************/

#include <deque>                        // std::deque
#include <memory>                       // std::shared_ptr, std::unique_ptr

#include "utils/lexer_utils.hpp"
#include "utils/parser_utils.hpp"

#include "error_handler.hpp"
#include "evaluator.hpp"
#include "variable_handler.hpp"

#include "objects/rosky_interface.hpp"

/******************************************************************************/

// Create a static instance of the variable handler.
static VariableTable_T var_table;

/******************************************************************************/

// This function is the main 'brain' of the parser. It will look through
// a provided token table and dispatch specialized parse functions based on
// the tokens it encounters.
void parse(const std::deque<std::shared_ptr<Token_T>>& __tokens,
            size_t __start_idx, size_t __end_idx = 0);

/******************************************************************************/

// This function is for parsing expressions. It forms the tokens into
// an expression tree, and upon success feeds the tree into the evaluator
// to get the result.
extern std::shared_ptr<RoskyInterface>
    parse_expr(const std::deque<std::shared_ptr<Token_T>>& __tokens,
               size_t& __idx, size_t __end_idx);

/******************************************************************************/

#endif // TOKEN_PARSER
