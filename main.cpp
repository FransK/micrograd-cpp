#include <iostream>
#include "value.cpp"

int main() {
    auto a = std::make_shared<Value>(3.0);
    auto b = a + a;
    auto c = 1 + b;
    auto d = 4 * c;
    d->buildGrads();

    d->print();

    return 0;
}