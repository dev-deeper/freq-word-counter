#ifndef FREQ_PARSE_H_
#define FREQ_PARSE_H_

#include <string>
#include <vector>
#include <unordered_map>

typedef std::unordered_map<std::string, size_t> WordCountDictionary;
typedef std::pair<std::string, size_t> StringCountPair;
typedef std::vector<StringCountPair> PairVector;

// CLI arguments structure
struct CliArguments {
    std::string in_filename;    // input filename
    bool in_file_set = false;   // input file set flag
    std::string out_filename;   // output filename
    bool out_file_set = false;  // output file set flag
    bool help_set = false;      // help flag
};

// File permissions structure
struct FilePermissions {
    bool f_flag = false; // the file exists
    bool r_flag = false; // the file can be accessed for reading
    bool w_flag = false; // the file can be accessed for writing
};

// Get file permissions
FilePermissions GetFilePermission(const std::string &name);

// Convert word to lowercase
void PrepareWord(std::string &input);

// Trim left non character symbols
void TrimLeftNonChar(std::string &input);

// Trim right non character symbols
void TrimRightNonChar(std::string &input);

// Parse CLI arguments
CliArguments ParseArgs(int argc, char **argv);

PairVector SortDict(const WordCountDictionary &map);

#endif
