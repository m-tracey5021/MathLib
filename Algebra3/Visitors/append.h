#pragma once

#include "visitor.h"

class Append : public Visitor {

    public:

        Append();

        void append(Symbol& parent, shared_ptr<Symbol>& child);

};