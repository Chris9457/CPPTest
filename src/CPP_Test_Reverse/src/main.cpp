#include "Glossary.h"
#include <iostream>
#include <filesystem>

int main(int argc, char **argv) {
    static const std::string tableOption{ "--table" };
    static const std::string reverseOption{ "--reverse" };
    bool generateTable   = false;
    bool generateReverse = false;
    std::filesystem::path path;

    for (int index = 1; index < argc; ++index) {
        if (argv[index] == tableOption) {
            generateTable = true;
        } else if (argv[index] == reverseOption) {
            generateReverse = true;
        } else {
            path = std::string(argv[index]);
        }
    }

    if (!exists(path) || !generateReverse && !generateTable) {
        std::cout << "Bad usage - tape:" << std::endl;
        std::cout << "Cpp_Test_Reverse [OPTIONS] <filename>" << std::endl;
        std::cout << std::endl;
        std::cout << "<filename> : name of the file to parse" << std::endl;
        std::cout << std::endl;
        std::cout << "OPTIONS:" << std::endl;
        std::cout << "    --table : to generate a table" << std::endl;
        std::cout << "    --reverse : to generate a reverted file" << std::endl;
        std::cout << std::endl;
        return -1;
    }

    cpptest::Glossary glossary(path);
    if (generateTable) {
        glossary.exportToTable();
    }
    if (generateReverse) {
        glossary.exportToReverse();
    }

    return 0;
}
