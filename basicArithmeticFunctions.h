#pragma once

#include <vector>


double power(double num, int power);

double sqrt(double num);

double abs(double num);

bool isDivisibleBy(int num, int divisor);

int nthMultiple(int num, int n);

int smallestMultiple(int num);

int largestMultiple(int num);

std::vector<int> allMultiples(int num);

/*
int smallestCommonMultiple(int num, int comparedNum);

int largestCommonMultiple(int num, int comparedNum);
*/

int largestCommonMultiple(int num, int comparedNum);

double findPercentOf(int num, int compared);

double findNumberByPercent(int num, int percent);