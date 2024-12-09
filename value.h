#include "string"
#include <set>
#include <stack>
#include <vector>
#include <functional>
#include <memory>

class Value : public std::enable_shared_from_this<Value> {
    public:
        float data;
        float grad;
        std::set<std::shared_ptr<Value>> prev;
        std::string op;
        std::function<void()> backward = []() {};

        Value(float data);
        Value(float data, std::set<std::shared_ptr<Value>>& children, const std::string& op);

        void print(int level) const;
        std::shared_ptr<Value> tanh();

        void buildGrads();

    friend std::shared_ptr<Value> operator+(const std::shared_ptr<Value>& lhs, const std::shared_ptr<Value>& rhs) {
        auto newSet = std::set<std::shared_ptr<Value>>{lhs, rhs};
        auto out = std::make_shared<Value>(lhs->data + rhs->data, newSet, "+");

        out->backward = [lhs, rhs, out]() {
            lhs->grad += 1.0 * out->grad;
            rhs->grad += 1.0 * out->grad;
        };

        return out;
    }

    friend std::shared_ptr<Value> operator+(const std::shared_ptr<Value>& lhs, int rhs) {
        auto other = std::make_shared<Value>(rhs);
        auto newSet = std::set<std::shared_ptr<Value>>{lhs, other};
        auto out = std::make_shared<Value>(lhs->data + other->data, newSet, "+");

        out->backward = [lhs, other, out]() {
            lhs->grad += 1.0 * out->grad;
            other->grad += 1.0 * out->grad;
        };

        return out;
    }

    friend std::shared_ptr<Value> operator*(const std::shared_ptr<Value>& lhs, const std::shared_ptr<Value>& rhs) {
        auto newSet = std::set<std::shared_ptr<Value>>{lhs, rhs};
        auto out = std::make_shared<Value>(lhs->data * rhs->data, newSet, "*");

        out->backward = [lhs, rhs, out]() {
            lhs->grad += rhs->data * out->grad;
            rhs->grad += lhs->data * out->grad;
        };

        return out;
    }

    friend std::shared_ptr<Value> operator*(const std::shared_ptr<Value>& lhs, int rhs) {
        auto other = std::make_shared<Value>(rhs);
        auto newSet = std::set<std::shared_ptr<Value>>{lhs, other};
        auto out = std::make_shared<Value>(lhs->data * other->data, newSet, "*");

        out->backward = [lhs, other, out]() {
            lhs->grad += other->data * out->grad;
            other->grad += lhs->data * out->grad;
        };

        return out;
    }
};

std::ostream& operator<<(std::ostream& os, const Value& value)
{
    return os << value.data;
}

void buildTopoOrder(const std::shared_ptr<Value>& v, std::vector<std::shared_ptr<Value>>& topoOrder, std::set<Value*>& visited) {
    if (visited.count(v.get())) {
        return;
    }
    visited.insert(v.get());

    for (const auto& child : v->prev) {
        buildTopoOrder(child, topoOrder, visited);
    }
    topoOrder.push_back(v);
}