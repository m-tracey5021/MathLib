#pragma once

#include "term.h"
#include "termOperation.h"

class ComplexTerm : Term {
    private:
        Term* firstOperand;
        Term* secondOperand;
        TermOperation operation;
    public:
        ComplexTerm(){}
        ComplexTerm(Term* first, Term* second, TermOperation operation): 
            Term(),
            firstOperand(first),
            secondOperand(second),
            operation(operation){}
        Term* getFirst(){return firstOperand;}
        Term* getSecond(){return secondOperand;}
        TermOperation getOperation(){return operation;}

        void setFirst(Term* first){firstOperand = first;}
        void setSecond(Term* second){secondOperand = second;}
        void setOperation(TermOperation op){operation = op;}
};