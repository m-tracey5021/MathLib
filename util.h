#pragma once

#include "Trees\treeElement.h"
#include "Trees\operatorType.h"

int stringLength(std::string str);

bool stringIsEqual(std::string str1, std::string str2);

OperatorType getOperatorType(char value);

bool charIsNumeric(char c);

bool charIsOperator(char c);

char* substring(char* str, int len, int startPos);

int convertToInt(char* numberStr, int len);

int convertToInt(char* numberStr, int startIndex, int endIndex);

int* findSurroundingBrackets(char* eq, int startPos);

//int parseForMainOperator(char* eq, int start, int end);

int* parseForMainOperator(char* eq, int start, int end);

int parseForFirstInt(char* eq, int start, int end);

char parseForFirstChar(char* eq, int start, int end);

TreeElement* parseForFirstOperand(char* eq, int start, int end);

