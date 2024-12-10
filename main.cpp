#include <iostream>
#include "module.h"

int main() {
    std::vector<int> nouts = {4, 4, 1};
    auto n = std::make_shared<MLP>(3, nouts);

    std::cout << n->to_string() << std::endl;

    std::vector<std::vector<std::shared_ptr<Value>>> xs = {
        {std::make_shared<Value>(2.0), std::make_shared<Value>(3.0), std::make_shared<Value>(-1.0)}, 
        {std::make_shared<Value>(3.0), std::make_shared<Value>(-1.0), std::make_shared<Value>(0.5)}, 
        {std::make_shared<Value>(0.5), std::make_shared<Value>(1.0), std::make_shared<Value>(1.0)},
        {std::make_shared<Value>(1.0), std::make_shared<Value>(1.0), std::make_shared<Value>(-1.0)}
        };
    std::vector<std::shared_ptr<Value>> ys = {std::make_shared<Value>(1.0), std::make_shared<Value>(-1.0), std::make_shared<Value>(-1.0), std::make_shared<Value>(1.0)};

    for (int i = 0; i < 20; i++) {
        // Forward pass
        std::vector<std::vector<std::shared_ptr<Value>>> ypred;
        for (auto& x : xs) {
            ypred.emplace_back((*n)(x));
        }

        std::vector<std::shared_ptr<Value>> loss;
        // Iterate using iterators
        auto it_ys = ys.begin();
        auto it_ypred = ypred.begin();

        for (; it_ys != ys.end() && it_ypred != ypred.end(); ++it_ys, ++it_ypred) {
            auto ygt = it_ys;  // Ground truth value
            auto yout = it_ypred[0];  // Prediction value
            loss.push_back((yout[0] - ygt[0])->pow(2.0));
        }

        auto total_loss = std::accumulate(loss.begin(), loss.end(), loss[0]);

        // go backward
        n->zero_grad();
        total_loss->buildGrads();

        // update
        for (auto& p : n->parameters()) {
            p->data += -0.1 * p->grad;
        }

        std::cout << i << ": " << total_loss->data << std::endl;

        for (auto& pred : ypred) {
            std::cout << pred[0]->data << std::endl;
        }
    }

    return 0;
}