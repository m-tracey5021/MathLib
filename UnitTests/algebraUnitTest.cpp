#include <iostream>
#include <memory>

#include "algebraUnitTest.h"
#include "../Algebra3/expressionComponents.h"

using std::shared_ptr;
using std::make_shared;

bool testStructure(){

    SumOp sum = SumOp();
    MulOp mul = MulOp();
    DivOp div = DivOp();

    shared_ptr<SymbolContainerBase> sumContainer = make_shared<SymbolContainer<SumOp>>(sum);
    shared_ptr<SymbolContainerBase> mulContainer = make_shared<SymbolContainer<MulOp>>(mul);
    shared_ptr<SymbolContainerBase> divContainer = make_shared<SymbolContainer<DivOp>>(div);

    
    vector<shared_ptr<SymbolContainerBase>> containers;

    containers.push_back(sumContainer);
    containers.push_back(mulContainer);
    containers.push_back(divContainer);

    Expression expression = Expression(containers);

    string result = expression.toString();

    return true;
}