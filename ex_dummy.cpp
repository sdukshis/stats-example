class Shape {
public:
    virtual ~Shape() {};
    virtual double area() = 0;
};

class Square: public Shape {
public:
    Square(double side) : side_{side} {};
    double area() override { return side_ * side_; }
private:
    double side_;
};

class Rectangle: public Shape {
public:
    Rectangle(double width, double height):
        width_{width}, height_{height} {};
    double area() override { return width_ * height_; };
private:
    double width_, height_;
};

int main() {}
