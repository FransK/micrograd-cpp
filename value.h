#include "string"
#include "set"
#include <functional>
#include <memory>

class Value {
    public:
        float data;
        float grad;
        std::set<Value*> prev;
        std::string op;

        Value(float data);
        Value(float data, std::set<Value*>& children);
        Value(float data, std::set<Value*>& children, const std::string& op);

        bool operator<(const Value &rhs) const;
        Value operator+(Value &rhs);
        Value operator*(Value &rhs);

        void print(int level) const;
        Value tanh();
        std::function<void()> backward = []() {};
};

std::ostream& operator<<(std::ostream& os, const Value& value)
{
    return os << value.data;
}