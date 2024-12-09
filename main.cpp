#include <cmath>
#include <iostream>
#include "value.cpp"

float derivative_tanh(float x) {
    float tanh_x = std::tanh(x);
    return 1.0 - tanh_x * tanh_x;
}

int main() {
    auto a = std::make_shared<Value>(-3.0);
    auto b = std::make_shared<Value>(2.0);
    auto c = std::make_shared<Value>(0.0);
    auto d = std::make_shared<Value>(1.0);
    auto e = a * b;
    auto f = c * d;
    auto g = e + f;
    auto base = std::make_shared<Value>(6.881373);
    auto h = g + base;
    auto L = h->tanh();

    L->grad = 1.0;
    L->backward();

    L->print();

    return 0;
}