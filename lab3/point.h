#ifndef POINT_H
#define POINT_H

#include <string>

class Point {
private:
    double x;
    double y;

public:
    Point(double xCoord, double yCoord);
    Point();
    
    double getX() const;
    double getY() const;
    
    void setX(double newX);
    void setY(double newY);
    
    std::string toString() const;
    void print() const;
};

#endif