
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
//                              This file also owns the instance
//                              of the variable handler backend.
//
//  Dependencies:               lexer_utils.hpp
//                              parser_utils.hpp
//                              error_handler.hpp
//                              evaluator.hpp
//                              variable_handler.hpp
//                              function_handler.hpp
//                              rosky_interface.hpp
//
//  Classes:                    Parser_T
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       Ctor.
//                              parse
//                              parse_expr
//                              
/******************************************************************************/

#ifndef TOKEN_PARSER
#define TOKEN_PARSER

/******************************************************************************/

#include <deque>                        // std::deque
#include <memory>                       // std::shared_ptr, std::unique_ptr
#include <utility>                      // std::pair
#include <vector>                       // std::vector

#include "utils/lexer_utils.hpp"
#include "utils/parser_utils.hpp"

#include "error_handler.hpp"
#include "evaluator.hpp"
#include "variable_handler.hpp"
#include "function_handler.hpp"

#include "objects/rosky_interface.hpp"

/******************************************************************************/

// This class provides the definition for the parser object. It holds
// instances the different components it needs to reference so that the
// instances don't need to be passed to each seperate function of the
// parser.
class Parser_T {

private:

    // The token table object.
    std::deque<std::shared_ptr<Token_T>> _tokens;

    // The variable table handler instance.
    std::unique_ptr<VariableTable_T> _var_table;

    // The function table handler instance.
    std::unique_ptr<FunctionTable_T> _func_table;

    // This flag defines whether we are currently in a loop.
    bool _loop_flag;

    // This flag defines whether we have encountered a loop break.
    bool _break_flag;

    // This flag defines whether we have encountered a loop continue.
    bool _cont_flag;

public:

    // Ctor.
    Parser_T(const std::deque<std::shared_ptr<Token_T>>& __tokens)
        : _tokens(__tokens), _loop_flag(false), _break_flag(false), _cont_flag(false) {
        
        // Instantiate the variable handler.
        _var_table = std::make_unique<VariableTable_T>();

        // Instantiate the function handler.
        _func_table = std::make_unique<FunctionTable_T>();

    }
    
    // This function is the main 'brain' of the parser. It will look through
    // a provided token table and dispatch specialized parse functions based on
    // the tokens it encounters.
    void parse(size_t __start_idx, size_t __end_idx, size_t __scope);

    // The following functions are defined in external files from
    // the parser.cpp

    // This function is for parsing expressions. It forms the tokens into
    // an expression tree, and upon success feeds the tree into the evaluator
    // to get the result.
    std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
        parse_expr(size_t& __idx, size_t __end_idx, size_t __scope);

    // This is a helper function for parsing function arguments.
    std::vector<std::shared_ptr<RoskyInterface>>
        parse_func_args(size_t& __idx, size_t __end_idx, size_t __scope);

    // This function is for parsing function calls. It forms objects from the
    // arguments and calls upon the function handler to evaluate the
    // provided function along with its arguments.
    std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
        parse_func(size_t& __idx, size_t __end_idx, size_t __scope);

    // This function is for parsing member function calls. It forms objects
    // from the arguments and calls the function handler.
    std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
        parse_member_func(std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>> __obj,
                          size_t& __idx, size_t __end_idx, size_t __scope);

    // This function is for parsing if statements.
    void parse_if(size_t& __idx, size_t __end_idx, size_t __scope);

    // This function is for parsing while loops.
    void parse_while(size_t& __idx, size_t __end_idx, size_t __scope);

    // These functions (also found in the parse_while.cpp file) are
    // loop controls.
    void parse_continue(size_t& __idx, size_t __end_idx, size_t __scope);
    void parse_break(size_t& __idx, size_t __end_idx, size_t __scope);

    // This function creates a group object.
    std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
        parse_group(size_t& __idx, size_t __end_idx, size_t __scope);

};

/******************************************************************************/

#endif // TOKEN_PARSER
