
/******************************************************************************/
//
//  Source Name:                lexer.hpp
//
//  Description:                This file is responsible for "tokenizing"
//                              a provided source file. Tokens are store
//                              in a table (std::deque) with each entry
//                              containing certain metadata.
//
//                              Specific lexer errors such as unrecognized
//                              or unexpected tokens can be caught and thrown
//                              here, but the lexer is not responsible for
//                              making logical or syntactic sense of the
//                              source.
//
//                              After the table is created, it will be
//                              fed into the parser.
//
//  Dependencies:               source_handler.hpp
//                              lexer_utils.hpp
//                              error_handler.hpp
//                              <parser>
//
//  Classes:                    None
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       tokenize_src
//                              
/******************************************************************************/

#ifndef SRC_LEXER
#define SRC_LEXER

/******************************************************************************/

#include <string>                   // std::string
#include <deque>                    // std::deque
#include <memory>                   // std::unique_ptr, std::make_unique

#include "source_handler.hpp"
#include "error_handler.hpp"
#include "utils/lexer_utils.hpp"

/******************************************************************************/

// This function is responsible for converting a formatted source
// into a table of tokens for parsing.
void tokenize_src(const std::unique_ptr<Src_T>& __src);

/******************************************************************************/

#endif // SRC_LEXER