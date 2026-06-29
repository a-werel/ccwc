#include <CLITextCounter.h>
#include <iostream>

int main(int argc, char* argv[]) {
    CLITextCounter counter(argc, argv);
    counter.execute();
    return 0;
}