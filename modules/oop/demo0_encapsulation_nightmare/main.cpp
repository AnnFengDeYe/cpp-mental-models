#include "Shape.h"
#include <iostream>
#include <vector>

int main() {
    Shape myCircle(5.0);
    Shape myRect(10.0, 20.0);

    std::vector<Point> triangleVertices = {{0.0, 0.0}, {4.0, 0.0}, {0.0, 3.0}};
    Shape myPolygon(triangleVertices);

    std::cout << myCircle << " | Area: " << myCircle.getArea() << "\n";
    std::cout << myRect << " | Area: " << myRect.getArea() << "\n";
    std::cout << myPolygon << " | Area: " << myPolygon.getArea() << "\n";

    std::cout << "Total Shapes: " << Shape::getShapeCount() << "\n";
}