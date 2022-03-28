
/******************************************************************************/
//
//  Source Name:                main.cpp
//
//  Description:                This is the main file and entry
//                              point for the program. It's job
//                              is to parse the input commands
//                              and report usage corrections.
//
//                              Upon success, the input file is
//                              converted to a source object
//                              and lexing may begin.
//
//  Dependencies:               source_handler.hpp
//                              lexer.hpp
//
//  Classes:                    None
//
//  Inherited Subprograms:      None
//
//  Exported Subprograms:       None
//
/******************************************************************************/

#include <cstdio>               // printf, fprintf
#include <fstream>              // std::ifstream
#include <string.h>             // strlen
#include <memory>               // std::unique_ptr, std::make_unique

#include "includes/source_handler.hpp"
#include "includes/lexer.hpp"

/******************************************************************************/

// This enum defines the command line status type.
enum CMD_LINE_STATUS {

    OK,
    BAD_ARGS,
    FILE_NOT_FOUND,
    INVALID_FILE_TYPE,

};

/******************************************************************************/

// This function is responsible for taking args from stdin and
// returning a status.
CMD_LINE_STATUS arg_parser(int argc, char* argv[]) {

    // Check if the number of arguments is incorrect.
    if (argc != 2) {
        return BAD_ARGS;
    }

    // Set a temporary string to check against the provided
    // file extension.
    char ext[] = ".rosky";

    // Attempt to open the file.
    std::ifstream in_file;
    in_file.open(argv[1]);

    // If the file did not open, it could not be found.
    if (!in_file.is_open()) {
        return FILE_NOT_FOUND;
    }

    // Close the file.
    in_file.close();

    // If the length of the filename is less than
    // the length of the extension, it cannot be a legal
    // filename.
    if (strlen(argv[1]) < strlen(ext)) {
        return INVALID_FILE_TYPE;
    }

    // Check the file extension.
    size_t ext_index = 0;
    for (size_t i = strlen(argv[1]) - strlen(ext); i < strlen(argv[1]); i++) {

        if (argv[1][i] != ext[ext_index++]) {
            return INVALID_FILE_TYPE;
        }

    }

    // Passed all checks, return ok.
    return OK;

}

/******************************************************************************/

// This function takes in a cmd status and responds accordingly.
// This function will terminate execution if the status is not OK.
void status_response(CMD_LINE_STATUS __status, char* argv[]) {

    // If the status is ok, return.
    if (__status == OK) { return; }

    // Respond to status accordingly.
    if (__status == BAD_ARGS) {
        fprintf(stderr, "Bad arguments\n");
    } else if (__status == FILE_NOT_FOUND) {
        fprintf(stderr, "File not found: '%s'\n", argv[1]);
    } else if (__status == INVALID_FILE_TYPE) {
        fprintf(stderr, "Invalid file type\n");
    }

    fprintf(stderr, "Format: $ ");
    fprintf(stderr, "rosky.exe [filepath].rosky\n");

    exit(1);

}

/******************************************************************************/

int main(int argc, char* argv[]) {

    // Parse the command line arguments and get a status.
    CMD_LINE_STATUS status = arg_parser(argc, argv);

    // Respond to errors. This function will terminate the
    // program on it's own if status is not OK.
    status_response(status, argv);

    // Create the main source object.
    std::unique_ptr<Src_T> main_src = std::make_unique<Src_T>(argv[1]);

    // Pass the main source into the lexer.
    tokenize_src(main_src);

    // Return successful.
    return 0;

}

/******************************************************************************/
