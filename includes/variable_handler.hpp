
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

#include <memory>                   // std::shared_ptr
#include <string>                   // std::string
#include <utility>                  // std::pair
#include <list>                     // std::list
#include <iterator>                 // std::next

#include <iostream>

#include "objects/rosky_interface.hpp"

/******************************************************************************/

// This struct defines an entry in the variable table.
struct VariableEntry_T {

    std::string _name;
    std::shared_ptr<RoskyInterface> _obj;
    size_t _scope;

    // The recursive index allows us to know the recursion depth
    // of a variable to dictate overwrite rules.
    size_t _recurisve_index;

    VariableEntry_T(const std::string& __name,
                    const std::shared_ptr<RoskyInterface>& __obj,
                    size_t __scope, size_t __r_index)
                    : _name(__name), _obj(__obj),
                    _scope(__scope), _recurisve_index(__r_index) {}

};

/******************************************************************************/

// This class manages the variable table.
class VariableTable_T {

    // The variable table is saved as a linked list so
    // if the table grows or shrinks during evaluation,
    // it won't reallocate when addresses are sensitive.
    std::list<VariableEntry_T> var_table;

public:

    VariableTable_T() {}
    
    // This function sets an entry within the variable table, overwriting
    // the previous entry.
    void set_entry(const std::string& __var_name,
                          const std::shared_ptr<RoskyInterface>& __val,
                          size_t __scope, size_t __r_index) noexcept;

    // This function returns a pointer to the object of the entry
    // with a given name, or nullptr if the entry does not exist.
    // It also returns the entries recursion depth.
    std::pair<std::shared_ptr<RoskyInterface>*, size_t>
        get_entry(const std::string& __var_name) noexcept;

    // This function releases all variables above and including a given
    // scope.
    void release_above_scope(size_t __scope) noexcept;

};

/******************************************************************************/

#endif // VARIABLE_HANDLER


