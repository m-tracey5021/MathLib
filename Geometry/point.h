#pragma once

class Point {
    private:
        double x, y;
    public:
        Point(){}
        Point(double x, double y): x(x), y(y){}
        double getX(){return x;}
        double getY(){return y;}

        double distance(Point other);

};