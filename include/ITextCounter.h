#pragma once
#include <string>

class ITextCounter {
public:
    virtual ~ITextCounter() = default;
    virtual void execute() = 0;

protected:
    virtual int countWords(const std::string& text) const = 0;
    virtual int countLines(const std::string& text) const = 0;
    virtual int countCharacters(const std::string& text) const = 0;
    virtual int countBytes(const std::string& text) const = 0;
};
