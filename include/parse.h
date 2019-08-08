#pragma once
#include <string>

// CLI arguments structure
struct cli_arguments {
    std::string in_file;        // input file
    bool in_file_set = false;   // input file set flag
    std::string out_file;       // output file
    bool out_file_set = false;  // output file set flag
    bool help_set = false;      // help flag
};

// File permissions structure
struct file_permissions {
    bool F_flag = false; // the file exists
    bool R_flag = false; // the file can be accessed for reading
    bool W_flag = false; // the file can be accessed for writing
};

// Get file permissions
file_permissions getFilePermission(const std::string &name);

// Trim left non character symbols
void trimLeftNonChar(std::string &input);

// Trim right non character symbols
void trimRightNonChar(std::string &input);

cli_arguments parseArgs(int argc, char **argv);
