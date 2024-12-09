#include "string"
#include "set"

class Value {
    public:
        float data;
        std::set<Value> prev;

        Value(float data);
        Value(float data, std::set<Value>& children);

        bool operator<(const Value &rhs) const;
        Value operator+(const Value &rhs) const;
        Value operator*(const Value &rhs) const;
};

std::ostream& operator<<(std::ostream& os, const Value& value)
{
    return os << value.data;
}