#include <CLITextCounter.h>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

void CLITextCounter::printHelp() const {
    std::cout << "Usage ccwc [options] [file...]\n"
              << "Options:\n"
              << "-h, --help\tShow this help message\n"
              << "-w, --words\tCount words\n"
              << "-l, --lines\tCount lines\n"
              << "-c, --characters\tCount characters\n"
              << "-b, --bytes\tCount bytes\n";
}

std::string CLITextCounter::readFromFile(const std::string& filename) const {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

CLITextCounter::CLITextCounter(int argc, char* argv[]) : argc_(argc), options_(), text_("") {
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            if (std::strncmp("-", argv[i], 1) == 0) {
                options_.push_back(std::string(argv[i]));
            } else {
                std::string filename(argv[i]);
                text_ = readFromFile(filename);
            }
        }
    }
}

void CLITextCounter::execute() {
    if (argc_ <= 1) {
        printHelp();
        return;
    }
    for (const auto& option : options_) {
        if (option == "-h" || option == "--help") {
            printHelp();
            return;
        } else if (option == "-w" || option == "--words") {
            std::cout << "Word count: " << countWords(text_) << std::endl;
        } else if (option == "-l" || option == "--lines") {
            std::cout << "Line count: " << countLines(text_) << std::endl;
        } else if (option == "-c" || option == "--characters") {
            std::cout << "Character count: " << countCharacters(text_) << std::endl;
        } else if (option == "-b" || option == "--bytes") {
            std::cout << "Byte count: " << countBytes(text_) << std::endl;
        } else {
            std::cerr << "Unknown option: " << option << std::endl;
            printHelp();
            return;
        }
    }
}

int CLITextCounter::countWords(const std::string& text) const {
    std::stringstream stream;
    // rdbuf() returns a pointer to the stream buffer associated with the stream.
    // pubsetbuf() sets the buffer for the stream to the provided character array.
    // it requires pointer to non-const char array, so we use const_cast to remove constness from text.c_str()
    stream.rdbuf()->pubsetbuf(const_cast<char*>(text.c_str()), text.size());
    std::istream_iterator<std::string> begin(stream), end;
    // std::distance returns how many times it had to do ++ on begin to reach end
    // ++ on iterator advances it forward to the next word in the stream, so the
    // distance is the number of words
    return std::distance(begin, end);
}

int CLITextCounter::countLines(const std::string& text) const { return std::count(text.begin(), text.end(), '\n') + (text.empty() ? 0 : 1); }

int CLITextCounter::countBytes(const std::string& text) const { return static_cast<int>(text.size()); }

// count UTF8 characters, we need to manually check whether the byte
int CLITextCounter::countCharacters(const std::string& text) const {
    return std::count_if(text.begin(), text.end(), [](unsigned char c) { return (c & 0xC0) != 0x80; });
}
