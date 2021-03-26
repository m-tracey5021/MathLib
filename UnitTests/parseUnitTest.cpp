
#include "../Parsing/mParser.h"

bool testDataAllocation(){
    
}

bool testFindScope(){

    MParser parser;
    vector<string> expressions = {
        "x+y+z",
        "x+(y+z)",
        "x+(y+z+a)",
        "xy+z",
        "2(x+y+z-1/2)",
        "xy/pq",
        "(t+2r)/(3er)",
        "c^2|",
        "x+t^2|",
        "(x+t)^2|",
        "2(2+3t)/4r"
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
        "x+y+z",
        "x+(y+z)",
        "x+(y+z+a)",
        "xy+z",
        "2(x+y+z-1/2)",
        "xy/pq",
        "(t+2r)/(3er)",
        "c^2|",
        "x+t^2|",
        "(x+t)^2|",
        "2(2+3t)/4r"
    };

    vector<vector<string>> operandsPerExp;

    for(string exp : expressions){
        vector<string> operands = parser.separateOperands(exp);
        operandsPerExp.push_back(operands);
    }

    return false;
}