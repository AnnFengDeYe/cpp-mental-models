#include "Shape.h"
#include <cmath>

Shape::Shape(double r) : type(CIRCLE), radius(r), width(0), height(0), cachedArea(0.0), isAreaCached(false) {
    shapeCount++;
}

Shape::Shape(double w, double h) : type(RECTANGLE), radius(0), width(w), height(h), cachedArea(0.0), isAreaCached(false) {
    shapeCount++;
}

Shape::Shape(const std::vector<Point>& v) : type(POLYGON), radius(0), width(0), height(0), vertices(v), cachedArea(0.0), isAreaCached(false) {
    shapeCount++;
}

Shape::~Shape() {
    shapeCount--;
}

int Shape::getShapeCount() {
    return shapeCount;
}

double Shape::getArea() const {
    if (isAreaCached) {         // Cache Hit
        return cachedArea;
    }

    // Cache Miss
    double area = 0.0;
    if (type == CIRCLE) {
        area = 3.14159 * radius * radius;
    } else if (type == RECTANGLE) {
        area = width * height;
    } else if (type == POLYGON) {
        int n = vertices.size();
        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            area += (vertices[i].x * vertices[j].y - vertices[j].x * vertices[i].y);
        }
        area = std::abs(area) / 2.0;
    }

    cachedArea = area;
    isAreaCached = true;

    return cachedArea;
}