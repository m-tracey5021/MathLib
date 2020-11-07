#include "math.h"
#include "point.h"

double Point::distance(Point other){
    double deltaX = x - other.getX();
    double deltaY = y - other.getY();
    double distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
    return distance;
}