#include <iostream>
#include "module.h"

using namespace std;

int main() {
    vector<int> nouts = {4, 4, 1};
    auto n = make_shared<MLP>(3, nouts);

    cout << n->to_string() << endl;

    vector<vector<shared_ptr<Value>>> xs = {
        {make_shared<Value>(2.0), make_shared<Value>(3.0), make_shared<Value>(-1.0)}, 
        {make_shared<Value>(3.0), make_shared<Value>(-1.0), make_shared<Value>(0.5)}, 
        {make_shared<Value>(0.5), make_shared<Value>(1.0), make_shared<Value>(1.0)},
        {make_shared<Value>(1.0), make_shared<Value>(1.0), make_shared<Value>(-1.0)}
        };
    vector<shared_ptr<Value>> ys = {make_shared<Value>(1.0), make_shared<Value>(-1.0), make_shared<Value>(-1.0), make_shared<Value>(1.0)};

    for (int i = 0; i < 10000; i++) {
        // Forward pass
        vector<vector<shared_ptr<Value>>> ypred;
        for (auto& x : xs) {
            ypred.emplace_back((*n)(x));
        }

        // Add up the squared differences between y and ypred
        vector<shared_ptr<Value>> ys = {make_shared<Value>(1.0), make_shared<Value>(-1.0), make_shared<Value>(-1.0), make_shared<Value>(1.0)};
        auto loss = accumulate(ys.begin(), ys.end(), make_shared<Value>(0.0), [&](const auto &acc, const auto &yi) { 
                auto diff = ypred[&yi - &ys[0]][0] - yi;
                return acc + diff->pow(2.0); });

        // go backward
        n->zero_grad();
        loss->buildGrads();

        // update
        for (auto& p : n->parameters()) {
            p->data += -0.01 * p->grad;
        }

        cout << i << ": " << loss->data << endl;

        for (auto& pred : ypred) {
            cout << pred[0]->data << endl;
        }
    }

    return 0;
}