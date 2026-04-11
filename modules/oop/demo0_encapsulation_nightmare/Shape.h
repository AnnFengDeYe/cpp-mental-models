#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <iostream>

struct Point {
    double x, y;
};

class Shape {
private:
    inline static int shapeCount = 0;

    enum Type { CIRCLE, RECTANGLE, POLYGON } type;
    double radius;
    double width, height;
    std::vector<Point> vertices;

    mutable double cachedArea;
    mutable bool isAreaCached;

public:
    explicit Shape(double r);
    explicit Shape(double w, double h);
    explicit Shape(const std::vector<Point>& v);

    ~Shape();

    static int getShapeCount();

    double getArea() const;

    friend std::ostream& operator<<(std::ostream& os, const Shape& shape) {
        os << "[Shape Info] ";
        if (shape.type == CIRCLE) {
            os << "Circle (Radius: " << shape.radius << ")";
        } else if (shape.type == RECTANGLE) {
            os << "Rectangle (Width: " << shape.width << ", Height: " << shape.height << ")";
        } else if (shape.type == POLYGON) {
            os << "Polygon (Vertices: " << shape.vertices.size() << ")";
        }
        return os;
    }
};

#endif