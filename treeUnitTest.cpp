#include "Trees\EqTrees\eqTree.h"
#include "algabraicFunctions.h"

bool testTreeStructure(){
    char eq1[] = "(509 + 4) / 2 - 3 = 12 + x";
    int size1 = sizeof(eq1) / sizeof(eq1[0]);
    EqTree tree1 = createTreeFromEquation(eq1, size1);
    std::string treeStr1 = tree1.toString();

    char eq2[] = "((5 + 3) / 6) = 10";
    int size2 = sizeof(eq2) / sizeof(eq2[0]);
    EqTree tree2 = createTreeFromEquation(eq2, size2);
    std::string treeStr2 = tree2.toString();

    std::string expected1 = "(509+4)/2-3=12+x";
    std::string expected2 = "((5+3)/6)=10";

    bool tree1Passed;
    bool tree2Passed;

    if (tree1.getRoot()->getElement()->toString() == "=" & 
        tree1.getRoot()->getLeftNode()->getElement()->toString() == "-" & 
        tree1.getRoot()->getLeftNode()->getLeftNode()->getElement()->toString() == "/" & 
        tree1.getRoot()->getLeftNode()->getLeftNode()->getLeftNode()->getElement()->toString() == "+" &
        tree1.getRoot()->getLeftNode()->getLeftNode()->getLeftNode()->getLeftNode()->getElement()->toString() == "509" & 
        tree1.getRoot()->getLeftNode()->getLeftNode()->getLeftNode()->getRightNode()->getElement()->toString() == "4" & 
        tree1.getRoot()->getLeftNode()->getLeftNode()->getRightNode()->getElement()->toString() == "2" & 
        tree1.getRoot()->getLeftNode()->getRightNode()->getElement()->toString() == "3" & 
        tree1.getRoot()->getRightNode()->getElement()->toString() == "+" & 
        tree1.getRoot()->getRightNode()->getRightNode()->getElement()->toString() == "x" & 
        tree1.getRoot()->getRightNode()->getLeftNode()->getElement()->toString() == "12"){
        tree1Passed = true;
    }else{
        tree1Passed = false;
    }

    if (tree2.getRoot()->getElement()->toString() == "=" & 
        tree2.getRoot()->getLeftNode()->getElement()->toString() == "/" & 
        tree2.getRoot()->getLeftNode()->getLeftNode()->getElement()->toString() == "+" & 
        tree2.getRoot()->getLeftNode()->getLeftNode()->getLeftNode()->getElement()->toString() == "5" & 
        tree2.getRoot()->getLeftNode()->getLeftNode()->getRightNode()->getElement()->toString() == "3" & 
        tree2.getRoot()->getLeftNode()->getRightNode()->getElement()->toString() == "6" & 
        tree2.getRoot()->getRightNode()->getElement()->toString() == "10"){
        tree2Passed = true;
    }else{
        tree2Passed = false;
    }

    if ((tree1Passed & treeStr1 == expected1) & (tree2Passed & treeStr2 == expected2)){
        return true;
    }else{
        return false;
    }


}

bool testTreeInsertion(){
    char eq1[] = "x / 3 + 6 = 5";
    int size1 = sizeof(eq1) / sizeof(eq1[0]);
    EqTree tree1 = createTreeFromEquation(eq1, size1);
    std::string treeStr1 = tree1.toString();

    char eq2[] = "x + 8 / 2 = 10";
    int size2 = sizeof(eq2) / sizeof(eq2[0]);
    EqTree tree2 = createTreeFromEquation(eq2, size2);
    std::string treeStr2 = tree2.toString();

    Operator* op1 = new Operator(OperatorType::Multiplication, false, "operator");
    Operator* op2 = new Operator(OperatorType::Division, false, "operator");
    StaticOperand* operand1 = new StaticOperand(3, "operand");
    StaticOperand* operand2 = new StaticOperand(2, "operand");

    tree1.insertFunctionRight(op1, operand1);
    treeStr1 = tree1.toString();

    tree2.insertFunctionRight(op2, operand2);
    treeStr2 = tree2.toString();

    std::string expected1 = "x/3+6=5*3";
    std::string expected2 = "x+8/2=10/2";

    if (treeStr1 == expected1 & treeStr2 == expected2){
        return true;
    }else{
        return false;
    }
}

bool testTreeFunctionApplication(){
    char eq1[] = "x / 3 + 6 = 5";
    int size1 = sizeof(eq1) / sizeof(eq1[0]);
    EqTree tree1 = createTreeFromEquation(eq1, size1);
    std::string treeStr1 = tree1.toString();

    char eq2[] = "x + 8 / 2 = 10";
    int size2 = sizeof(eq2) / sizeof(eq2[0]);
    EqTree tree2 = createTreeFromEquation(eq2, size2);
    std::string treeStr2 = tree2.toString();

    Operator* op1 = new Operator(OperatorType::Multiplication, false, "operator");
    Operator* op2 = new Operator(OperatorType::Division, false, "operator");

    StaticOperand* operand1 = new StaticOperand(3, "operand");
    StaticOperand* operand2 = new StaticOperand(2, "operand");

    tree1.applyFunctionLeft(*op1, *operand1);
    treeStr1 = tree1.toString();

    tree2.applyFunctionLeft(*op2, *operand2);
    treeStr2 = tree2.toString();

    std::string expected1 = "x+18=5";
    std::string expected2 = "x+4/1=10";

    if (treeStr1 == expected1 & treeStr2 == expected2){
        return true;
    }else{
        return false;
    }

}