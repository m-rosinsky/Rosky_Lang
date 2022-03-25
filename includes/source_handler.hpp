
/******************************************************************************/
//
//  Source Name:                source_handler.hpp
//
//  Description:                This file is responsible for opening
//                              the provided file path from the input
//                              command and formatting it into a usable
//                              source object.
//
//  Dependencies:               None
//
//  Classes:                    Src_T
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       ctor
//                              
/******************************************************************************/

#ifndef SRC_HANDLER
#define SRC_HANDLER

/******************************************************************************/

#include <string>                   // std::string
#include <fstream>                  // std::ifstream

/******************************************************************************/

// This struct is considered formatted source. It accepts
// a filepath from stdin and creates a formatted source
// within the constructor.
struct Src_T {

    // This holds the source file name.
    std::string _filename;

    // This holds the source file contents.
    std::string _data;

    // Ctor.
    Src_T(const std::string& __filename)
        : _filename(__filename) {

        // Read in the file from stdin.
        std::ifstream in_file(_filename);

        // Read in the contents of the file line by line.
        for (std::string line; std::getline(in_file, line); ) {

            // Some text editors insert carriage returns '13' at the end
            // of lines, while others don't. Filter out carriage returns
            // so the line endings are standardized.
            if (int(line[line.size() - 1]) == 13) {
                line = line.substr(0, line.size()-1);
            }

            _data += line;

            // Insert a new line character at the end of the line
            _data += char(10);

        }

        // Close the file.
        in_file.close();

    }

};

/******************************************************************************/

#endif // SRC_HANDLER
