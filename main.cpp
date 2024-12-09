#include <cmath>
#include <iostream>
#include "value.cpp"

float derivative_tanh(float x) {
    float tanh_x = std::tanh(x);
    return 1.0 - tanh_x * tanh_x;
}

int main() {
    Value a = Value(-3.0);
    Value b = Value(2.0);
    Value c = Value(0.0);
    Value d = Value(1.0);
    Value e = a * b;
    Value f = c * d;
    Value g = e + f;
    Value h = g + 6.881373;
    Value L = h.tanh();
    L.print();
    return 0;
}