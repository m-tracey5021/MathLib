#include "expression.h"
#include "expressionComponents.h"

#include <iostream>
#include <algorithm>

Expression::Expression(){}

Expression::Expression(vector<shared_ptr<SymbolContainerBase>> tree): tree(tree){}

int Expression::getNode(shared_ptr<SymbolContainerBase>& node)
{
    vector<shared_ptr<SymbolContainerBase>>::iterator it = std::find(tree.begin(), tree.end(), node);
    return std::distance(tree.begin(), it);
}

int Expression::getParent(shared_ptr<SymbolContainerBase>& node)
{
    int index = getNode(node);
    return parentMap.at(index);
}

vector<int> Expression::getChildren(shared_ptr<SymbolContainerBase>& node)
{
    int index = getNode(node);
    return childMap.at(index);
}

void Expression::addNode(shared_ptr<SymbolContainerBase>& root)
{

    tree.push_back(root);

    int parentIndex = -1;
    int childIndex = tree.size() - 1;

    parentMap[childIndex] = parentIndex;
    childMap[parentIndex].push_back(childIndex);
    
}

void Expression::addNode(shared_ptr<SymbolContainerBase>& parent, shared_ptr<SymbolContainerBase>& child)
{

    tree.push_back(child);

    int parentIndex = getNode(parent);
    int childIndex = tree.size() - 1;

    parentMap[childIndex] = parentIndex;
    childMap[parentIndex].push_back(childIndex);
    
}

void Expression::addNodes(shared_ptr<SymbolContainerBase>& parent, vector<shared_ptr<SymbolContainerBase>> children)
{
    for (shared_ptr<SymbolContainerBase>& child : children)
    {
        addNode(parent, child);
    }
}

string Expression::toString()
{
    string result = "";

    for (shared_ptr<SymbolContainerBase> container : tree)
    {
        result += container->toString();
    }
    
    return result;
}

shared_ptr<SymbolContainerBase> ExpressionBuilder::buildSymbol(bool sign, char symbol)
{
    if (symbol == '+' || symbol == '-')
    {
        SumOp sum = SumOp();
        shared_ptr<SymbolContainerBase> sumContainer = make_shared<SymbolContainer<SumOp>>(sum);
        return sumContainer;
    }
    else if (symbol == '*')
    {
        MulOp mul = MulOp();
        shared_ptr<SymbolContainerBase> mulContainer = make_shared<SymbolContainer<MulOp>>(mul);
        return mulContainer;
    }
    else if (symbol == '/')
    {
        DivOp div = DivOp();
        shared_ptr<SymbolContainerBase> divContainer = make_shared<SymbolContainer<DivOp>>(div);
        return divContainer;
    }
    else if (symbol == '^')
    {
        Exponent exp = Exponent();
        shared_ptr<SymbolContainerBase> expContainer = make_shared<SymbolContainer<Exponent>>(exp);
        return expContainer;
    }
    else if (symbol == 'v')
    {
        Radical rad = Radical();
        shared_ptr<SymbolContainerBase> radContainer = make_shared<SymbolContainer<Radical>>(rad);
        return radContainer;
    }
    else if (isalpha(symbol))
    {
        Variable var = Variable(symbol);
        shared_ptr<SymbolContainerBase> varContainer = make_shared<SymbolContainer<Variable>>(var);
        return varContainer;
    }
    else if (isdigit(symbol))
    {
        Constant con = Constant(symbol - '0');
        shared_ptr<SymbolContainerBase> conContainer = make_shared<SymbolContainer<Constant>>(con);
        return conContainer;
    }
    else
    {
        throw "Symbol not supported";
    }
}

void ExpressionBuilder::build()
{
    expression = Expression();
}

void ExpressionBuilder::plus(int constant)
{
    shared_ptr<SymbolContainerBase> container = buildSymbol(true, constant);
    expression.addNode(container);
}
