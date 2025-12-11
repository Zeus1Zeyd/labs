#include "point.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Point::Point(double xCoord, double yCoord) : x(xCoord) , y(yCoord) {}
Point::Point(): x(0), y(0) {}

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

void Point::setX(double newX) {
    x = newX;
}

void Point::setY(double newY) {
    y = newY;
}

std::string Point::toString() const {
    std::ostringstream oss;
    oss << "{" << x << ";" << y << "}";
    return oss.str();
}

void Point::print() const {
    std::cout << toString() << std::endl;
}