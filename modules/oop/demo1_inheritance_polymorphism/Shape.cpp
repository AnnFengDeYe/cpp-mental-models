#include "Shape.h"
#include <cmath>

Circle::Circle(double r) : radius(r) {}

double Circle::getArea() const {
    return 3.14159 * radius * radius;
}

void Circle::print(std::ostream& os) const {
    os << "Circle [ID: " << id << "] (Radius: " << radius << ")";
}

Rectangle::Rectangle(double w, double h) : width(w), height(h) {}

double Rectangle::getArea() const {
    return width * height;
}

void Rectangle::print(std::ostream& os) const {
    os << "Rectangle [ID: " << id << "] (Width: " << width << ", Height: " << height << ")";
}

Polygon::Polygon(const std::vector<Point>& v)
        : vertices(v), cachedArea(0.0), isAreaCached(false) {
}

double Polygon::getArea() const {
    if (isAreaCached) {
        return cachedArea;
    }

    double area = 0.0;
    int n = vertices.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += (vertices[i].x * vertices[j].y - vertices[j].x * vertices[i].y);
    }
    cachedArea = std::abs(area) / 2.0;
    isAreaCached = true;

    return cachedArea;
}

void Polygon::print(std::ostream& os) const {
    os << "Polygon [ID: " << id << "] (Vertices: " << vertices.size() << ")";
}