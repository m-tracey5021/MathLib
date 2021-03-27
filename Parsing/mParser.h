#include "../Algebra3/expressionTree.h"
#include "../Algebra3/symbol.h"
#include "../Algebra3/operation.h"
#include "../Algebra3/sumOp.h"
#include "../Algebra3/mulOp.h"
#include "../Algebra3/divOp.h"
#include "../Algebra3/auxOp.h"
#include "../Algebra3/exponent.h"
#include "../Algebra3/root.h"
#include "../Algebra3/function.h"
#include "../Algebra3/constant.h"
#include "../Algebra3/variable.h"
#include "../Algebra3/expression.h"
#include <vector>
#include <string>
#include <utility>

using std::vector;
using std::string;
using std::pair;

enum class ScopeType { 

    Summation,
    Multiplication,
    Division,
    Exponent,
    Radical,
    Atomic

};

struct OpInfo {

    char op;

    pair<int, int> between;

    OpInfo(){}

    OpInfo(char op, int lhsBetween, int rhsBetween): op(op), between{lhsBetween, rhsBetween}{}

};

struct Scope {

    ScopeType type;

    vector<OpInfo> ops;

    int start;

    int end;

    Scope(): start(0), end(0){}

    Scope(int start, int end): start(start), end(end){}

    void appendOperator(char op, int lhs, int rhs){
        OpInfo opWithinScope(op, lhs, rhs);
        ops.push_back(opWithinScope);
    }

};



class MParser {

    private:

        Expression parseTree;

    public:

        MParser();

        unique_ptr<Operation> buildOperation(char c);

        unique_ptr<AuxOp> buildAuxOperation(char c);

        void parseExpression(unique_ptr<Symbol>& parentSymbol, string expression);

        void parseEquation(string equation);

        void parseFunction(string function);

        int findMatchingBracket(int i, string expression);

        Scope scopeExpression(int i, string expression);

        Scope scopeTerm(int i, string expression);

        Scope scopeRational(int i, string expression);

        Scope scopeAuxOp(int i, string expression);

        Scope scopeConstant(int i, string expression);

        Scope findScope(int i, string expression);

        Scope findMainScope(string expression);

        vector<string> separateOperands(Scope& scope, string expression);
        
};
