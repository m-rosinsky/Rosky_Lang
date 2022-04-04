
/******************************************************************************/
//
//  Source Name:                parse_group.cpp
//
//  Description:                This file is responsible for parsing
//                              groups. It will form a RoskyGroup object
//                              from a token table and a given start
//                              iterator.
// 
//
//  Dependencies:               lexer_utils.hpp
//                              parser_utils.hpp
//                              error_handler.hpp
//                              evaluator.hpp
//                              variable_handler.hpp
//                              rosky_interface.hpp
//
//  Classes:                    Parser_T
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       parse_expr
//                              
/******************************************************************************/

#include "../../includes/parser.hpp"

#include "../../includes/objects/rosky_group.hpp"

/******************************************************************************/

std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    Parser_T::parse_group(size_t& __idx, size_t __end_idx, size_t __scope) {

    // Create a deque to hold the objects.
    std::deque<std::shared_ptr<RoskyInterface>> obj_deque;

    // Collect objects until no more commas.
    size_t comma_idx = find_nextof(_tokens, ++__idx, ",");

    // This flag marks if we have a comma.
    bool has_comma = false;

    // While the comma comes before the end idx.
    while (comma_idx != 0 && comma_idx < __end_idx) {

        // Mark the flag.
        has_comma = true;

        // If the comma is the next index, throw an error for an empty arg.
        if (comma_idx == __idx) {
            throw_error(ERR_EMPTY_ARG, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
        }

        // Parse the expression from this index, to the comma index.
        auto obj_pair = parse_expr(__idx, comma_idx, __scope);

        // Add the object to the deque.
        obj_deque.push_back(obj_pair.second);

        // Find the next comma.
        comma_idx = find_nextof(_tokens, ++__idx, ",");

    }

    // If the next index is the closing bracket and no comma, return empty.
    if (__idx == __end_idx && !has_comma) {
        return {nullptr, std::make_shared<RoskyGroup>(obj_deque)};
    }

    // If the next index is closing parentheses and comma, empty arg.
    if (__idx == __end_idx) {
        throw_error(ERR_EMPTY_ARG, "", _tokens[__idx]->_colnum, _tokens[__idx]->_linenum);
    }

    // Parse the expression between this index and the end idx.
    auto obj_pair = parse_expr(__idx, __end_idx, __scope);

    // Add the object to the deque.
    obj_deque.push_back(obj_pair.second);

    // Return the new object.
    return {nullptr, std::make_shared<RoskyGroup>(obj_deque)};

}

/******************************************************************************/
