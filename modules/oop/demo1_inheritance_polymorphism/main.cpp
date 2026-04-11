#include "Shape.h"
#include <iostream>
#include <vector>

int main() {
    Circle myCircle(5.0);
    Rectangle myRect(10.0, 20.0);

    std::vector<Point> triangleVertices = {{0.0, 0.0}, {4.0, 0.0}, {0.0, 3.0}};
    Polygon myPolygon(triangleVertices);

    // Upcasting
    std::vector<Shape*> shapeCollection;
    shapeCollection.push_back(&myCircle);
    shapeCollection.push_back(&myRect);
    shapeCollection.push_back(&myPolygon);

    // Dynamic Binding
    for (const Shape* s : shapeCollection) {
        std::cout << *s << " | Area: " << s->getArea() << "\n";
    }

    std::cout << "\nTotal Shapes in memory: " << Shape::getShapeCount() << "\n";

    Shape* s1 = new Circle(5.0);
    s1->getArea();
}