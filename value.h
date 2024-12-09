#include "string"
#include "set"

class Value {
    public:
        float data;
        std::set<Value> prev;
        std::string op;

        Value(float data);
        Value(float data, std::set<Value>& children);
        Value(float data, std::set<Value>& children, std::string op);

        bool operator<(const Value &rhs) const;
        Value operator+(const Value &rhs) const;
        Value operator*(const Value &rhs) const;

        void print(int level) const;
};

std::ostream& operator<<(std::ostream& os, const Value& value)
{
    return os << value.data;
}