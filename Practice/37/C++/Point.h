#ifndef POINT_H
#define POINT_H

const auto PI = 3.141592653589793;

enum system_coord {
    Cartesian, Polar 
};
class Point {
    double x, y;
public:
    Point(double = 0, double = 0, system_coord = system_coord::Cartesian);
    constexpr static const double skip = 100;
    bool operator==(const Point&) const;
    bool operator!=(const Point&) const;

    double get_x() const;
    void set_x(double);
    double get_y() const;
    void set_y(double);
    double get_r() const;
    void set_r(double);
    double get_phi() const;
    void set_phi(double);

};

#endif 