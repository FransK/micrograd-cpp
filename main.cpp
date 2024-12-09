#include <iostream>
#include "value.cpp"

int main() {
    Value a = Value(2.0);
    Value b = Value(-3.0);
    Value c = Value(10.0);
    Value d = a * b;
    Value e = c + d;
    Value f = Value(-2.0);
    Value L = e * f;
    L.print();
    return 0;
}