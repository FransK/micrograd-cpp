#include "value.h"
#include <iostream>
#include <cmath>
#include <algorithm>

Value::Value(float data) : data(data) {}

Value::Value(float data, std::set<std::shared_ptr<Value>>& prev, const std::string& op)
    : data(data), prev(prev), op(op) {}

void Value::buildGrads() {
    // Topological sort
    std::vector<std::shared_ptr<Value>> topoOrder;
    std::set<Value*> visited;

    buildTopoOrder(shared_from_this(), topoOrder, visited);

    // Reverse the topological order
    std::reverse(topoOrder.begin(), topoOrder.end());

    // Initialize the gradient of the output node
    this->grad = 1.0;

    // Call backward for each node in reverse order
    for (const auto& node : topoOrder) {
        if (node->backward) {
            node->backward();
        }
    }
}

std::shared_ptr<Value> Value::tanh() {
    auto newSet = std::set<std::shared_ptr<Value>>{shared_from_this()};
    float t = std::tanh(this->data);
    auto out = std::make_shared<Value>(t, newSet, "tanh");

    out->backward = [self = shared_from_this(), t]()
    {
        self->grad += (1 - std::pow(t, 2));
    };

    return out;
}

void Value::print(int level = 0) const {
    std::cout << std::string(level * 2, ' ') << "Value: " << data << " Grad: " << grad << " " << op << std::endl;

    for (const auto& child : prev) {
        child->print(level + 1);
    }
}