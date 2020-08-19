#pragma once

#include "point.h"

class Line {
    private:
        Point* p1;
        Point* p2;
    public:
        Line(){}
        Line(Point* p1, Point* p2): p1(p1), p2(p2){}
};