#include <iostream>

#include <string>

#include <fstream>

#include <vector>

#include <algorithm>

#include <cmath>

#include "point.h"

Point::Point(double a1, double a2, system_coord coord_system) {
    if (coord_system == system_coord::Cartesian) {
        x = a1;
        y = a2;
    } else {
        x = cos(a2) * a1;
        y = sin(a2) * a1;
    }
}

bool Point::operator==(const Point& other) const {
    return abs(x - other.x) < 1e-10 && abs(y - other.y) < 1e-10;
}

bool Point::operator!=(const Point& tyother) const {
    return !(*this == tyother);
}

double Point::get_x()const { return x; }

void Point::set_x(double x) { this->x = x; }

double Point::get_y() const { return y; }

void Point::set_y(double y) { this->y = y; }

double Point::get_r() const
{ 
    return sqrt(x * x + y * y); 
}

void Point::set_r(double r) {
    double phi = get_phi();
    x = cos(phi) * r;
    y = sin(phi) * r;
}

double Point::get_phi() const 
{ 
    return atan(y / x) + (x < 0 ? PI : 0);
}

void Point::set_phi(double phi) {
    double r = get_r();
    x = cos(phi) * r;
    y = sin(phi) * r;
}

std::ostream& operator<<(std::ostream& out, const Point& a_) {
    out << '(' << a_.get_x() << ',' << a_.get_y() << ')';
    return out;
}

std::istream& operator>>(std::istream& in, Point& pointin) {
    double poi;
    in.ignore(Point::skip, '(');
    in >> poi;
    pointin.set_x(poi);
    in.ignore(Point::skip, ',');
    in >> poi;
    pointin.set_y(poi);
    in.ignore(Point::skip, ')');
    return in;
}