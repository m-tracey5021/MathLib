
#include "../Parsing/mParser.h"

bool testDataAllocation(){
    
}

bool testMParse(){

    MParser parser;
    vector<string> expressions = {
        "x+y+z",
        "x+(y+z)",
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

    for (string exp : expressions){
        for (int i = 0; i < exp.size(); i ++){
            Scope ithScope = parser.findScope(i, exp);
            scopes.push_back(ithScope);
        }
    }

    return false;
}