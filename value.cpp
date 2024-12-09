#include "value.h"
#include <iostream>
#include <cmath>

Value::Value(float data) : data(data) {}

Value::Value(float data, std::set<std::shared_ptr<Value>>& prev, const std::string& op)
    : data(data), prev(prev), op(op) {}

std::shared_ptr<Value> Value::tanh() {
    auto newSet = std::set<std::shared_ptr<Value>>{shared_from_this()};
    float t = std::tanh(this->data);
    auto out = std::make_shared<Value>(t, newSet, "tanh");

    out->backward = [self = shared_from_this(), t]()
    {
        self->grad = (1 - std::pow(t, 2));
    };

    return out;
}

void Value::print(int level = 0) const {
    std::cout << std::string(level * 2, ' ') << "Value: " << data << " Grad: " << grad << " " << op << std::endl;

    for (const auto& child : prev) {
        child->print(level + 1);
    }
}