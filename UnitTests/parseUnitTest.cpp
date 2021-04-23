
#include "../Parsing/mParser.h"

bool testFindScope(){

    MParser parser;
    vector<string> expressions = {
        "2",
        "235",
        "2xyz",
        "2x+3y",
        "2x+376",
        "2x+7",
        "x+y+z",
        "x+(y+z)",
        "x+(y+z+a)",
        "xy+z",
        "2(x+y+z-1/2)",
        "xy/pq",
        "(t+2r)/(3er)",
        "2(2+3t)/4r",
        "c^{2}",
        "x+t^{2}",
        "(x+t)^{2}",
        "[2]v3",
        "[2]v2x",
        "[2]v(2x)",
        "[2x+3]v4",
        "[2x+4]v(4t+1/2)",
        "[2x+4]v4(t+1/2)",
        "xy^{2x}z",
        "(xy)^{2x}z",
        "x[2x]vyz",
        "x[2x]v(yz)"
    };

    vector<Scope> scopes;
    vector<Scope> mainScopes;

    for (string exp : expressions){
        for (int i = 0; i < exp.size(); i ++){
            Scope ithScope = parser.findScope(i, exp);
            scopes.push_back(ithScope);
        }
    }

    for (string exp: expressions){
        Scope ithMainScope = parser.findMainScope(exp);
        mainScopes.push_back(ithMainScope);
    }

    return false;
}

bool testSeparateOperands(){
    
    MParser parser;
    vector<string> expressions = {
        "2",
        "235",
        "2xyz",
        "2x+3y",
        "2x+376",
        "2x+7",
        "x+y+z",
        "x+(y+z)",
        "x+(y+z+a)",
        "xy+z",
        "2(x+y+z-1/2)",
        "xy/pq",
        "(t+2r)/(3er)",
        "2(2+3t)/4r",
        "c^{2}",
        "x+t^{2}",
        "(x+t)^{2}",
        "[2]v3",
        "[2]v2x",
        "[2]v(2x)",
        "[2x+3]v4",
        "[2x+4]v(4t+1/2)",
        "[2x+4]v4(t+1/2)",
        "xy^{2x}z",
        "(xy)^{2x}z",
        "x[2x]vyz",
        "x[2x]v(yz)"
    };

    vector<vector<string>> operandsPerExp;

    for(string exp : expressions){
        Scope mainScope = parser.findMainScope(exp);
        vector<string> operands = parser.separateOperands(mainScope, exp);
        operandsPerExp.push_back(operands);
    }

    return false;
}

bool testParseExpression(){

    MParser parser;
    vector<string> expressions = {
        // "2",
        // "235",
        // "2xyz",
        // "2x+3y",
        // "2x+376",
        // "2x+7",
        // "x+y",
        // "x+y+z",
        // "x+(y+z)",
        // "x+(y+z+a)",
        // "xy+z",
        // "2(x+y+z-1/2)",
        // "xy/pq",
        // "(t+2r)/(3er)",
        // "2(2+3t)/4r",
        // "c^{2}",
        // "x+t^{2}",
        // "(x+t)^{2}",
        // "[2]v3",
        // "[2]v2x",
        // "[2]v(2x)",
        // "[2x+3]v4",
        // "[2x+4]v(4t+1/2)",
        // "[2x+4]v4(t+1/2)",
        // "xy^{2x}z",
        // "(xy)^{2x}z",
        // "x[2x]vyz",
        // "x[2x]v(yz)",
        "x^{2}^{3}",
        "(x^{2})^{3}",
        "(2x+t)^{3x}^{4r-2t}"
    };

    for (string exp : expressions){
        parser.parseExpression(exp);
        string parseTreeStr = parser.getParseTree().toString();
    }
    
    return false;
    
}