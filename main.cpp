#include <iostream>
#include "value.cpp"

int main() {
    Value a = Value(1.0);
    Value b = Value(3.0);
    Value c = a + b;
    std::cout << "Value of c: " << c << std::endl;
    return 0;
}