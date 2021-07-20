#include "expression.h"

Expression::Expression(){}

Expression::Expression(vector<shared_ptr<SymbolContainerBase>> tree): tree(tree){}

string Expression::toString()
{
    string result = "";

    for (shared_ptr<SymbolContainerBase> container : tree)
    {
        result += container->toString();
    }
    
    return result;
}
