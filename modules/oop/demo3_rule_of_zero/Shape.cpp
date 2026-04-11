#include "Shape.h"

Circle::Circle(double r, std::string t) : radius(r), tag(std::move(t)) {}

double Circle::getArea() const {
    return 3.14159 * radius * radius;
}

void Circle::print(std::ostream& os) const {
    os << "Circle [ID: " << id << "] (Radius: " << radius << ", Tag: " << tag << ")";
}