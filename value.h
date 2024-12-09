#include "string"
#include "set"
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

        bool operator<(const Value &rhs) const;

        void print(int level) const;
        std::shared_ptr<Value> tanh();

        friend std::shared_ptr<Value> operator+(const std::shared_ptr<Value>& lhs, const std::shared_ptr<Value>& rhs) {
            auto newSet = std::set<std::shared_ptr<Value>>{lhs, rhs};
            auto out = std::make_shared<Value>(lhs->data + rhs->data, newSet, "+");

            out->backward = [lhs, rhs, out]() {
                lhs->grad += 1.0 * out->grad;
                rhs->grad += 1.0 * out->grad;
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
};

std::ostream& operator<<(std::ostream& os, const Value& value)
{
    return os << value.data;
}