#include "value.h"
#include <iostream>
#include <cmath>

Value::Value(float data) {
    this->data = data;
    this->grad = 0.0;
    this->prev = std::set<Value*>{};
    this->op = "";
}

Value::Value(float data, std::set<Value*>& prev) {
    this->data = data;
    this->grad = 0.0;
    this->prev = prev;
    this->op = "";
}

Value::Value(float data, std::set<Value*>& prev, const std::string& op) {
    this->data = data;
    this->grad = 0.0;
    this->prev = prev;
    this->op = op;
}

bool Value::operator<(const Value& rhs) const {
    return this->data < rhs.data;
}

Value Value::operator+(Value& rhs) {
    std::set<Value*> newSet = {this, &rhs};
    Value out = Value(this->data + rhs.data, newSet, "+");

    out.backward = [this, &rhs, &out]()
    {
        this->grad = 1.0 * out.grad;
        rhs.grad = 1.0 * out.grad;
    };

    return out;
}

Value Value::operator*(Value& rhs) {
    std::set<Value*> newSet = {this, &rhs};
    Value out = Value(this->data * rhs.data, newSet, "*");

    out.backward = [this, &rhs, &out]()
    {
        this->grad = rhs.data * out.grad;
        rhs.grad = this->data * out.grad;
    };

    return out;
}

Value Value::tanh() {
    std::set<Value*> newSet = {this};
    float t = std::tanh(this->data);
    Value out = Value(t, newSet, "tanh");

    out.backward = [this, t]()
    {
        this->grad = (1 - std::pow(t, 2));
    };

    return out;
}

void Value::print(int level = 0) const {
    std::cout << std::string(level * 2, ' ') << "Value: " << data << " Grad: " << grad << " " << op << std::endl;

    for (const auto& child : prev) {
        child->print(level + 1);
    }
}