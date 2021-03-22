#pragma once

#include "symbol.h"

struct Scope {
    vector<pair<char, int>> ops;
    int start;
    int end;
};

class Operation : public Symbol {

    protected:

        Scope scope;

    public:

        Operation();

        Operation(char op);

};