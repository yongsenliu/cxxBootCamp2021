#include <iostream>
#define pi 3

using namespace std;

// create interface for shapes
// class ShapeInterface {
//     public:
//     virtual void setValues(int, int) = 0;
//     virtual int area() = 0;
//     virtual bool isEqual() = 0;
//     virtual bool isGreater() = 0;
//     virtual bool isSmaller() = 0;
// };

// create base class for shapes which comply the interface
class Shape {
    protected:
        int x, y;

    public:
    void setValues(int _x, int _y) final {
        x = _x;
        y = _y;
    };
    int area() override {
        return -1;
    }
    bool isEqual(const ) final {
        return true;
    }
    bool isGreater() final {
        return true;
    }
    bool isSmaller() final {
        return true;
    }
};

// create classes for shapes
class Circle: public Shape {
    public:
    int area() {
        return pi*x*y;
    }
};

class Triangle: public Shape {
    public:
    int area() {
        return x*y/2;
    }
};

class Rectangle: public Shape {
    public:
    int area() override {
        return x*y;
    }
};

class Square: public Rectangle {
    public:
    int area() {
        if (x>y) {
            return x*x;
        } else {
            return y*y;
        } 
    }
};

// main entry
int main() {
    Circle cir;
    Triangle tri;
    Rectangle rect;
    Square sq;

    Shape *p = new Shape;

    p = &cir;
    p->setValues(2, 3);
    std::cout << typeid(*p).name() << ": " << p->area() << std::endl;
    
}





