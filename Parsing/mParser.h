#include "../Algebra3/expressionTree.h"
#include "../Algebra3/symbol.h"
#include "../Algebra3/operation.h"
#include "../Algebra3/sumOp.h"
#include "../Algebra3/mulOp.h"
#include "../Algebra3/divOp.h"
#include "../Algebra3/auxOp.h"
#include "../Algebra3/exponent.h"
#include "../Algebra3/radical.h"
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
    Atomic,
    None

};

enum class AuxilliaryRelation {
    Target,
    Exponent,
    Radical,
    None
};

struct OpInfo {

    char op;

    pair<int, int> between;

    OpInfo(): op('~'), between{0, 0}{}

    OpInfo(char op, int lhsBetween, int rhsBetween): op(op), between{lhsBetween, rhsBetween}{}

};

struct AuxOpInfo {

    char op;

    int start;

    int end;

    AuxOpInfo(): op('~'), start(0), end(0){}

    AuxOpInfo(char op, int start, int end): op(op), start(start), end(end){}

};

struct Scope {

    ScopeType type;

    vector<OpInfo> ops;

    vector<string> operands;
    
    bool sign;

    int start;

    int end;

    Scope(): type(ScopeType::None), sign(true), start(0), end(0){}

    Scope(int start, int end): sign(true), start(start), end(end){}

    void appendOperator(char op, int lhs, int rhs){
        OpInfo opWithinScope(op, lhs, rhs);
        ops.push_back(opWithinScope);
    }

    // void addAuxillary(char op, int start, int end){
    //     AuxOpInfo auxillary(op, start, end);
    //     auxOps.push_back(auxillary);
    // }
    

};





class MParser {

    private:

        Expression parseTree;

    public:

        MParser();

        Expression getParseTree();

        bool isOpeningBracket(char bracket);

        bool isClosingBracket(char bracket);

        bool isVariable(string expression, int start, int end);

        bool isConstant(string expression, int start, int end);

        bool isAtomic(string expression, int start, int end);

        string sanitise(string expression, string expressionType);

        unique_ptr<Symbol> buildSymbol(Scope scope, string expression);

        unique_ptr<Symbol> buildAtom(string s);

        unique_ptr<Operation> buildOperation(ScopeType type);

        unique_ptr<Operation> buildOperation(char c);

        unique_ptr<AuxOp> buildAuxOperation(char c, string expression);

        unique_ptr<AuxOp> buildAuxOperationChain(vector<AuxOpInfo>& auxillaries, string expression);

        void setSymbolAsAuxillary(unique_ptr<Symbol>& symbol, AuxilliaryRelation relation);

        void parseExpression(string expression);

        void parseExpression(unique_ptr<Symbol>& parent, AuxilliaryRelation parentRelation, string expression);

        void parseEquation(string equation);

        void parseFunction(string function);
        
        int findAuxOpApplicability(int auxOpStart, int auxOpEnd, int expressionMinMax, bool& cont);

        int findMatchingBracket(int i, string expression);

        Scope scopeExpression(int i, string expression);

        Scope scopeTerm(int i, string expression);

        Scope scopeRational(int i, string expression);

        Scope scopeConstant(int i, string expression);

        Scope findScope(int i, string expression);

        Scope findMainScope(string expression);

        Scope scopeAuxOp(int i, string expression);

        // vector<AuxOpInfo> scopeAuxOp(int i, string expression);

        // vector<AuxOpInfo> scopeAuxOp(Scope parentScope, string expression);

        vector<string> separateOperands(Scope& scope, string expression);

        pair<string, vector<string>> separateAuxillaries(Scope& scope, string expression);
        
};
