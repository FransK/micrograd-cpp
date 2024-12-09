#include <iostream>
#include "value.cpp"

int main() {
    auto a = std::make_shared<Value>(-3.0);
    auto b = std::make_shared<Value>(2.0);
    auto c = std::make_shared<Value>(0.0);
    auto d = std::make_shared<Value>(1.0);
    auto e = a * b;
    auto f = c * d;
    auto g = e + f;
    auto base = std::make_shared<Value>(6.8813735870195432);
    auto h = g + base;
    auto L = h->tanh();

    L->grad = 1.0;
    L->backward();
    h->backward();
    base->backward();
    g->backward();
    f->backward();
    e->backward();

    L->print();

    return 0;
}