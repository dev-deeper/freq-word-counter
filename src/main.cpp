#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "parse.h"

#define EXIT_OK 0
#define EXIT_FAILURE 1

// Program Usage
void Usage();

// Print error message to stdout
void PrintError(const std::string &err);

int main(int argc, char **argv) {
    // Parse CLI arguments
    CliArguments args = ParseArgs(argc, argv);

    // Check input data
    if (argc == 1 or args.help_set) {
        Usage();
        return EXIT_OK;
    } else if (argc < 3) {
        PrintError("Invalid arguments count.");
        Usage();
        return EXIT_FAILURE;
    } else if (not args.in_file_set) {
        PrintError("Input file doesn't set.");
        return EXIT_FAILURE;
    }

    // Check input file permissions
    FilePermissions in_file_perm = GetFilePermission(args.in_filename);
    if (not in_file_perm.f_flag) {
        PrintError("File \"" + args.in_filename + "\" doesn't exist.");
        return EXIT_FAILURE;
    } else if (not in_file_perm.r_flag) {
        PrintError("File \"" + args.in_filename + "\" reading prohibited.");
        return EXIT_FAILURE;
    }

    std::ifstream input_file(args.in_filename);
    WordCountDictionary dict;

    // Read input file
    for (std::string word; input_file >> word;) {
        PrepareWord(word);
        dict[word]++;
    }

    input_file.close();
    PairVector sorted_dict = SortDict(dict);

    // Check that output file was given
    if (args.out_file_set) {
        // Check output file permissions
        FilePermissions out_file_perm = GetFilePermission(args.out_filename);
        if (out_file_perm.f_flag and (not out_file_perm.w_flag)) {
            PrintError("File \"" + args.out_filename + "\" writing prohibited.");
            return EXIT_FAILURE;
        }

        std::ofstream output_file(args.out_filename);

        // Write results to output file
        for (const auto &x: sorted_dict)
            output_file << x.second << ' ' << x.first << std::endl;

        output_file.close();
    } else {
        // Write results to stdout
        for (const auto &x: sorted_dict)
            std::cout << x.second << ' ' << x.first << std::endl;
    }

    return EXIT_OK;
}

void Usage() {
    std::cout << "Usage: freq -i INPUT_FILE [-o OUTPUT_FILE]\n";
    std::cout << "Counting repeated words in INPUT_FILE.\nPrint output to stdout if OUTPUT_FILE doesn't given.\n\n";
    std::cout << "Arguments:\n";
    std::cout << "  -i, --input  set input file\n";
    std::cout << "  -o, --output set output file\n";
    std::cout << "  -h, --help   display this help and exit\n";
}

void PrintError(const std::string &err) {
    std::cerr << "[!] ERROR: " << err << std::endl;
}
