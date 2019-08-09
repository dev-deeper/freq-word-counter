#include <algorithm>
#include <getopt.h>
#include <unistd.h>
#include "parse.h"

FilePermissions GetFilePermission(const std::string &name) {

    FilePermissions perm{};

    // Check that file exist
    if (access(name.c_str(), F_OK) == 0) {
        perm.f_flag = true;

        // Check read permissions
        if (access(name.c_str(), R_OK) == 0)
            perm.r_flag = true;

        // Check write permissions
        if (access(name.c_str(), W_OK) == 0)
            perm.w_flag = true;
    }

    return perm;
}

void PrepareWord(std::string &input) {

    // Convert word to lower case
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);

    // Trim begin and end non character symbols
    TrimLeftNonChar(input);
    TrimRightNonChar(input);

}

void TrimLeftNonChar(std::string &input) {
    input.erase(
            input.begin(),
            find_if(input.begin(),
                    input.end(),
                    [](int ch) { return isalpha(ch); }));
}

void TrimRightNonChar(std::string &input) {
    input.erase(
            find_if(input.rbegin(),
                    input.rend(),
                    [](int ch) { return isalpha(ch); }).base(),
            input.end());
}

CliArguments ParseArgs(const int argc, char **argv) {
    const char *short_options = "i:o:h";

    const struct option long_options[] = {
            {"input",  required_argument, nullptr, 'i'},
            {"output", required_argument, nullptr, 'o'},
            {"help",   no_argument,       nullptr, 'h'},
            {nullptr, 0,                  nullptr, 0}
    };

    opterr = 0; // do not print internal error message
    CliArguments args{};

    while (true) {
        const auto curr_opt = getopt_long(argc, argv, short_options, long_options, nullptr);

        // Detect the end of the options
        if (curr_opt == -1) break;

        switch (curr_opt) {
            case 'i':
                args.in_filename = optarg;
                args.in_file_set = true;
                break;
            case 'o':
                args.out_filename = optarg;
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

PairVector SortDict(const WordCountDictionary &map) {

    PairVector v_dict(map.begin(), map.end());
    std::sort(v_dict.begin(), v_dict.end(),
              [](const StringCountPair &a, const StringCountPair &b) {
                  return (a.second == b.second) ? (a.first < b.first) : (a.second > b.second);
              });

    return v_dict;
}
