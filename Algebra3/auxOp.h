#pragma once

#include <string>
#include <vector>
#include <memory>
#include <utility>

using std::string;
using std::vector;
using std::unique_ptr;
using std::shared_ptr;
using std::move;
using std::make_unique;
using std::make_shared;
using std::pair;

class Symbol;

class AuxOp {

    protected:

        unique_ptr<Symbol> root;

    public:

        AuxOp();

        AuxOp(unique_ptr<Symbol>& root);

        ~AuxOp();

        void setRoot(unique_ptr<Symbol>& root);

        unique_ptr<Symbol>& getRoot();

        virtual unique_ptr<AuxOp> copy() = 0;

        virtual string toString() = 0;

};
