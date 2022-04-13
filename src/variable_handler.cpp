
/******************************************************************************/
//
//  Source Name:                variable_handler.cpp
//
//  Description:                This file is responsible managing the
//                              variable/symbol table. It contains
//                              functions to get and set different
//                              entries in the table.
// 
//                              The data structure for the variable
//                              table is a deque.
//
//  Dependencies:               rosky_interface.hpp
//
//  Classes:                    VariableEntry_T
//                              VariableTable_T
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       get_entry
//                              set_entry
//                              
/******************************************************************************/

#include "../includes/variable_handler.hpp"

/******************************************************************************/

void VariableTable_T::set_entry(const std::string& __var_name,
                                const std::shared_ptr<RoskyInterface>& __val,
                                size_t __scope, size_t __r_index) noexcept {
    
    // Create a new entry.
    var_table.emplace_front(__var_name, __val, __scope, __r_index);

}

/******************************************************************************/

std::pair<std::shared_ptr<RoskyInterface>*, size_t>
        VariableTable_T::get_entry(const std::string& __var_name) noexcept {

    for (auto& var : var_table) {
        if (var._name == __var_name) {
            return {&(var._obj), var._recurisve_index};
        }
    }

    return {nullptr, 0};

}

/******************************************************************************/

void VariableTable_T::release_above_scope(size_t __scope) noexcept {

    std::deque<size_t> deletion;

    size_t idx = 0;
    for (auto& var : var_table) {
        if (var._scope >= __scope) {
            deletion.push_front(idx);
        }
        idx++;
    }

    for (auto it = deletion.begin(); it != deletion.end(); it++) {
        auto list_it = var_table.begin();
        std::next(list_it, *it);
        var_table.erase(list_it);
    }

}

/******************************************************************************/