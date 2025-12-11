#include "line.h"
#include <iostream>
#include <sstream>
#include <cmath>

Line::Line(Point* start, Point* end) : startPoint(start), endPoint(end) {}

Line::Line(const Point& start, const Point& end) : 
    startPoint(new Point(start.getX(), start.getY())), 
    endPoint(new Point(end.getX(), end.getY())) {}

Line::Line(double x1, double y1, double x2, double y2) :
    startPoint(new Point(x1, y1)),
    endPoint(new Point(x2, y2)) {}

Point* Line::getStartPoint() const {
    return startPoint;
}

Point* Line::getEndPoint() const {
    return endPoint;
}

void Line::setStartPoint(Point* point) {
    startPoint = point;
}

void Line::setEndPoint(Point* point) {
    endPoint = point;
}

std::string Line::toString() const {
    std::ostringstream oss;
    oss << "Линия от " << startPoint->toString() << " до " << endPoint->toString();
    return oss.str();
}

double Line::length() const {
    double dx = endPoint->getX() - startPoint->getX();
    double dy = endPoint->getY() - startPoint->getY();
    return std::sqrt(dx*dx + dy*dy);
}

void Line::print() const {
    std::cout << toString() << std::endl;
}