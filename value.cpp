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

    out->backward = [self = shared_from_this(), t, out]()
    {
        self->grad += (1 - std::pow(t, 2)) * out->grad;
    };

    return out;
}

std::shared_ptr<Value> Value::exp() {
    auto newSet = std::set<std::shared_ptr<Value>>{shared_from_this()};
    float e = std::exp(this->data);
    auto out = std::make_shared<Value>(e, newSet, "exp");

    out->backward = [self = shared_from_this(), out]()
    {
        self->grad += out->data * out->grad;
    };

    return out;
}

std::shared_ptr<Value> Value::pow(float exp) {
    auto newSet = std::set<std::shared_ptr<Value>>{shared_from_this()};
    float p = std::pow(this->data, exp);
    auto out = std::make_shared<Value>(p, newSet, "^" + std::to_string(exp));

    out->backward = [self = shared_from_this(), exp, out]()
    {
        self->grad += exp * std::pow(self->data, (exp - 1)) * out->grad;
    };

    return out;
}

void Value::print(int level = 0) const {
    std::cout << std::string(level * 2, ' ') << " | " << label << " - " << "Value: " 
        << data << " Grad: " << grad << " " << op << std::endl;

    for (const auto& child : prev) {
        child->print(level + 1);
    }
}