#include "value.h"
#include <iostream>

Value::Value(float data) {
    this->data = data;
    this->prev = std::set<Value>{};
    this->op = "";
}

Value::Value(float data, std::set<Value>& prev) {
    this->data = data;
    this->prev = prev;
    this->op = "";
}

Value::Value(float data, std::set<Value>& prev, std::string op) {
    this->data = data;
    this->prev = prev;
    this->op = op;
}

void Value::print(int level = 0) const {
        std::cout << std::string(level * 2, ' ') << "Value: " << data << " " << op << std::endl;

        for (const auto& child : prev) {
            child.print(level + 1);
        }
    }

bool Value::operator<(const Value& rhs) const {
    return this->data < rhs.data;
}

Value Value::operator+(const Value& rhs) const {
    std::set<Value> newSet = {*this, rhs};
    Value out = Value((*this).data + rhs.data, newSet, "+");
    return out;
}

Value Value::operator*(const Value& rhs) const {
    std::set<Value> newSet = {*this, rhs};
    Value out = Value((*this).data * rhs.data, newSet, "*");
    return out;
}