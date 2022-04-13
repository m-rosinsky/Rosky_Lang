
/******************************************************************************/
//
//  Source Name:                evaluator.hpp
//
//  Description:                This file is responsible for evaluating
//                              a parse tree generated by the parser and
//                              returning the resulting object.
//
//  Dependencies:               parser_utils.hpp
//                              lexer_utils.hpp
//                              error_handler.hpp
//                              variable_handler.hpp
//                              rosky_interface.hpp
//
//  Classes:                    None
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       evaluate
//                              
/******************************************************************************/

#ifndef TREE_EVALUATOR
#define TREE_EVALUATOR

/******************************************************************************/

#include <memory>                       // std::shared_ptr
#include <utility>                      // std::pair

#include "utils/parser_utils.hpp"
#include "utils/lexer_utils.hpp"

#include "error_handler.hpp"
#include "variable_handler.hpp"

#include "objects/rosky_interface.hpp"
#include "objects/rosky_pointer.hpp"
#include "objects/rosky_null.hpp"

/******************************************************************************/

// This function evaluates a parse tree and returns the resulting object.
// The parse tree is expected to be correctly formatted, so any errors in
// evaluation fall on the parser.
// The __top indicates if this is the top level evaluation in the
// recursion stack. Recursive calls will set this to false.
std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    evaluate(const std::shared_ptr<ParseNode>& __root,
             std::unique_ptr<VariableTable_T>& __var_table,
             bool __top,
             size_t __scope, size_t __r_index);

/******************************************************************************/

#endif // TREE_EVALUATOR
