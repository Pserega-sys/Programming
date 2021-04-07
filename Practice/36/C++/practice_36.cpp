#include <iostream>

#include <string>

#include <fstream>

#include <vector>

#include <algorithm>



const auto PI = 3.141592653589793;


class Point {

    enum Coordinata
    {
        Cartesian, Polar
    };

    double a1 = 0, a2 = 0, x, y;
public:
    constexpr static const double skip = 100;
    Point() : x(0), y(0) {}
    Point(double a1, double a2, enum Coordinata coord_system) {
        switch (coord_system) {
        case Cartesian:
            x = a1;
            y = a2;
            break;
        case Polar:
            x = cos(a2) * a1;
            y = sin(a2) * a1;
            break;
        }
    };

    bool operator ==(const Point& other)const {
        return abs(x - other.x) < 1e-10 && abs(y - other.y) < 1e-10;
    }

    bool operator !=(const Point& tyother)const {
        return !(*this == tyother);
    }

    double get_x()const
    {
        return x;
    }

    void set_x(double x) 
    { 
        this->x = x; 
    }

    double get_y()const 
    { 
        return y; 
    }

    void set_y(double y) 
    { 
        this->y = y; 
    }

    double get_r()const 
    {
        return sqrt(x * x + y * y); 
    }

    double get_phi()const 
    { 
        return atan(y / x) + (x < 0 ? PI : 0);
    }

    void set_phi(double phi) 
    {
        double r = get_r();
        x = r * cos(phi);
        y = r * sin(phi);
    }

};

std::ostream& operator <<(std::ostream& out, const Point& a_) {
    out << '(' << a_.get_x() << ',' << a_.get_y() << ')';
    return out;
};

std::istream& operator >>(std::istream& in, Point& pointin) {
    double poi;
    in.ignore(Point::skip, '(');
    in >> poi;
    pointin.set_x(poi);
    in.ignore(Point::skip, ',');
    in >> poi;
    pointin.set_y(poi);
    in.ignore(Point::skip, ')');
    return in;
};

int main() {
    std::vector<Point> original;
    std::ifstream fin("data.txt");
    if (!fin.is_open()) {
        std::cout << "Can't open file" << std::endl;
        return 1;
    }
    else {
        while (!fin.eof()) {
            Point p;
            fin >> p;
            fin.ignore(2); // Точки разделены двумя символами ", "
            original.push_back(p);
        }
        fin.close();
    }

    std::vector<Point> simulacrum(original);
    for (auto& p : simulacrum) {
        std::cout << p;
        p.set_x(p.get_x() + 10);
        p.set_phi(p.get_phi() + 180 * PI / 180);
        p.set_y(-p.get_y());
        p.set_x(-p.get_x() - 10);
        std::cout << p << std::endl;
    }

    if (std::equal(original.begin(), original.end(), simulacrum.begin()))
        std::cout << "\nIt works!\n";
    else
        std::cout << "\nIt not works!\n";
}