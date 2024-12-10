#include <iostream>
#include "value.cpp"

void practice_one() {
    auto x1 = std::make_shared<Value>(2.0);
    x1->label = "x1";
    auto x2 = std::make_shared<Value>(0.0);
    x2->label = "x2";
    auto w1 = std::make_shared<Value>(-3.0);
    w1->label = "w1";
    auto w2 = std::make_shared<Value>(1.0);
    w2->label = "w2";

    auto b = std::make_shared<Value>(6.8813735870195432);
    b->label = "b";

    auto x1w1 = x1 * w1;
    x1w1->label = "x1w1";
    auto x2w2 = x2 * w2;
    x2w2->label = "x2w2";
    auto x1w1x2w2 = x1w1 + x2w2;
    x1w1x2w2->label = "x1w1x2w2";
    auto n = x1w1x2w2 + b;
    n->label = "n";

    auto e = (2 * n)->exp();
    e->label = "e";
    auto o = (e - 1) / (e + 1);
    o->label = "o";

    o->buildGrads();
    o->print();
}

int main() {
    practice_one();

    return 0;
}