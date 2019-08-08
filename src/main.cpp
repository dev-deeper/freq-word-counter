#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "parse.h"

#define EXIT_OK 0
#define EXIT_FAILURE 1

// Program usage
void usage();

// Print error message to stdout
void printError(const std::string &err);

int main(int argc, char **argv) {

    // Parse CLI arguments
    cli_arguments args = parseArgs(argc, argv);

    // Check input data
    if (argc == 1 or args.help_set) {
        usage();
        return EXIT_OK;
    } else if (argc < 3) {
        printError("Invalid arguments count.");
        usage();
        return EXIT_FAILURE;
    } else if (not args.in_file_set) {
        printError("Input file doesn't set.");
        return EXIT_FAILURE;
    }

    // Check input file permissions
    file_permissions in_file_perm = getFilePermission(args.in_file);
    if (not in_file_perm.F_flag) {
        printError("File \"" + args.in_file + "\" doesn't exist.");
        return EXIT_FAILURE;
    } else if (not in_file_perm.R_flag) {
        printError("File \"" + args.in_file + "\" reading prohibited.");
        return EXIT_FAILURE;
    }

    std::ifstream inputFile;
    inputFile.open(args.in_file);
    std::unordered_map<std::string, size_t> dict;

    // Read input file
    for (std::string word; inputFile >> word;) {

        // Convert word to lower case
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        // Trim begin and end non character symbols
        trimLeftNonChar(word);
        trimRightNonChar(word);

        // Add word to map
        dict[word]++;
    }

    std::vector<std::pair<std::string, size_t>> v_dict(dict.begin(), dict.end());
    std::sort(v_dict.begin(), v_dict.end(),
              [](const std::pair<std::string, size_t> &a, const std::pair<std::string, size_t> &b) {
                  return (a.second == b.second) ? (a.first < b.first) : (a.second > b.second);
              });

    // Check that output file was given
    if (args.out_file_set) {
        std::ofstream outFile;
        outFile.open(args.out_file);

        // Check output file permissions
        file_permissions out_file_perm = getFilePermission(args.out_file);
        if (not out_file_perm.W_flag) {
            printError("File \"" + args.out_file + "\" writing prohibited.");
            return EXIT_FAILURE;
        }

        // Write results to output file
        for (const auto &x: v_dict)
            outFile << x.second << ' ' << x.first << std::endl;

    } else {

        // Write results to stdout
        for (const auto &x: v_dict)
            std::cout << x.second << ' ' << x.first << std::endl;
    }

    return EXIT_OK;
}

void usage() {
    std::cout << "Usage: freq -i INPUT_FILE [-o OUTPUT_FILE]\n";
    std::cout << "Counting repeated words in INPUT_FILE.\nPrint output to stdout if OUTPUT_FILE doesn't given.\n\n";
    std::cout << "Arguments:\n";
    std::cout << "  -i, --input  set input file\n";
    std::cout << "  -o, --output set output file\n";
    std::cout << "  -h, --help   display this help and exit\n";
}

void printError(const std::string &err) {
    std::cerr << "[!] ERROR: " << err << std::endl;
}
