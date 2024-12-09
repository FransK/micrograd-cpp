#include "value.h"

Value::Value(float data) {
    this->data = data;
}

Value::Value(float data, std::set<Value>& prev) {
    this->data = data;
    this->prev = prev;
}

bool Value::operator<(const Value& rhs) const {
    return this->data < rhs.data;
}

Value Value::operator+(const Value& rhs) const {
    std::set<Value> newSet = {*this, rhs};
    Value out = Value((*this).data + rhs.data, newSet);
    return out;
}

Value Value::operator*(const Value& rhs) const {
    std::set<Value> newSet = {*this, rhs};
    Value out = Value((*this).data * rhs.data, newSet);
    return out;
}