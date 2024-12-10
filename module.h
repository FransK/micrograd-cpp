#ifndef MODULE_H
#define MODULE_H

#include "value.h"
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <random>

// Base Module class
class Module {
public:
    virtual void zero_grad();
    virtual std::vector<std::shared_ptr<Value>> parameters();
    virtual ~Module() = default;
};

// Neuron class
class Neuron : public Module {
public:
    Neuron(int nin);

    std::shared_ptr<Value> operator()(const std::vector<std::shared_ptr<Value>>& x);
    std::vector<std::shared_ptr<Value>> parameters() override;
    std::string to_string() const;

private:
    std::vector<std::shared_ptr<Value>> w;
    std::shared_ptr<Value> b;
};

// Layer class
class Layer : public Module {
public:
    Layer(int nin, int nout);

    std::vector<std::shared_ptr<Value>> operator()(const std::vector<std::shared_ptr<Value>>& x);
    std::vector<std::shared_ptr<Value>> parameters() override;
    std::string to_string() const;

private:
    std::vector<Neuron> neurons;
};

// MLP class
class MLP : public Module {
public:
    MLP(int nin, const std::vector<int>& nouts);

    std::vector<std::shared_ptr<Value>> operator()(const std::vector<std::shared_ptr<Value>>& x);
    std::vector<std::shared_ptr<Value>> parameters() override;
    std::string to_string() const;

private:
    std::vector<Layer> layers;
};

#endif
