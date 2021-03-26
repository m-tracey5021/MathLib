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

enum class OpType { 
    Sum,
    Multiply,
    Divide
};

struct Scope {
    vector<pair<char, int>> ops;
    vector<pair<int, int>> operands;
    int start;
    int end;

    Scope(): start(0), end(0){}

};



class MParser {

    private:

        Expression parseTree;

    public:

        MParser();

        // unique_ptr<Symbol> buildSymbol(char c);

        void parseExpression(string expression);

        void parseEquation(string equation);

        void parseFunction(string function);

        int findMatchingBracket(int i, string expression);

        vector<int> findSurroundingBrackets(int i, string expression);

        void appendOperator(Scope scope, int i, string expression);

        Scope scopeLowPriorityOp(int i, string expression);

        Scope scopeHighPriorityOp(int i, string expression);

        Scope scopeAuxOp(int i, string expression);

        Scope findScope(int i, string expression);

        Scope findMainScope(string expression);

        

        vector<string> separateOperands(string expression);
        
};
