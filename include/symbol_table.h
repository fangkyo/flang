#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <map>

using namespace std;

class SymbolTable{
    private:
        map<string,string> m_symbolMap;
    public:
        SymbolTable();

};

#endif
