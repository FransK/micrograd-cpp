#include "module.h"
#include <numeric>
#include <iostream>

// Helper function for random initialization
float random_uniform(float low, float high) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(low, high);
    return dis(gen);
}

// Module methods
void Module::zero_grad() {
    for (auto& p : parameters()) {
        p->grad = 0.0f;
    }
}

std::vector<std::shared_ptr<Value>> Module::parameters() {
    return {};
}

// Neuron methods
Neuron::Neuron(int nin, bool nonlin) : nonlin(nonlin) {
    for (int i = 0; i < nin; ++i) {
        w.push_back(std::make_shared<Value>(random_uniform(-1.0, 1.0)));
    }
    b = std::make_shared<Value>(random_uniform(-1.0, 1.0));
}

std::shared_ptr<Value> Neuron::operator()(const std::vector<std::shared_ptr<Value>>& x) {
    auto act = std::accumulate(w.begin(), w.end(), b, [&](const auto& acc, const auto& wi) {
        return acc + (wi * x[&wi - &w[0]]);
    });
    return nonlin ? act->tanh() : act;
}

std::vector<std::shared_ptr<Value>> Neuron::parameters() {
    auto params = w;
    params.push_back(b);
    return params;
}

std::string Neuron::to_string() const {
    return (nonlin ? "ReLU" : "Linear") + std::string("Neuron(") + std::to_string(w.size()) + ")";
}

// Layer methods
Layer::Layer(int nin, int nout, bool nonlin) {
    for (int i = 0; i < nout; ++i) {
        neurons.emplace_back(nin, nonlin);
    }
}

std::vector<std::shared_ptr<Value>> Layer::operator()(const std::vector<std::shared_ptr<Value>>& x) {
    std::vector<std::shared_ptr<Value>> out;
    for (auto& neuron : neurons) {
        out.push_back(neuron(x));
    }
    return out;
}

std::vector<std::shared_ptr<Value>> Layer::parameters() {
    std::vector<std::shared_ptr<Value>> params;
    for (auto& neuron : neurons) {
        auto neuron_params = neuron.parameters();
        params.insert(params.end(), neuron_params.begin(), neuron_params.end());
    }
    return params;
}

std::string Layer::to_string() const {
    std::ostringstream oss;
    oss << "Layer of [";
    for (const auto& neuron : neurons) {
        oss << neuron.to_string() << ", ";
    }
    oss << "]";
    return oss.str();
}

// MLP methods
MLP::MLP(int nin, const std::vector<int>& nouts) {
    int input_size = nin;
    for (size_t i = 0; i < nouts.size(); ++i) {
        layers.emplace_back(input_size, nouts[i], i != nouts.size() - 1);
        input_size = nouts[i];
    }
}

std::vector<std::shared_ptr<Value>> MLP::operator()(const std::vector<std::shared_ptr<Value>>& x) {
    std::vector<std::shared_ptr<Value>> out = x;
    for (auto& layer : layers) {
        out = layer(out);
    }
    return out;
}

std::vector<std::shared_ptr<Value>> MLP::parameters() {
    std::vector<std::shared_ptr<Value>> params;
    for (auto& layer : layers) {
        auto layer_params = layer.parameters();
        params.insert(params.end(), layer_params.begin(), layer_params.end());
    }
    return params;
}

std::string MLP::to_string() const {
    std::ostringstream oss;
    oss << "MLP of [";
    for (const auto& layer : layers) {
        oss << layer.to_string() << ", ";
    }
    oss << "]";
    return oss.str();
}
