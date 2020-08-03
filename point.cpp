#include "math.h"
#include "Geometry/point.h"

Point::Point(){}

Point::Point(double x, double y): x(x), y(y){}

double Point::distance(Point other){
    double deltaX = x - other.getX();
    double deltaY = y - other.getY();
    double distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
    return distance;
}