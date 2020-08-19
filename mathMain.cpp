
#include <iostream>
#include "Binary\bitString.h"
#include "Fractions\fraction.h"
#include "Sets\set.h"
#include "UnitTests\setUnitTest.h"
#include "UnitTests\fractionUnitTest.h"
#include "UnitTests\treeUnitTest.h"
#include "UnitTests\automataUnitTest.h"
#include "Sets\stdSetOperations.h"
#include "HashTables\integerHashSet.h"
#include "HashTables\hashSet.h"
#include "Binary\binaryFunctions.h"
#include "basicArithmeticFunctions.h"
#include "algabraicFunctions.h"
#include "util.h"
#include <set>

using namespace std;

int main(){
    BitString bits = addDecimalToBin(23, 43);
    int toDec = convertToDecimal(bits);
    BitString bits1Reversed = reverseBits(bits);

    /*
    Operator* op = new Operator(OperatorType::Addition, false, "operator");
    StaticOperand* operand = new StaticOperand(13, "operand");
    */
   
    //tree.insertMainFunctionLeft(op, operand);
    //BinaryNode* removed = tree2.removeMainFunctionLeft();


    std::set<int> ints1 = {1, 2, 3, 3, 4, 5};
    std::set<int> ints2 = {4, 5, 5, 9, 10};

    std::set<int> diff = stdSet::setDifference(ints1, ints2);

    bool treeStructurePassed = testTreeStructure();

    bool setDiffPassed = testSetDifference();

    bool setUnionPassed = testSetUnion();

    bool setIntersectionPassed = testSetIntersection();

    bool setStringSpecPassed = testStringSpecialisation();

    bool addPassed = testAdd();

    bool simplifyPassed = testSimplify();

    bool threeStateDFAPassed = testThreeState();

    bool fiveStateDFAPassed = testFiveState();

    int elements1[] = {3, 4, 5};
    char elements2[] = {'a', 'b', 'c'};

    HashSet<int> generic1(6, 3, elements1); 
    HashSet<char> generic2(6, 3, elements2);

    std::string str1 = generic1.toString();
    std::string str2 = generic2.toString();

    generic1.insert(7);
    generic2.insert('d');

    int* arr1 = generic1.toArray();
    char* arr2 = generic2.toArray();

    str1 = generic1.toString();
    str2 = generic2.toString();


    Fraction fraction1(8, 24);
    Fraction fraction2(3, 10);
    Fraction fraction3(52, 87);
    cout << fraction1.toString() << endl;
    cout << fraction2.toString() << endl;
    cout << fraction3.toString() << endl;
    fraction1.simplify();
    fraction2.simplify();
    fraction3.simplify();
    cout << fraction1.toString() << endl;
    cout << fraction2.toString() << endl;
    cout << fraction3.toString() << endl;
    Fraction added = fraction1.add(fraction2);
    cout << "f1 + f2 = " << added.toString() << endl;
    Fraction subtracted = fraction2.subtract(fraction3);
    cout << "f2 - f3 = " << subtracted.toString() << endl;
    Fraction multiplied1 = fraction3.multiply(fraction1);
    cout << "f3 * f1 = " << multiplied1.toString() << endl;

    Fraction multiplied2 = fraction3.multiply(2);
    cout << "f3 * 2 = " << multiplied2.toString() << endl;
    int m1 = nthMultiple(16, 2);
    int m2 = nthMultiple(18, 1);
    int m3 = nthMultiple(10, 5);
    int d = -2 * 5;
    
    return 0;
}