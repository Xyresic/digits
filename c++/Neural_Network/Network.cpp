#include <iostream>
#include <fstream>
#include <cmath>
#include <random>

#include "Node.h"
#include "Network.h"

/* neural network */
//create activator function
double swish(double x) {
    return x / (1 + exp(-x));
}
std::function<double(double)> sigma = swish;
//activator derivative
double swish_prime(double x) {
    return (1 + exp(-x) * (x + 1)) / pow(1 + exp(-x), 2);
}
std::function<double(double)> sigma_prime = swish_prime;

//cost function (quadratic)
double cost(const std::vector<double>& results, const std::vector<double>& expected) {
    double cost = 0;
    for (int i = 0; i < results.size(); i++) {
        double diff = results[i] - expected[i];
        cost += diff * diff;
    }
    return cost;
}

std::string path = ".\\params.dat";

std::default_random_engine engine;
std::uniform_real_distribution<double> distribution(-0.5, 0.5);

std::vector<double> confidences;
std::vector<std::shared_ptr<Node>> top;

/* utility */
//get index of element from vector
template <class generic>
int vec_index(const std::vector<generic>& vec, const generic& ele) {
    return distance(vec.begin(), find(vec.begin(), vec.end(), ele));
}

/* debug */
template <class iterable>
void print_iterable(const iterable& iter) {
    if (iter.empty()) {
        std::cout << "[]" << std::endl;
    } else {
        std::string result = "[";
        for (auto item : iter) {
            result += std::to_string(item) + ' ';
        }
        std::cout << result.substr(0, result.size() - 1) << ']' << std::endl;
    }
}

std::string to_string(Node input) {
    return std::to_string(input.get_output());
}

void link_layers(std::vector<std::shared_ptr<Node>>& top, std::vector<std::shared_ptr<Node>>& carriage) {
    if (!top.empty()) {
        for (auto &node : carriage) {
            node->set_receivers(top);
        }
        for (auto &node : top) {
            node->set_senders(carriage);
        }
    }
    top = carriage;
    carriage.clear();
}

void initialize_layer(std::ofstream& file, int nodes, int weights) {
    for (int i = 0; i < nodes; i++) {
        file << 0 << ',';
        for (int j = 0; j < weights; j++) {
            file << distribution(engine) << ',';
        }
        file << '\n';
    }
}

void initialize_network() {
    std::ofstream parameters(path);
    if (parameters.is_open()) {
        initialize_layer(parameters, 10, 10);
        parameters << '\n';
        initialize_layer(parameters, 10, 100);
        parameters << '\n';
        initialize_layer(parameters, 100, 900);
        parameters << "end";
    } else {
        std::cout << "Unable to open file." << std::endl;
    }

    parameters.close();
}

int run_network(double* inputs) {
    top.clear();
    confidences.clear();

    std::ifstream parameters(path);
    std::vector<std::shared_ptr<Node>> carriage;
    std::string line;

    //create network
    if (parameters.is_open()) {
        while (getline(parameters, line)) {
            if (line.empty() || line == "end") {
                link_layers(top, carriage);
                if (line == "end") {
                    for (auto& i : top[0]->get_weights()) {
                        std::vector<double> weights;
                        carriage.emplace_back(std::make_shared<Node>(weights, 0));
                    }
                    link_layers(top, carriage);
                }
            } else {
                size_t pos;
                std::vector<double> weights;

                double bias = stod(line, &pos);
                line = line.substr(pos + 1);
                while (!line.empty()) {
                    weights.push_back(stod(line, &pos));
                    line = line.substr(pos + 1);
                }

                carriage.emplace_back(std::make_shared<Node>(weights, bias));
            }
        }
    } else {
        std::cout << "Unable to open file." << std::endl;
    }
    parameters.close();

    //retrieve inputs from GUI
    for (int i = 0; i < top.size(); i++) {
        top[i]->set_input(inputs[i]);
    }

    //feed forwards
    while (!top[0]->is_last()) {
        for (auto& node : top) {
            node->compute(sigma);
        }
        top = top[0]->receiver_ptrs();
    }

    //get result
    for (auto& node : top) {
        node->compute(sigma);
        confidences.push_back(node->get_output());
    }
    std::cout << "Results: ";
    print_iterable(confidences);
    return vec_index(confidences, *max_element(confidences.begin(), confidences.end()));
}

void descend_gradient(std::vector<double> expected) {
    std::cout << "Expected: ";
    print_iterable(expected);
    std::cout << "Cost: " << cost(confidences, expected) << std::endl;

    //backpropagation
    std::ofstream parameters(path);
    while (!top[0]->is_first()) {
        for (int i = 0; i < top.size(); i++) {
            if (top[i]->is_last()) {
                top[i]->descend(sigma_prime, expected[i]);
            } else {
                top[i]->descend(sigma_prime, i);
            }
            Parameters new_params = top[i]->get_new_params();
            parameters << new_params.bias << ',';
            for (auto weight : new_params.weights) {
                parameters << weight << ',';
            }
            parameters << '\n';
        }
        top = top[0]->sender_ptrs();
        if (!top[0]->is_first()) {
            parameters << '\n';
        }
    }
    parameters << "end";
    parameters.close();
}