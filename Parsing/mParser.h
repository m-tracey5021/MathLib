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
#include "../Algebra3/constantElement.h"
#include "../Algebra3/variableElement.h"
#include <vector>
#include <string>
#include <utility>


using std::vector;
using std::string;
using std::pair;

// struct Scope {
//     int start;
//     int end;
//     char op;
// };

class MParser {

    private:

        ExpressionTree parseTree;

    public:

        MParser();

        unique_ptr<Symbol> buildSymbol(char c);

        void parseExpression(string expression);

        void parseEquation(string equation);

        void parseFunction(string function);

        int findMatchingBracket(int i, string expression);

        vector<int> findSurroundingBrackets(int i, string expression);

        vector<int> scopeLowPriorityOp(int i, string expression);

        vector<int> scopeHighPriorityOp(int i, string expression);

        // vector<int> scopeOfDivOp(int i, string expression);

        vector<int> scopeAuxOp(int i, string expression);

        Scope findScope(int i, string expression);
        
};