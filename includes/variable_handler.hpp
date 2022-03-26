
/******************************************************************************/
//
//  Source Name:                variable_handler.hpp
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

#ifndef VARIABLE_HANDLER
#define VARIABLE_HANDLER

/******************************************************************************/

#include <deque>                    // std::deque
#include <memory>                   // std::shared_ptr
#include <string>                   // std::string
#include <utility>                  // std::pair

#include <iostream>

#include "objects/rosky_interface.hpp"

/******************************************************************************/

// This struct defines an entry in the variable table.
struct VariableEntry_T {

    std::string _name;
    std::shared_ptr<RoskyInterface> _obj;
    size_t _scope;

    VariableEntry_T(const std::string& __name,
                    const std::shared_ptr<RoskyInterface>& __obj,
                    size_t __scope)
                    : _name(__name), _obj(__obj), _scope(__scope) {}

};

/******************************************************************************/

// This class manages the variable table.
class VariableTable_T {

    std::deque<VariableEntry_T> var_table;

public:
    
    // This function sets an entry within the variable table, overwriting
    // the previous entry.
    inline void set_entry(const std::string& __var_name, const std::shared_ptr<RoskyInterface>& __val) noexcept {

        // See if the entry already exists.
        for (auto& var : var_table) {
            if (var._name == __var_name) {
                var._obj = __val;
                return;
            }
        }

        // Create a new entry.
        var_table.emplace_back(__var_name, __val, 0);

    }

    // This function returns an entry within the variable table, or
    // nullptr if the entry is not found.
    inline std::shared_ptr<RoskyInterface> get_entry(const std::string& __var_name) const noexcept {

        for (auto& var : var_table) {
            if (var._name == __var_name) {
                return var._obj;
            }
        }

        return nullptr;

    }

};

/******************************************************************************/

#endif // VARIABLE_HANDLER


