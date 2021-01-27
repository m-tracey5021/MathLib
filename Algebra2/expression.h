#pragma once

#include <string>
#include <vector>

class Summation;
class Multiplication;
class Division;
class Constant;
class Variable;

class Expression {

    protected:

        bool sign;

        Expression* root;

        Expression* exponent;

        Expression* parentExpression;

        std::string expressionString;

    public:

        Expression();

        Expression(bool sign, Expression* root, Expression* exponent);

        bool getSign();

        Expression& getRoot();

        Expression& getExponent();

        Expression& getParentExpression();

        std::string getExpressionString();

        //  === Virtual methods ===

        // Get

        virtual int* getValue() = 0;

        virtual std::vector<Expression> getContent() = 0;

        // Append/Remove/Replace

        virtual Expression& appendExpression(Expression& e) = 0;

        virtual void removeExpression(int i) = 0;

        virtual void replaceExpression(int i, Expression& e) = 0;

        // Clean

        virtual void sanitise() = 0;

        // Test

        virtual bool isAtomic() = 0;

        virtual bool isAtomicExponent() = 0;

        virtual bool isAtomicNumerator() = 0;

        virtual bool isLikeExpression(Expression& e) = 0;

        virtual bool isMergeable() = 0;

        // Manipulate

        virtual Expression& sum(Expression& e) = 0;

        virtual Expression& multiply(Expression& e) = 0;

        virtual Expression& divide(Expression& e) = 0;

        virtual Expression& mergeMultiplications(Expression& e) = 0;

        virtual Expression& expandForExponent() = 0;

        virtual Expression& expandAsExponent(Expression& baseExpression) = 0;

        virtual Expression& expandAsConstNum(Expression& baseExpression, Division baseDivision) = 0;

        virtual Expression& expandAsNegativeExponent(Expression& baseExpression) = 0;

        virtual Expression& factor() = 0;

        virtual std::vector<Expression> getConstantFactors() = 0;

        virtual std::vector<Expression> getAllFactors() = 0;

        // Misc

        virtual Expression& copy() = 0;

        virtual std::string toString() = 0;

        virtual std::string exponentToString() = 0;




};

class Summation : Expression {

    private:

        std::vector<Expression> operands;

    public:

        std::vector<Expression> getOperands();

        // Overrides

        // Get

        int* getValue() override;

        std::vector<Expression> getContent() override;

        // Append/Remove/Replace

        Expression& appendExpression(Expression& e) override;

        void removeExpression(int i) override;

        void replaceExpression(int i, Expression& e) override;

        // Clean

        void sanitise() override;

        // Test

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeExpression(Expression& e) override;

        bool isMergeable() override;

        // Manipulate

        Expression& sum(Expression& e) override;

        Expression& multiply(Expression& e) override;

        Expression& divide(Expression& e) override;

        Expression& mergeMultiplications(Expression& e) override;

        Expression& expandForExponent() override;

        Expression& expandAsExponent(Expression& baseExpression) override;

        Expression& expandAsConstNum(Expression& baseExpression, Division baseDivision) override;

        Expression& expandAsNegativeExponent(Expression& baseExpression) override;

        Expression& factor() override;

        std::vector<Expression> getConstantFactors() override;

        std::vector<Expression> getAllFactors() override;

        // Misc

        Expression& copy() override;

        std::string toString() override;

        std::string exponentToString() override;

};

class Multiplication : Expression {

    private:

        std::vector<Expression> operands;

    public:

        std::vector<Expression> getOperands();

        // Overrides

        // Get

        int* getValue() override;

        std::vector<Expression> getContent() override;

        // Append/Remove/Replace

        Expression& appendExpression(Expression& e) override;

        void removeExpression(int i) override;

        void replaceExpression(int i, Expression& e) override;

        // Clean

        void sanitise() override;

        // Test

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeExpression(Expression& e) override;

        bool isMergeable() override;

        // Manipulate

        Expression& sum(Expression& e) override;

        Expression& multiply(Expression& e) override;

        Expression& divide(Expression& e) override;

        Expression& mergeMultiplications(Expression& e) override;

        Expression& expandForExponent() override;

        Expression& expandAsExponent(Expression& baseExpression) override;

        Expression& expandAsConstNum(Expression& baseExpression, Division baseDivision) override;

        Expression& expandAsNegativeExponent(Expression& baseExpression) override;

        Expression& factor() override;

        std::vector<Expression> getConstantFactors() override;

        std::vector<Expression> getAllFactors() override;

        // Misc

        Expression& copy() override;

        std::string toString() override;

        std::string exponentToString() override;
    
};

class Division : Expression {

    private:

        Expression& numerator;

        Expression& denominator;

    public:

        Expression& getNumerator();

        Expression& getDenominator();

        // Overrides

        // Get

        int* getValue() override;

        std::vector<Expression> getContent() override;

        // Append/Remove/Replace

        Expression& appendExpression(Expression& e) override;

        void removeExpression(int i) override;

        void replaceExpression(int i, Expression& e) override;

        // Clean

        void sanitise() override;

        // Test

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeExpression(Expression& e) override;

        bool isMergeable() override;

        // Manipulate

        Expression& sum(Expression& e) override;

        Expression& multiply(Expression& e) override;

        Expression& divide(Expression& e) override;

        Expression& mergeMultiplications(Expression& e) override;

        Expression& expandForExponent() override;

        Expression& expandAsExponent(Expression& baseExpression) override;

        Expression& expandAsConstNum(Expression& baseExpression, Division baseDivision) override;

        Expression& expandAsNegativeExponent(Expression& baseExpression) override;

        Expression& factor() override;

        std::vector<Expression> getConstantFactors() override;

        std::vector<Expression> getAllFactors() override;

        // Misc

        Expression& copy() override;

        std::string toString() override;

        std::string exponentToString() override;

};

class Constant : Expression {

    private:

        int constant;

    public:

        Constant();

        Constant(bool sign, Expression* root, Expression* exponent, int constant);

        // Overrides

        // Get

        int* getValue() override;

        std::vector<Expression> getContent() override;

        // Append/Remove/Replace

        Expression& appendExpression(Expression& e) override;

        void removeExpression(int i) override;

        void replaceExpression(int i, Expression& e) override;

        // Clean

        void sanitise() override;

        // Test

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeExpression(Expression& e) override;

        bool isMergeable() override;

        // Manipulate

        Expression& sum(Expression& e) override;

        Expression& multiply(Expression& e) override;

        Expression& divide(Expression& e) override;

        Expression& mergeMultiplications(Expression& e) override;

        Expression& expandForExponent() override;

        Expression& expandAsExponent(Expression& baseExpression) override;

        Expression& expandAsConstNum(Expression& baseExpression, Division baseDivision) override;

        Expression& expandAsNegativeExponent(Expression& baseExpression) override;

        Expression& factor() override;

        std::vector<Expression> getConstantFactors() override;

        std::vector<Expression> getAllFactors() override;

        // Misc

        Expression& copy() override;

        std::string toString() override;

        std::string exponentToString() override;

};

class Variable : Expression {

    private:

        char variable;

    public:

        Variable();

        Variable(char v);

        // Overrides

        // Get

        int* getValue() override;

        std::vector<Expression> getContent() override;

        // Append/Remove/Replace

        Expression& appendExpression(Expression& e) override;

        void removeExpression(int i) override;

        void replaceExpression(int i, Expression& e) override;

        // Clean

        void sanitise() override;

        // Test

        bool isAtomic() override;

        bool isAtomicExponent() override;

        bool isAtomicNumerator() override;

        bool isLikeExpression(Expression& e) override;

        bool isMergeable() override;

        // Manipulate

        Expression& sum(Expression& e) override;

        Expression& multiply(Expression& e) override;

        Expression& divide(Expression& e) override;

        Expression& mergeMultiplications(Expression& e) override;

        Expression& expandForExponent() override;

        Expression& expandAsExponent(Expression& baseExpression) override;

        Expression& expandAsConstNum(Expression& baseExpression, Division baseDivision) override;

        Expression& expandAsNegativeExponent(Expression& baseExpression) override;

        Expression& factor() override;

        std::vector<Expression> getConstantFactors() override;

        std::vector<Expression> getAllFactors() override;

        // Misc

        Expression& copy() override;

        std::string toString() override;

        std::string exponentToString() override;
};

