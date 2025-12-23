#include "Point3D.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

// Point2D
Point2D::Point2D(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}

double Point2D::getX() const { return x; }
double Point2D::getY() const { return y; }

std::string Point2D::toString() const {
    using namespace std;
    ostringstream oss;
    oss << fixed << setprecision(2) << "{" << x << "; " << y << "}";
    return oss.str();
}

void Point2D::print() const {
    using namespace std;
    cout << toString() << endl;
}

double Point2D::distanceTo(const Point2D& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return sqrt(dx * dx + dy * dy);
}

// Point3D
Point3D::Point3D(double xCoord, double yCoord, double zCoord) 
    : Point2D(xCoord, yCoord), z(zCoord) {}

std::string Point3D::toString() const {
    using namespace std;
    ostringstream oss;
    oss << fixed << setprecision(2) << "{" << getX() << "; " << getY() << "; " << z << "}";
    return oss.str();
}

double Point3D::distanceTo(const Point3D& other) const {
    double dx = getX() - other.getX();
    double dy = getY() - other.getY();
    double dz = z - other.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

/*double Point3D::distanceTo(const Point2D& other) const {
    const Point3D* other3D = dynamic_cast<const Point3D*>(&other);
    if (other3D) {
        return distanceTo(*other3D);
    }
    
    double dx = getX() - other.getX();
    double dy = getY() - other.getY();
    return sqrt(dx * dx + dy * dy);
}
*/