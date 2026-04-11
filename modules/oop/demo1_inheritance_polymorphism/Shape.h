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

public:
    Shape() {
        shapeCount++;
        id = shapeCount;
    }

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

class Circle final: public Shape {
private:
    double radius;

public:
    explicit Circle(double r) ;
    double getArea() const override final;

protected:
    void print(std::ostream& os) const override;
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    explicit Rectangle(double w, double h);
    double getArea() const override;

protected:
    void print(std::ostream& os) const override;
};

class Polygon : public Shape {
private:
    std::vector<Point> vertices;

    mutable double cachedArea;
    mutable bool isAreaCached;

public:
    explicit Polygon(const std::vector<Point>& v);
    double getArea() const override;

protected:
    void print(std::ostream& os) const override;
};

#endif