#include "Shape.h"

// Construction
Circle::Circle(double r, const char* t) : radius(r) {
    if (t != nullptr) {
        tag = new char[std::strlen(t) + 1];
        std::strcpy(tag, t);
    } else {
        tag = nullptr;
    }

    std::cout << "  ✨ [Construction] Circle (" << (tag ? tag : "Empty") << ") is born.\n";
}

// Destruction
Circle::~Circle() {
    std::cout << "  💀 [Destruction] Circle (" << (tag ? tag : "Empty") << ") is destroyed. Memory freed.\n";
    delete[] tag;
}

// Copy Construction - deep copy
Circle::Circle(const Circle& other) : Shape(other), radius(other.radius) {
    if (other.tag != nullptr) {
        tag = new char[std::strlen(other.tag) + 1];
        std::strcpy(tag, other.tag);
    } else {
        tag = nullptr;
    }
    std::cout << "  👯 [Copy Const] Cloned from (" << (other.tag ? other.tag : "Empty") << "). Deep copy successful.\n";
}

// Copy Assignment
Circle& Circle::operator=(const Circle& other) {
    std::cout << "  🔄 [Copy Assign] Overwriting (" << (tag ? tag : "Empty") << ") with (" << (other.tag ? other.tag : "Empty") << ").\n";

    if (this == &other) return *this;

    Shape::operator=(other);

    char* new_tag = nullptr;
    if (other.tag != nullptr) {
        new_tag = new char[std::strlen(other.tag) + 1];
        std::strcpy(new_tag, other.tag);
    }

    delete[] tag;

    radius = other.radius;
    tag = new_tag;

    return *this;
}

// Move Construction
Circle::Circle(Circle&& other) noexcept : Shape(std::move(other)), radius(other.radius), tag(other.tag) {
    std::cout << "  🚀 [Move Const] Stealing resources from (" << (other.tag ? other.tag : "Empty") << ").\n";
    other.tag = nullptr;
}

// Move Assignment
Circle& Circle::operator=(Circle&& other) noexcept {
    std::cout << "  🛸 [Move Assign] Overwriting (" << (tag ? tag : "Empty") << ") by stealing from (" << (other.tag ? other.tag : "Empty") << ").\n";

    if (this == &other) return *this;

    Shape::operator=(std::move(other));

    delete[] tag;

    radius = other.radius;
    tag = other.tag;
    other.tag = nullptr;

    return *this;
}

double Circle::getArea() const {
    return 3.14159 * radius * radius;
}

void Circle::print(std::ostream& os) const {
    os << "Circle [ID: " << id << "] (Radius: " << radius << ", Tag: " << (tag ? tag : "Empty") << ")";
}