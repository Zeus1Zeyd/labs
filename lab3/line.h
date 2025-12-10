#ifndef LINE_H
#define LINE_H

#include "point.h"
#include <string>

class Line {
private:
    Point* startPoint;
    Point* endPoint;
    
public:
    Line(Point* start, Point* end);
    Line(const Point& start, const Point& end);
    Line(double x1, double y1, double x2, double y2);
    
    Point* getStartPoint() const;
    Point* getEndPoint() const;
    
    void setStartPoint(Point* point);
    void setEndPoint(Point* point);
    
    std::string toString() const;
    double length() const;
    void print() const;
};

#endif