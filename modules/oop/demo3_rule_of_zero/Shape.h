#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <iostream>
#include <string>


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
    [[nodiscard]] virtual double getArea() const = 0;

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
    std::string tag;

public:
    explicit Circle(double r, std::string t = "Default Circle");

    [[nodiscard]] double getArea() const override;

protected:
    void print(std::ostream& os) const override;
};

#endif