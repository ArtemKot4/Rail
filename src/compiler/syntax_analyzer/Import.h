#ifndef IMPORT_H
#define IMPORT_H

#include <string>
#include <vector>

struct Import {
    std::string file;
    std::vector<std::string> symbols;
    int line, column;
};

#endif