#include <CLITextCounter.h>
#include <gtest/gtest.h>
#include <fstream>

class CLITextCounterWrapper : public CLITextCounter {
public:
    CLITextCounterWrapper(int argc, char* argv[]) : CLITextCounter(argc, argv) {}
    int countWordsPublic(const std::string& text) const { return countWords(text); }
    int countLinesPublic(const std::string& text) const { return countLines(text); }
    int countCharactersPublic(const std::string& text) const { return countCharacters(text); }
    int countBytesPublic(const std::string& text) const { return countBytes(text); }
};

TEST(CLITextCounterTest, CountWords) {
    CLITextCounterWrapper counter(0, nullptr);
    EXPECT_EQ(counter.countWordsPublic("Hello world!"), 2);
    EXPECT_EQ(counter.countWordsPublic("Hello   world!"), 2);
    EXPECT_EQ(counter.countWordsPublic("Hello\nworld!"), 2);
    EXPECT_EQ(counter.countWordsPublic("Hello\tworld!"), 2);
    EXPECT_EQ(counter.countWordsPublic(""), 0);
    EXPECT_EQ(counter.countWordsPublic("   "), 0);
    EXPECT_EQ(counter.countWordsPublic("\n\n\n"), 0);
    EXPECT_EQ(counter.countWordsPublic("\t\t\t"), 0);
}

TEST(CLITextCounterTest, CountLines) {
    CLITextCounterWrapper counter(0, nullptr);
    EXPECT_EQ(counter.countLinesPublic("Hello world!"), 0);
    EXPECT_EQ(counter.countLinesPublic("Hello world!\nThis is a test."), 1);
    EXPECT_EQ(counter.countLinesPublic("Line1\nLine2\nLine3"), 2);
    EXPECT_EQ(counter.countLinesPublic(""), 0);
    EXPECT_EQ(counter.countLinesPublic("\n\n\n"), 3);
    EXPECT_EQ(counter.countLinesPublic("\t\t\t"), 0);
}

TEST(CLITextCounterTest, CountCharacters) {
    CLITextCounterWrapper counter(0, nullptr);
    EXPECT_EQ(counter.countCharactersPublic("Hello world!"), 12);
    EXPECT_EQ(counter.countCharactersPublic("ą"), 1);
    EXPECT_EQ(counter.countCharactersPublic("ą ę"), 3);
    EXPECT_EQ(counter.countCharactersPublic("Hello ą world!"), 14);
    EXPECT_EQ(counter.countCharactersPublic("Hello ą ę world!"), 16);
    EXPECT_EQ(counter.countCharactersPublic("Hello ą ę world!\nThis is a test."), 32);
    EXPECT_EQ(counter.countCharactersPublic("Hello ą ę world!\nThis is a test.\tOne two three four five."), 57);
    EXPECT_EQ(counter.countCharactersPublic(""), 0);
    EXPECT_EQ(counter.countCharactersPublic("   "), 3);
    EXPECT_EQ(counter.countCharactersPublic("\n\n\n"), 3);
    EXPECT_EQ(counter.countCharactersPublic("\t\t\t"), 3);
}

TEST(CLITextCounterTest, CountBytes) {
    CLITextCounterWrapper counter(0, nullptr);
    EXPECT_EQ(counter.countBytesPublic("Hello world!"), 12);
    EXPECT_EQ(counter.countBytesPublic("ą"), 2);
    EXPECT_EQ(counter.countBytesPublic("ą ę"), 5);
    EXPECT_EQ(counter.countBytesPublic("Hello ą world!"), 15);
    EXPECT_EQ(counter.countBytesPublic("Hello ą ę world!"), 18);
    EXPECT_EQ(counter.countBytesPublic("Hello ą ę world!\nThis is a test."), 34);
    EXPECT_EQ(counter.countBytesPublic("Hello ą ę world!\nThis is a test.\tOne two three four five."), 59);
    EXPECT_EQ(counter.countBytesPublic(""), 0);
    EXPECT_EQ(counter.countBytesPublic("   "), 3);
    EXPECT_EQ(counter.countBytesPublic("\n\n\n"), 3);
    EXPECT_EQ(counter.countBytesPublic("\t\t\t"), 3);
}
