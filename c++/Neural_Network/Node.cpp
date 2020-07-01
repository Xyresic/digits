#include <iostream>

#include "Node.h"

Node::Node(const std::vector<double>& weights, double bias) {
    this->weights = weights;
    this->bias = bias;
}

Parameters Node::get_new_params() {
    double new_bias = bias + del_b / (abs(del_b) > 1? 2 * abs(del_b):1);
    std::vector<double> new_weights;
    for (int i = 0; i < weights.size(); i++) {
        new_weights.push_back(weights[i] + del_w[i] / (abs(del_w[i]) > 1? 2 * abs(del_w[i]):1));
    }
    Parameters new_params = {new_bias, new_weights};
    return new_params;
}

void Node::set_input(double input) {
    this->input = input;
}

void Node::set_senders(const std::vector<std::shared_ptr<Node>>& senders) {
    this->senders = senders;
}

void Node::set_receivers(const std::vector<std::shared_ptr<Node>>& receivers) {
    this->receivers = receivers;
}

bool Node::is_first() {
    return senders.empty();
}

bool Node::is_last() {
    return receivers.empty();
}

void Node::compute(const std::function<double(double)>& activator) {
    if (senders.empty()) {
        lin_comb = input;
        output = input;
    } else {
        for (int i = 0; i < senders.size(); i++) {
            output += senders[i]->output * weights[i];
        }
        lin_comb = output + bias;
        output = activator(lin_comb);
    }
}

void Node::descend(const std::function<double(double)>& derivative, double expected) {
    del_b = -2 * (output - expected) * derivative(lin_comb);
    for(int i = 0; i < senders.size(); i++) {
        del_w.push_back(del_b * senders[i]->output);
    }
}

void Node::descend(const std::function<double (double)> &derivative, int index) {
    for (auto& node : receivers) {
        del_b += node->del_b * node->weights[index] * derivative(lin_comb);
    }
    for (int i = 0; i < senders.size(); i++) {
        del_w.push_back(del_b * senders[i]->output);
    }
}