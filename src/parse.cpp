#include <algorithm>
#include <getopt.h>
#include <unistd.h>
#include "parse.h"

file_permissions getFilePermission(const std::string &name) {

    file_permissions perm{};

    // Check that file exist
    if (access(name.c_str(), F_OK) == 0) {
        perm.F_flag = true;

        // Check read permissions
        if (access(name.c_str(), R_OK) == 0)
            perm.R_flag = true;

        // Check write permissions
        if (access(name.c_str(), W_OK) == 0)
            perm.W_flag = true;
    }

    return perm;
}

void trimLeftNonChar(std::string &input) {
    input.erase(
            input.begin(),
            find_if(input.begin(),
                    input.end(),
                    [](int ch) { return isalpha(ch); }));
}

void trimRightNonChar(std::string &input) {
    input.erase(
            find_if(input.rbegin(),
                    input.rend(),
                    [](int ch) { return isalpha(ch); }).base(),
            input.end());
}

cli_arguments parseArgs(const int argc, char **argv) {
    const char *short_options = "i:o:h";

    const struct option long_options[] = {
            {"input",  required_argument, nullptr, 'i'},
            {"output", required_argument, nullptr, 'o'},
            {"help",   no_argument,       nullptr, 'h'},
            {nullptr, 0,                  nullptr, 0}
    };

    opterr = 0; // do not print internal error message
    cli_arguments args{};

    while (true) {
        const auto curr_opt = getopt_long(argc, argv, short_options, long_options, nullptr);

        // Detect the end of the options
        if (curr_opt == -1) break;

        switch (curr_opt) {
            case 'i':
                args.in_file = optarg;
                args.in_file_set = true;
                break;
            case 'o':
                args.out_file = optarg;
                args.out_file_set = true;
                break;
            case 'h':
                args.help_set = true;
                break;
            default:
                break;
        }
    }

    return args;
}
