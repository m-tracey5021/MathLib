#pragma once

#include "Trees\EqTrees\eqTree.h"
#include "Trees\EqTrees\operatorType.h"
#include <string>

EqTree createTreeFromEquation(char* eq, int size);

void printEqTree(BinaryNode root);

