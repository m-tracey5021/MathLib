#pragma once

#include "auxOp.h"
#include <string>
#include <vector>
#include <memory>
#include <utility>

using std::string;
using std::vector;
using std::unique_ptr;
using std::move;
using std::make_unique;
using std::pair;

class Symbol {

    protected:

        char symbol;

        bool sign;

        unique_ptr<AuxOp> auxOp;

    public:

        Symbol();

        Symbol(char symbol);

        Symbol(char symbol, bool sign);

        Symbol(char symbol, unique_ptr<AuxOp>& auxOp);

        Symbol(char symbol, bool sign, unique_ptr<AuxOp>& auxOp);

        ~Symbol();

};