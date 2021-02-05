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

        void getAllSubTerms(vector<unique_ptr<Expression>>& terms,
                                vector<unique_ptr<Expression>>& subTerms,
                                int start,
                                int end);

        //  === Virtual methods ===

        // Get

        virtual int* getValue() = 0;

        virtual vector<unique_ptr<Expression>> getContent() = 0;

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

        virtual unique_ptr<Expression> sum(Summation s) = 0;
        virtual unique_ptr<Expression> sum(Multiplication m) = 0;
        virtual unique_ptr<Expression> sum(Division d) = 0;
        virtual unique_ptr<Expression> sum(ConstantExpression c) = 0;
        virtual unique_ptr<Expression> sum(VariableExpression v) = 0;

        virtual unique_ptr<Expression> multiply(Summation s) = 0;
        virtual unique_ptr<Expression> multiply(Multiplication m) = 0;
        virtual unique_ptr<Expression> multiply(Division d) = 0;
        virtual unique_ptr<Expression> multiply(ConstantExpression c) = 0;
        virtual unique_ptr<Expression> multiply(VariableExpression v) = 0;

        virtual unique_ptr<Expression> divide(Summation s) = 0;
        virtual unique_ptr<Expression> divide(Multiplication m) = 0;
        virtual unique_ptr<Expression> divide(Division d) = 0;
        virtual unique_ptr<Expression> divide(ConstantExpression c) = 0;
        virtual unique_ptr<Expression> divide(VariableExpression v) = 0;

        virtual unique_ptr<Expression> mergeMultiplications(Expression& e) = 0;

        virtual unique_ptr<Expression> expandForExponent() = 0;

        virtual unique_ptr<Expression> expandAsExponent(Expression& baseExpression) = 0;

        virtual unique_ptr<Expression> expandAsConstNum(Expression& baseExpression, Division& baseDivision) = 0;

        virtual unique_ptr<Expression> expandAsNegativeExponent(Expression& baseExpression) = 0;

        virtual unique_ptr<Expression> factor() = 0;

        virtual vector<unique_ptr<Expression>> getConstantFactors() = 0;

        virtual vector<unique_ptr<Expression>> getAllFactors() = 0;

        // Misc

        virtual unique_ptr<Expression> copy() = 0;

        //virtual unique_ptr<Expression> reassign() = 0;

        //virtual unique_ptr<Expression> shallowCopy() = 0;

        //virtual unique_ptr<Expression> deepCopy() = 0;

        virtual string toString() = 0;

        virtual string exponentToString() = 0;




};

class Summation : public Expression {

    private:

        vector<unique_ptr<Expression>> operands;

    public:

        Summation();

        Summation(bool sign, unique_ptr<Expression>& root, unique_ptr<Expression>& exponent, vector<unique_ptr<Expression>>& operands);

        ~Summation();

        vector<unique_ptr<Expression>> getOperands();

        void setOperands(vector<unique_ptr<Expression>> o);

        // Overrides

        // Get

        int* getValue() override;

        vector<unique_ptr<Expression>> getContent() override;

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

        unique_ptr<Expression> sum(Summation s) override;
        unique_ptr<Expression> sum(Multiplication m) override;
        unique_ptr<Expression> sum(Division d) override;
        unique_ptr<Expression> sum(ConstantExpression c) override;
        unique_ptr<Expression> sum(VariableExpression v) override;

        unique_ptr<Expression> multiply(Summation s) override;
        unique_ptr<Expression> multiply(Multiplication m) override;
        unique_ptr<Expression> multiply(Division d) override;
        unique_ptr<Expression> multiply(ConstantExpression c) override;
        unique_ptr<Expression> multiply(VariableExpression v) override;

        unique_ptr<Expression> divide(Summation s) override;
        unique_ptr<Expression> divide(Multiplication m) override;
        unique_ptr<Expression> divide(Division d) override;
        unique_ptr<Expression> divide(ConstantExpression c) override;
        unique_ptr<Expression> divide(VariableExpression v) override;

        unique_ptr<Expression> mergeMultiplications(Expression& e) override;

        unique_ptr<Expression> expandForExponent() override;

        unique_ptr<Expression> expandAsExponent(Expression& baseExpression) override;

        unique_ptr<Expression> expandAsConstNum(Expression& baseExpression, Division& baseDivision) override;

        unique_ptr<Expression> expandAsNegativeExponent(Expression& baseExpression) override;

        unique_ptr<Expression> factor() override;

        vector<unique_ptr<Expression>> getConstantFactors() override;

        vector<unique_ptr<Expression>> getAllFactors() override;

        // Misc

        unique_ptr<Expression> copy() override;

        //unique_ptr<Expression> shallowCopy() override;

        string toString() override;

        string exponentToString() override;

};

class Multiplication : public Expression {

    private:

        vector<unique_ptr<Expression>> operands;

    public:

        Multiplication();

        Multiplication(bool sign, unique_ptr<Expression>& root, unique_ptr<Expression>& exponent, vector<unique_ptr<Expression>>& operands);

        ~Multiplication();

        vector<unique_ptr<Expression>> getOperands();

        void setOperands(vector<unique_ptr<Expression>> operands);

        // Overrides

        // Get

        int* getValue() override;

        vector<unique_ptr<Expression>> getContent() override;

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

        unique_ptr<Expression> sum(Summation s) override;
        unique_ptr<Expression> sum(Multiplication m) override;
        unique_ptr<Expression> sum(Division d) override;
        unique_ptr<Expression> sum(ConstantExpression c) override;
        unique_ptr<Expression> sum(VariableExpression v) override;

        unique_ptr<Expression> multiply(Summation s) override;
        unique_ptr<Expression> multiply(Multiplication m) override;
        unique_ptr<Expression> multiply(Division d) override;
        unique_ptr<Expression> multiply(ConstantExpression c) override;
        unique_ptr<Expression> multiply(VariableExpression v) override;

        unique_ptr<Expression> divide(Summation s) override;
        unique_ptr<Expression> divide(Multiplication m) override;
        unique_ptr<Expression> divide(Division d) override;
        unique_ptr<Expression> divide(ConstantExpression c) override;
        unique_ptr<Expression> divide(VariableExpression v) override;

        unique_ptr<Expression> mergeMultiplications(Expression& e) override;

        unique_ptr<Expression> expandForExponent() override;

        unique_ptr<Expression> expandAsExponent(Expression& baseExpression) override;

        unique_ptr<Expression> expandAsConstNum(Expression& baseExpression, Division& baseDivision) override;

        unique_ptr<Expression> expandAsNegativeExponent(Expression& baseExpression) override;

        unique_ptr<Expression> factor() override;

        vector<unique_ptr<Expression>> getConstantFactors() override;

        vector<unique_ptr<Expression>> getAllFactors() override;

        // Misc

        unique_ptr<Expression> copy() override;

        string toString() override;

        string exponentToString() override;
    
};

class Division : public Expression {

    private:

        unique_ptr<Expression> numerator;

        unique_ptr<Expression> denominator;

    public:

        Division();

        Division(bool sign, unique_ptr<Expression>& root, unique_ptr<Expression>& exponent, unique_ptr<Expression>& numerator, unique_ptr<Expression>& denominator);

        ~Division();

        unique_ptr<Expression> getNumerator();

        unique_ptr<Expression> getDenominator();

        void setNumerator(Expression* n);

        void setDenominator(Expression* d);

        // Overrides

        // Get

        int* getValue() override;

        vector<unique_ptr<Expression>> getContent() override;

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

        unique_ptr<Expression> sum(Summation s) override;
        unique_ptr<Expression> sum(Multiplication m) override;
        unique_ptr<Expression> sum(Division d) override;
        unique_ptr<Expression> sum(ConstantExpression c) override;
        unique_ptr<Expression> sum(VariableExpression v) override;

        unique_ptr<Expression> multiply(Summation s) override;
        unique_ptr<Expression> multiply(Multiplication m) override;
        unique_ptr<Expression> multiply(Division d) override;
        unique_ptr<Expression> multiply(ConstantExpression c) override;
        unique_ptr<Expression> multiply(VariableExpression v) override;

        unique_ptr<Expression> divide(Summation s) override;
        unique_ptr<Expression> divide(Multiplication m) override;
        unique_ptr<Expression> divide(Division d) override;
        unique_ptr<Expression> divide(ConstantExpression c) override;
        unique_ptr<Expression> divide(VariableExpression v) override;

        unique_ptr<Expression> mergeMultiplications(Expression& e) override;

        unique_ptr<Expression> expandForExponent() override;

        unique_ptr<Expression> expandAsExponent(Expression& baseExpression) override;

        unique_ptr<Expression> expandAsConstNum(Expression& baseExpression, Division& baseDivision) override;

        unique_ptr<Expression> expandAsNegativeExponent(Expression& baseExpression) override;

        unique_ptr<Expression> factor() override;

        vector<unique_ptr<Expression>> getConstantFactors() override;

        vector<unique_ptr<Expression>> getAllFactors() override;

        // Misc

        unique_ptr<Expression> copy() override;

        string toString() override;

        string exponentToString() override;

};

class ConstantExpression : public Expression {

    private:

        int constant;

    public:

        ConstantExpression();

        ConstantExpression(bool sign, unique_ptr<Expression>& root, unique_ptr<Expression>& exponent, int constant);

        ~ConstantExpression();

        int getConstant();

        void setConstant(int c);

        // Overrides

        // Get

        int* getValue() override;

        vector<unique_ptr<Expression>> getContent() override;

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

        unique_ptr<Expression> sum(Summation s) override;
        unique_ptr<Expression> sum(Multiplication m) override;
        unique_ptr<Expression> sum(Division d) override;
        unique_ptr<Expression> sum(ConstantExpression c) override;
        unique_ptr<Expression> sum(VariableExpression v) override;

        unique_ptr<Expression> multiply(Summation s) override;
        unique_ptr<Expression> multiply(Multiplication m) override;
        unique_ptr<Expression> multiply(Division d) override;
        unique_ptr<Expression> multiply(ConstantExpression c) override;
        unique_ptr<Expression> multiply(VariableExpression v) override;

        unique_ptr<Expression> divide(Summation s) override;
        unique_ptr<Expression> divide(Multiplication m) override;
        unique_ptr<Expression> divide(Division d) override;
        unique_ptr<Expression> divide(ConstantExpression c) override;
        unique_ptr<Expression> divide(VariableExpression v) override;

        unique_ptr<Expression> mergeMultiplications(Expression& e) override;

        unique_ptr<Expression> expandForExponent() override;

        unique_ptr<Expression> expandAsExponent(Expression& baseExpression) override;

        unique_ptr<Expression> expandAsConstNum(Expression& baseExpression, Division& baseDivision) override;

        unique_ptr<Expression> expandAsNegativeExponent(Expression& baseExpression) override;

        unique_ptr<Expression> factor() override;

        vector<unique_ptr<Expression>> getConstantFactors() override;

        vector<unique_ptr<Expression>> getAllFactors() override;

        // Misc

        unique_ptr<Expression> copy() override;

        string toString() override;

        string exponentToString() override;

};

class VariableExpression : public Expression {

    private:

        char variable;

    public:

        VariableExpression();

        VariableExpression(bool sign, unique_ptr<Expression>& root, unique_ptr<Expression>& exponent, char variable);

        ~VariableExpression();

        char getVariable();

        void setVariable(char v);

        // Overrides

        // Get

        int* getValue() override;

        vector<unique_ptr<Expression>> getContent() override;

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

        unique_ptr<Expression> sum(Summation s) override;
        unique_ptr<Expression> sum(Multiplication m) override;
        unique_ptr<Expression> sum(Division d) override;
        unique_ptr<Expression> sum(ConstantExpression c) override;
        unique_ptr<Expression> sum(VariableExpression v) override;

        unique_ptr<Expression> multiply(Summation s) override;
        unique_ptr<Expression> multiply(Multiplication m) override;
        unique_ptr<Expression> multiply(Division d) override;
        unique_ptr<Expression> multiply(ConstantExpression c) override;
        unique_ptr<Expression> multiply(VariableExpression v) override;

        unique_ptr<Expression> divide(Summation s) override;
        unique_ptr<Expression> divide(Multiplication m) override;
        unique_ptr<Expression> divide(Division d) override;
        unique_ptr<Expression> divide(ConstantExpression c) override;
        unique_ptr<Expression> divide(VariableExpression v) override;

        unique_ptr<Expression> mergeMultiplications(Expression& e) override;

        unique_ptr<Expression> expandForExponent() override;

        unique_ptr<Expression> expandAsExponent(Expression& baseExpression) override;

        unique_ptr<Expression> expandAsConstNum(Expression& baseExpression, Division& baseDivision) override;

        unique_ptr<Expression> expandAsNegativeExponent(Expression& baseExpression) override;

        unique_ptr<Expression> factor() override;

        vector<unique_ptr<Expression>> getConstantFactors() override;

        vector<unique_ptr<Expression>> getAllFactors() override;

        // Misc

        unique_ptr<Expression> copy() override;

        string toString() override;

        string exponentToString() override;
};

