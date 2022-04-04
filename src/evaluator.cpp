
/******************************************************************************/
//
//  Source Name:                evaluator.cpp
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

#include "../includes/evaluator.hpp"

/******************************************************************************/

std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>>
    evaluate(const std::shared_ptr<ParseNode>& __root,
             std::unique_ptr<VariableTable_T>& __var_table, bool __top,
             size_t __scope) {

    // Operands
    
    if (__root->_type == PARSE_OPERAND) {

        // If this is a top level evaluation and the root is nullptr,
        // this means there was an unrecognized symbol.
        if (__root->is_nullptr() && __top) {
            throw_error(ERR_UNREC_SYM, __root->_op, __root->_colnum, __root->_linenum);
        }
        return {__root->_obj_adr, __root->_obj};

    }

    // Operators

    // Double left-right associative operators.
    if (__root->_type == PARSE_OPERATOR) {

        // Create a temp storage for the return value and the left and right operands.
        std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>> ret_obj = {nullptr, nullptr};

        auto right = evaluate(__root->_right, __var_table, false, __scope);
        std::pair<std::shared_ptr<RoskyInterface>*, std::shared_ptr<RoskyInterface>> left = {nullptr, nullptr};

        // If the operator is not unary, evaluate the left side.
        if (!is_unary_eval_op(__root->_op)) {
            left = evaluate(__root->_left, __var_table, false, __scope);
        }

        // The right side of an op is never allowed to be nullptr. This means
        // a symbol was unrecognized. Throw an error.
        if (right.second == nullptr) {
            throw_error(ERR_UNREC_SYM, __root->_right->_op, __root->_right->_colnum, __root->_right->_linenum);
        }

        // The left side of the op is allowed to be nullptr on assignments,
        // so check those first.
        if (is_assignment_op(__root->_op)) {

            // If the left side of the assign is unassignable, but not null
            // (new entry), throw an error.
            if (left.first == nullptr && left.second != nullptr) {
                throw_error(ERR_BAD_ASSIGN, "", __root->_colnum, __root->_linenum);
            }

            // Simple Assignment.
            if (__root->_op == "=") {

                // If the left has an addressable object, simply overwrite it.
                // Otherwise, set an entry.
                if (left.first != nullptr) {
                    *(left.first) = right.second;
                } else {
                    __var_table->set_entry(__root->_left->_op, right.second, __scope);
                }

            }

            // Return the right-side object.
            return right;

        }

        // If the left side of an op is nullptr.
        if (left.second == nullptr) {

            // The left side of the operator is allowed to be nullptr only
            // on unary operators. If the left side of an op is nullptr
            // on a non-unary operator, then there was an unrecognized
            // symbol
            if (!is_unary_eval_op(__root->_op)) {
                throw_error(ERR_UNREC_SYM, __root->_left->_op, __root->_left->_colnum, __root->_left->_linenum);
            }

        }

        // Perform the operation.
        if (__root->_op == "+") {
            ret_obj = {nullptr, left.second->add_op(right.second)};
        } else if (__root->_op == "*") {
            ret_obj = {nullptr, left.second->mul_op(right.second)};
        } else if (__root->_op == "&") {
            ret_obj = {nullptr, left.second->concat_op(right.second)};
        } else if (__root->_op == "==") {
            ret_obj = {nullptr, left.second->eq_op(right.second)};
        } else if (__root->_op == "[") {

            // If the left object is not iterable, throw error.
            if (left.second->is_iterable() == false) {
                throw_error(ERR_NON_ITERABLE, "'" + left.second->get_type_string() + "'", __root->_colnum, __root->_linenum);
            }

            // Check if the operation should return an addressable object.
            bool addressable = false;
            if (left.first != nullptr) {
                if ((*left.first)->is_addressable()) {
                    addressable = true;
                }
            }

            // Perform the operation.
            if (addressable) {
                ret_obj = (*left.first)->index_op(right.second, true);
            } else {
                ret_obj = left.second->index_op(right.second, false);
            }

            // Special case of index oob.
            if (ret_obj.first == nullptr && ret_obj.second == nullptr) {
                throw_error(ERR_INDEX_OOB, right.second->to_string(), __root->_right->_colnum, __root->_right->_linenum);
            }

        } else if (__root->_op == "de") {
            ret_obj = right.second->deref_op();

            // Special case where we try to dereference a nullptr.
            if (ret_obj.second == nullptr && right.second->get_type_id() == OBJ_POINTER) {
                throw_error(ERR_DEREF_NULLPTR, "", __root->_colnum, __root->_linenum);
            }

        } else if (__root->_op == "@") {
            
            // If the .first attribute of the right object is nullptr,
            // then we are trying to get the address of a temporary.
            if (right.first == nullptr) {
                throw_error(ERR_ADDR_TEMP, "", __root->_colnum, __root->_linenum);
            }

            ret_obj = {nullptr, std::make_shared<RoskyPointer>(right.first)};

        }

        // If the ret_obj is nullptr, the operator was incompat.
        if (ret_obj.second == nullptr) {

            // Construct the error message
            std::string err_op = __root->_op == "de" ? "deref" : __root->_op;

            std::string err_msg = "'" + err_op + "'";

            // Unary operator
            if (left.second == nullptr) {
                err_msg += " with type: '";
                err_msg += right.second->get_type_string();
            } else{
                err_msg += " with types: '";
                err_msg += left.second->get_type_string() + "' and '";
                err_msg += right.second->get_type_string() + "'";
            }

            throw_error(ERR_OP_INCOMPAT, err_msg, __root->_colnum, __root->_linenum);
        }

        // std::cout << ret_obj->to_string() << std::endl;

        // Return the object.
        return ret_obj;

    }

    // Should never reach here, but for safety.
    throw_error(ERR_UNEXP_OP, __root->_op, __root->_colnum, __root->_linenum);
    return {nullptr, nullptr};

}

/******************************************************************************/
