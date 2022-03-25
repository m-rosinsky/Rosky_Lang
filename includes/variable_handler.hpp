
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
//                              table is a map.
//
//  Dependencies:               rosky_interface.hpp
//
//  Classes:                    None
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

#include <map>                      // std::map
#include <memory>                   // std::shared_ptr
#include <string>                   // std::string
#include <utility>                  // std::pair

#include "objects/rosky_interface.hpp"

/******************************************************************************/

// This is the variable table. It is a mapping of a pair of string
// and size_t for the scope of the variable, and the pointer object.
static std::map<std::pair<std::string, size_t>, std::shared_ptr<RoskyInterface>> var_table;

/******************************************************************************/

// This function returns an entry within the variable table, or
// nullptr if the entry is not found.
inline std::shared_ptr<RoskyInterface> get_entry(const std::string& __var_name) noexcept {

    return var_table[{__var_name, 0}];

}

/******************************************************************************/

// This function sets an entry within the variable table, overwriting
// the previous entry.
inline void set_entry(const std::string& __var_name, const std::shared_ptr<RoskyInterface>& __val) noexcept {

    var_table[{__var_name, 0}] = __val;

}

/******************************************************************************/

#endif // VARIABLE_HANDLER


