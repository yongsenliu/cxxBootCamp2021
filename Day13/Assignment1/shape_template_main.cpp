/*Implement an interface for shape, and derive circle, triangle, rectangle, square as children. Overload all three
comparison operators to compare the shapes based on their area -- if equal then their perimeter should be
considered. Only, and if only both area and perimeter are equal then the objects should be considered equal.*/

#include "shape.h"

template <typename T1, typename T2> 
void compare(const T1 _a, const T2 _b) {
    if (_a > _b) std::cout << "a is greater than b" << std::endl;
    if (_a == _b) std::cout << "a is equal than b" << std::endl;
    if (_a < _b) std::cout << "a is less than b" << std::endl;
};

int main(){


    Shape *circ1 = new Circle(5);
    Shape *circ2 =  new Circle(100);

    Shape *triang1 = new Triangle(2,23);
    Shape *triang2 = new Triangle(3,5);

    Shape *rectangle1 = new Rectangle(23,1);
    Shape *rectangle2 = new Rectangle(2,1);

    Shape *shapes [6] ={circ1,circ2,triang1,triang2,rectangle1,rectangle2};

    compare(circ1, circ2);
    compare(rectangle1, triang1);
    compare(rectangle1, rectangle1);
    compare(1, 3.14f);
    compare(1, 1.0);

    for (size_t i=0;i<6;i++) {
        delete shapes[i];
    }

    return 0;
} 