
#include <string>
#include <vector>

using namespace std;

double power(double num, int power){
    if (power == 0){
        return 1;
    }else if (power == 1){
        return num;
    }else{
        double total = num; 
        for (int i = 0; i < power - 1; i ++){
            total *= num;
        }
        return total;
    }
}

double sqrt(double num){
    string numStr = to_string(num);
    vector<string> pairs;

    char firstDigit;
    char secondDigit;
    for (int i = numStr.size() - 1; i >= 0; i --){
        string pair = "";

        if (i > 0){
            firstDigit = numStr[i - 1];
            pair.push_back(firstDigit);
        }

        secondDigit = numStr[i];
        pair.push_back(secondDigit);

        pairs.push_back(pair);
        
        
    // unfinished, see algo online

    }
    return 0.0;
}

double abs(double num){
    if (num < 0){
        return num + (2 * num);
    }else if (num > 0){
        return num;
    }else{
        return 0;
    }
}

bool isDivisbleBy(int num, int divisor){
    if (num % divisor != 0){
        return false;
    }else{
        return true;
    }
}

int nthMultiple(int num, int n){
    int count = 1;
    int multiple = 1;
    bool done = false;
    while (!done){
        if (multiple > num){
            done = true;
        }else{
            if (num % multiple == 0){ 
                if (count == n){
                    return multiple;
                }else{
                    count ++;
                }
            }
            multiple ++;
        }
    }
    return -1;
}

int smallestMultiple(int num){
    int smallestMultiple = 2;
    bool done = false;
    while (!done){
        if (smallestMultiple == num){
            done = true;
        }else{
            if (num % smallestMultiple != 0){
                smallestMultiple ++;
            }else{
                return smallestMultiple;
            }
        }
    }
    return smallestMultiple;
}

int largestMultiple(int num){
    int largestMultiple = num;
    bool done = false;
    while (!done){
        if (largestMultiple == 1){
            done = true;
        }else{
            if (num % largestMultiple != 0){
                largestMultiple --;
            }else{
                return largestMultiple;
            }
        }
    }
    return largestMultiple;
}

vector<int> allMultiples(int num){
    vector<int> allMultiples;
    int currentMultiple = 1;
    bool done = false;
    while(!done){
        if (currentMultiple == num){
            done = true;
        }
        if (num % currentMultiple == 0){
            allMultiples.push_back(currentMultiple);
        }
        currentMultiple ++;
    }
    return allMultiples;
}

int largestCommonMultiple(int num, int comparedNum){
    int gcf = -1;
    int toDivide;
    int divisor;
    if (num > comparedNum){
        toDivide = num;
        divisor = comparedNum;
    }else if (num < comparedNum){
        toDivide = comparedNum;
        divisor = num;
    }else{
        return num;
    }
    
    bool found = false;
    while(!found){
        int result = toDivide / divisor;
        int remainder = toDivide % divisor;
        if (remainder == 0){
            found = true;
            gcf = divisor;
        }else{
            toDivide = divisor;
            divisor = remainder;
        }
    }
    return gcf;
}

double findPercentOf(int num, int compared){ // x is what percent of y
    // divide one by the other, this is just a fraction
    return 0;
}

double findNumberByPercent(int num, int percent){ // x is y percent of what number
    // divide num by numerator of percent as fraction, add the result to num
    return 0;
}



