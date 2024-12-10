#include <iostream>
#include "value.cpp"

int main() {
    auto a = std::make_shared<Value>(4.0);
    auto b = std::make_shared<Value>(2.0);
    auto c = a - b;
   
    c->buildGrads();
    c->print();

    return 0;
}