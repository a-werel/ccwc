#include <ITextCounter.h>
#include <istream>
#include <string>
#include <vector>

class CLITextCounter : public ITextCounter {
public:
  void execute() override;
  CLITextCounter(int argc, char *argv[]);

protected:
  void printHelp() const;
  int countWords(const std::string &text) const override;
  int countLines(const std::string &text) const override;
  int countCharacters(const std::string &text) const override;
  int countBytes(const std::string &text) const override;

private:
  std::string readFromFile(const std::string &filename) const;
  int argc_;
  std::vector<std::string> options_;
  std::string filename_;
  std::string text_;
};
