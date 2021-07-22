#include <iostream>
#include <memory>

#include "algebraUnitTest.h"
#include "../Algebra3/expression.h"
#include "../Algebra3/expressionComponents.h"

using std::shared_ptr;
using std::make_shared;

bool testStructure(){

    // SumOp sum = SumOp();
    // MulOp mul = MulOp();
    // DivOp div = DivOp();

    // shared_ptr<SymbolContainerBase> sumContainer = make_shared<SymbolContainer<SumOp>>(sum);
    // shared_ptr<SymbolContainerBase> mulContainer = make_shared<SymbolContainer<MulOp>>(mul);
    // shared_ptr<SymbolContainerBase> divContainer = make_shared<SymbolContainer<DivOp>>(div);

    
    // vector<shared_ptr<SymbolContainerBase>> containers;

    // containers.push_back(sumContainer);
    // containers.push_back(mulContainer);
    // containers.push_back(divContainer);

    // containers = { sumContainer, mulContainer, divContainer };

    // Expression expression = Expression(containers);

    Expression expression = Expression();

    ExpressionBuilder builder = ExpressionBuilder();

    shared_ptr<SymbolContainerBase> root = builder.buildSymbol(true, '+');
    shared_ptr<SymbolContainerBase> lhs = builder.buildSymbol(true, '3');
    shared_ptr<SymbolContainerBase> rhs = builder.buildSymbol(true, 'x');

    expression.addNode(root);
    expression.addNode(lhs);
    expression.addNode(rhs);

    string result = expression.toString();

    return true;
}