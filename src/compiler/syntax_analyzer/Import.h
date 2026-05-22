#ifndef IMPORT_H
#define IMPORT_H

struct Import {
    std::string file;
    std::vector<std::string> symbols;
    int line, column;
};

#endif