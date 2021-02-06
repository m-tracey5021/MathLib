#pragma once

#include "expressionDeclarations.h"
#include "expressionContainer.h"
#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::move;

// #define up unique_ptr
// #define mup make_unique

class Expression {

    protected:

        bool sign;

        ExpressionContainer root;

        ExpressionContainer exponent;

        ExpressionContainer parentExpression;

        string expressionString;

    public:

        Expression();

        Expression(bool sign, ExpressionContainer& root, ExpressionContainer& exponent);

        virtual ~Expression();

        bool getSign();

        ExpressionContainer getRoot();

        ExpressionContainer getExponent();

        ExpressionContainer getParentExpression();

        string getExpressionString();

        void setSign(bool s);

        void setRoot(ExpressionContainer& e);

        void setExponent(ExpressionContainer& e);

        void setParentExpression(ExpressionContainer& e);

        void updateExpressionString();

        void getAllSubTerms(vector<ExpressionContainer>& terms,
                                vector<ExpressionContainer>& subTerms,
                                int start,
                                int end);

        //  === Virtual methods ===

        // Get

        virtual int* getValue() = 0;

        virtual vector<ExpressionContainer> getContent() = 0;

        // Append/Remove/Replace

        virtual void appendExpression(Expression& e) = 0;

        virtual void removeExpression(int i) = 0;

        virtual void replaceExpression(int i, Expression& e) = 0;

        // Clean

        virtual void sanitise() = 0;

        // Test

        virtual bool isEqual(Expression& other) = 0;

        virtual bool isEqual(Summation& other) = 0;

        virtual bool isEqual(Multiplication& other) = 0;

        virtual bool isEqual(Division& other) = 0;

        virtual bool isEqual(ConstantExpression& other) = 0;

        virtual bool isEqual(VariableExpression& other) = 0;

        virtual bool isOne() = 0;

        virtual bool isAtomic() = 0;

        virtual bool isAtomicExponent() = 0;

        virtual bool isAtomicNumerator() = 0;

        virtual bool isLikeExpression(Expression& e) = 0;

        virtual bool isMergeable() = 0;

        // Manipulate

        virtual ExpressionContainer sum(Summation s) = 0;
        virtual ExpressionContainer sum(Multiplication m) = 0;
        virtual ExpressionContainer sum(Division d) = 0;
        virtual ExpressionContainer sum(ConstantExpression c) = 0;
        virtual ExpressionContainer sum(VariableExpression v) = 0;

        virtual ExpressionContainer multiply(Summation s) = 0;
        virtual ExpressionContainer multiply(Multiplication m) = 0;
        virtual ExpressionContainer multiply(Division d) = 0;
        virtual ExpressionContainer multiply(ConstantExpression c) = 0;
        virtual ExpressionContainer multiply(VariableExpression v) = 0;

        virtual ExpressionContainer divide(Summation s) = 0;
        virtual ExpressionContainer divide(Multiplication m) = 0;
        virtual ExpressionContainer divide(Division d) = 0;
        virtual ExpressionContainer divide(ConstantExpression c) = 0;
        virtual ExpressionContainer divide(VariableExpression v) = 0;

        virtual ExpressionContainer mergeMultiplications(Expression& e) = 0;

        virtual ExpressionContainer expandForExponent() = 0;

        virtual ExpressionContainer expandAsExponent(Expression& baseExpression) = 0;

        virtual ExpressionContainer expandAsConstNum(Expression& baseExpression, Division& baseDivision) = 0;

        virtual ExpressionContainer expandAsNegativeExponent(Expression& baseExpression) = 0;

        virtual ExpressionContainer factor() = 0;

        virtual vector<ExpressionContainer> getConstantFactors() = 0;

        virtual vector<ExpressionContainer> getAllFactors() = 0;

        // Misc

        virtual ExpressionContainer copy() = 0;

        //virtual ExpressionContainer reassign() = 0;

        //virtual ExpressionContainer shallowCopy() = 0;

        //virtual ExpressionContainer deepCopy() = 0;

        virtual string toString() = 0;

        virtual string exponentToString() = 0;




};

class Summation : public Expression {

    private:

        vector<ExpressionContainer> operands;

    public:

        Summation();

        Summation(bool sign, ExpressionContainer& root, ExpressionContainer& exponent, vector<ExpressionContainer>& operands);

        ~Summation();

        vector<ExpressionContainer> getOperands();

        void setOperands(vector<ExpressionContainer> o);

        // Overrides

        // Get

        int* getValue() override;

        vector<ExpressionContainer> getContent() override;

        // Append/Remove/Replace

        void appendExpression(Expression& e) override;

        void removeExpression(int i) override;

        void replaceExpression(int i, Expression& e) override;

        // Clean

        void sanitise() override;

        // Test

        bool isEqual(Expression& other) override;

        bool isEqual(Summation& other) override;

        bool isEqual(Multiplication& other) override;

        bool isEqual(Division& other) override;

        bool isEqual(ConstantExpression& other) override;

        bool isEqual(VariableExpression& other) override;

        bool isOne() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeExpression(Expression& e) override;

        bool isMergeable() override;

        // Manipulate

        ExpressionContainer sum(Summation s) override;
        ExpressionContainer sum(Multiplication m) override;
        ExpressionContainer sum(Division d) override;
        ExpressionContainer sum(ConstantExpression c) override;
        ExpressionContainer sum(VariableExpression v) override;

        ExpressionContainer multiply(Summation s) override;
        ExpressionContainer multiply(Multiplication m) override;
        ExpressionContainer multiply(Division d) override;
        ExpressionContainer multiply(ConstantExpression c) override;
        ExpressionContainer multiply(VariableExpression v) override;

        ExpressionContainer divide(Summation s) override;
        ExpressionContainer divide(Multiplication m) override;
        ExpressionContainer divide(Division d) override;
        ExpressionContainer divide(ConstantExpression c) override;
        ExpressionContainer divide(VariableExpression v) override;

        ExpressionContainer mergeMultiplications(Expression& e) override;

        ExpressionContainer expandForExponent() override;

        ExpressionContainer expandAsExponent(Expression& baseExpression) override;

        ExpressionContainer expandAsConstNum(Expression& baseExpression, Division& baseDivision) override;

        ExpressionContainer expandAsNegativeExponent(Expression& baseExpression) override;

        ExpressionContainer factor() override;

        vector<ExpressionContainer> getConstantFactors() override;

        vector<ExpressionContainer> getAllFactors() override;

        // Misc

        ExpressionContainer copy() override;

        //ExpressionContainer shallowCopy() override;

        string toString() override;

        string exponentToString() override;

};

class Multiplication : public Expression {

    private:

        vector<ExpressionContainer> operands;

    public:

        Multiplication();

        Multiplication(bool sign, ExpressionContainer& root, ExpressionContainer& exponent, vector<ExpressionContainer>& operands);

        ~Multiplication();

        vector<ExpressionContainer> getOperands();

        void setOperands(vector<ExpressionContainer> operands);

        // Overrides

        // Get

        int* getValue() override;

        vector<ExpressionContainer> getContent() override;

        // Append/Remove/Replace

        void appendExpression(Expression& e) override;

        void removeExpression(int i) override;

        void replaceExpression(int i, Expression& e) override;

        // Clean

        void sanitise() override;

        // Test

        bool isEqual(Expression& other) override;

        bool isEqual(Summation& other) override;

        bool isEqual(Multiplication& other) override;

        bool isEqual(Division& other) override;

        bool isEqual(ConstantExpression& other) override;

        bool isEqual(VariableExpression& other) override;

        bool isOne() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeExpression(Expression& e) override;

        bool isMergeable() override;

        // Manipulate

        ExpressionContainer sum(Summation s) override;
        ExpressionContainer sum(Multiplication m) override;
        ExpressionContainer sum(Division d) override;
        ExpressionContainer sum(ConstantExpression c) override;
        ExpressionContainer sum(VariableExpression v) override;

        ExpressionContainer multiply(Summation s) override;
        ExpressionContainer multiply(Multiplication m) override;
        ExpressionContainer multiply(Division d) override;
        ExpressionContainer multiply(ConstantExpression c) override;
        ExpressionContainer multiply(VariableExpression v) override;

        ExpressionContainer divide(Summation s) override;
        ExpressionContainer divide(Multiplication m) override;
        ExpressionContainer divide(Division d) override;
        ExpressionContainer divide(ConstantExpression c) override;
        ExpressionContainer divide(VariableExpression v) override;

        ExpressionContainer mergeMultiplications(Expression& e) override;

        ExpressionContainer expandForExponent() override;

        ExpressionContainer expandAsExponent(Expression& baseExpression) override;

        ExpressionContainer expandAsConstNum(Expression& baseExpression, Division& baseDivision) override;

        ExpressionContainer expandAsNegativeExponent(Expression& baseExpression) override;

        ExpressionContainer factor() override;

        vector<ExpressionContainer> getConstantFactors() override;

        vector<ExpressionContainer> getAllFactors() override;

        // Misc

        ExpressionContainer copy() override;

        string toString() override;

        string exponentToString() override;
    
};

class Division : public Expression {

    private:

        ExpressionContainer numerator;

        ExpressionContainer denominator;

    public:

        Division();

        Division(bool sign, ExpressionContainer& root, ExpressionContainer& exponent, ExpressionContainer& numerator, ExpressionContainer& denominator);

        ~Division();

        ExpressionContainer getNumerator();

        ExpressionContainer getDenominator();

        void setNumerator(Expression* n);

        void setDenominator(Expression* d);

        // Overrides

        // Get

        int* getValue() override;

        vector<ExpressionContainer> getContent() override;

        // Append/Remove/Replace

        void appendExpression(Expression& e) override;

        void removeExpression(int i) override;

        void replaceExpression(int i, Expression& e) override;

        // Clean

        void sanitise() override;

        // Test

        bool isEqual(Expression& other) override;

        bool isEqual(Summation& other) override;

        bool isEqual(Multiplication& other) override;

        bool isEqual(Division& other) override;

        bool isEqual(ConstantExpression& other) override;

        bool isEqual(VariableExpression& other) override;

        bool isOne() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeExpression(Expression& e) override;

        bool isMergeable() override;

        // Manipulate

        ExpressionContainer sum(Summation s) override;
        ExpressionContainer sum(Multiplication m) override;
        ExpressionContainer sum(Division d) override;
        ExpressionContainer sum(ConstantExpression c) override;
        ExpressionContainer sum(VariableExpression v) override;

        ExpressionContainer multiply(Summation s) override;
        ExpressionContainer multiply(Multiplication m) override;
        ExpressionContainer multiply(Division d) override;
        ExpressionContainer multiply(ConstantExpression c) override;
        ExpressionContainer multiply(VariableExpression v) override;

        ExpressionContainer divide(Summation s) override;
        ExpressionContainer divide(Multiplication m) override;
        ExpressionContainer divide(Division d) override;
        ExpressionContainer divide(ConstantExpression c) override;
        ExpressionContainer divide(VariableExpression v) override;

        ExpressionContainer mergeMultiplications(Expression& e) override;

        ExpressionContainer expandForExponent() override;

        ExpressionContainer expandAsExponent(Expression& baseExpression) override;

        ExpressionContainer expandAsConstNum(Expression& baseExpression, Division& baseDivision) override;

        ExpressionContainer expandAsNegativeExponent(Expression& baseExpression) override;

        ExpressionContainer factor() override;

        vector<ExpressionContainer> getConstantFactors() override;

        vector<ExpressionContainer> getAllFactors() override;

        // Misc

        ExpressionContainer copy() override;

        string toString() override;

        string exponentToString() override;

};

class ConstantExpression : public Expression {

    private:

        int constant;

    public:

        ConstantExpression();

        ConstantExpression(bool sign, ExpressionContainer& root, ExpressionContainer& exponent, int constant);

        ~ConstantExpression();

        int getConstant();

        void setConstant(int c);

        // Overrides

        // Get

        int* getValue() override;

        vector<ExpressionContainer> getContent() override;

        // Append/Remove/Replace

        void appendExpression(Expression& e) override;

        void removeExpression(int i) override;

        void replaceExpression(int i, Expression& e) override;

        // Clean

        void sanitise() override;

        // Test

        bool isEqual(Expression& other) override;

        bool isEqual(Summation& other) override;

        bool isEqual(Multiplication& other) override;

        bool isEqual(Division& other) override;

        bool isEqual(ConstantExpression& other) override;

        bool isEqual(VariableExpression& other) override;

        bool isOne() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeExpression(Expression& e) override;

        bool isMergeable() override;

        // Manipulate

        ExpressionContainer sum(Summation s) override;
        ExpressionContainer sum(Multiplication m) override;
        ExpressionContainer sum(Division d) override;
        ExpressionContainer sum(ConstantExpression c) override;
        ExpressionContainer sum(VariableExpression v) override;

        ExpressionContainer multiply(Summation s) override;
        ExpressionContainer multiply(Multiplication m) override;
        ExpressionContainer multiply(Division d) override;
        ExpressionContainer multiply(ConstantExpression c) override;
        ExpressionContainer multiply(VariableExpression v) override;

        ExpressionContainer divide(Summation s) override;
        ExpressionContainer divide(Multiplication m) override;
        ExpressionContainer divide(Division d) override;
        ExpressionContainer divide(ConstantExpression c) override;
        ExpressionContainer divide(VariableExpression v) override;

        ExpressionContainer mergeMultiplications(Expression& e) override;

        ExpressionContainer expandForExponent() override;

        ExpressionContainer expandAsExponent(Expression& baseExpression) override;

        ExpressionContainer expandAsConstNum(Expression& baseExpression, Division& baseDivision) override;

        ExpressionContainer expandAsNegativeExponent(Expression& baseExpression) override;

        ExpressionContainer factor() override;

        vector<ExpressionContainer> getConstantFactors() override;

        vector<ExpressionContainer> getAllFactors() override;

        // Misc

        ExpressionContainer copy() override;

        string toString() override;

        string exponentToString() override;

};

class VariableExpression : public Expression {

    private:

        char variable;

    public:

        VariableExpression();

        VariableExpression(bool sign, ExpressionContainer& root, ExpressionContainer& exponent, char variable);

        ~VariableExpression();

        char getVariable();

        void setVariable(char v);

        // Overrides

        // Get

        int* getValue() override;

        vector<ExpressionContainer> getContent() override;

        // Append/Remove/Replace

        void appendExpression(Expression& e) override;

        void removeExpression(int i) override;

        void replaceExpression(int i, Expression& e) override;

        // Clean

        void sanitise() override;

        // Test

        bool isEqual(Expression& other) override;

        bool isEqual(Summation& other) override;

        bool isEqual(Multiplication& other) override;

        bool isEqual(Division& other) override;

        bool isEqual(ConstantExpression& other) override;

        bool isEqual(VariableExpression& other) override;

        bool isOne() override;

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeExpression(Expression& e) override;

        bool isMergeable() override;

        // Manipulate

        ExpressionContainer sum(Summation s) override;
        ExpressionContainer sum(Multiplication m) override;
        ExpressionContainer sum(Division d) override;
        ExpressionContainer sum(ConstantExpression c) override;
        ExpressionContainer sum(VariableExpression v) override;

        ExpressionContainer multiply(Summation s) override;
        ExpressionContainer multiply(Multiplication m) override;
        ExpressionContainer multiply(Division d) override;
        ExpressionContainer multiply(ConstantExpression c) override;
        ExpressionContainer multiply(VariableExpression v) override;

        ExpressionContainer divide(Summation s) override;
        ExpressionContainer divide(Multiplication m) override;
        ExpressionContainer divide(Division d) override;
        ExpressionContainer divide(ConstantExpression c) override;
        ExpressionContainer divide(VariableExpression v) override;

        ExpressionContainer mergeMultiplications(Expression& e) override;

        ExpressionContainer expandForExponent() override;

        ExpressionContainer expandAsExponent(Expression& baseExpression) override;

        ExpressionContainer expandAsConstNum(Expression& baseExpression, Division& baseDivision) override;

        ExpressionContainer expandAsNegativeExponent(Expression& baseExpression) override;

        ExpressionContainer factor() override;

        vector<ExpressionContainer> getConstantFactors() override;

        vector<ExpressionContainer> getAllFactors() override;

        // Misc

        ExpressionContainer copy() override;

        string toString() override;

        string exponentToString() override;
};

