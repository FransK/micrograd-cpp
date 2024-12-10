#include <iostream>
#include "module.h"

int main() {
    auto x = std::vector<std::shared_ptr<Value>>{
        std::make_shared<Value>(2.0),
        std::make_shared<Value>(3.0),
    };

    auto n = std::make_shared<Layer>(2, 3);
    auto v = (*n)(x);

    std::cout << n->to_string() << std::endl;

    for (auto& neuron : v) {
        std::cout << neuron->data << std::endl;
    }

    return 0;
}