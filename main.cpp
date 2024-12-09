#include <iostream>
#include "value.cpp"

int main() {
    auto a = std::make_shared<Value>(3.0);
    auto b = a + a;
    auto c = b * 1;
    c->buildGrads();

    c->print();

    return 0;
}