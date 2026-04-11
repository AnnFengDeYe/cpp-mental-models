#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <iostream>
#include <cstring>

struct Point {
    double x, y;
};

class Shape {
private:
    inline static int shapeCount = 0;

public:
    Shape() {
        shapeCount++;
        id = shapeCount;
    }

    Shape(const Shape& /*other*/) { id = ++shapeCount; }
    Shape(Shape&& /*other*/) noexcept { id = ++shapeCount; }
    Shape& operator=(const Shape& /*other*/) { return *this; }
    Shape& operator=(Shape&& /*other*/) noexcept { return *this; }
    virtual ~Shape() { shapeCount--; }

    static int getShapeCount() { return shapeCount; }
    virtual double getArea() const = 0;

protected:
    int id = 0;
    virtual void print(std::ostream& os) const = 0;

public:
    friend std::ostream& operator<<(std::ostream& os, const Shape& shape) {
        os << "[Shape Info] ";
        shape.print(os);
        return os;
    }
};

class Circle final : public Shape {
private:
    double radius;
    char* tag;

public:
    explicit Circle(double r, const char* t = "Default Circle");

    Circle(const Circle& other);

    ~Circle() override;
    Circle& operator=(const Circle& other);
    Circle(Circle&& other) noexcept;
    Circle& operator=(Circle&& other) noexcept;
    double getArea() const override;

protected:
    void print(std::ostream& os) const override;
};

#endif