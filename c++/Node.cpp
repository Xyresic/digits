#include <iostream>

#include "Node.h"

Node::Node(const vector<double>& weights, double bias) {
    this->weights = weights;
    this->bias = bias;
}

void Node::set_input(double input) {
    this->input = input;
}

void Node::set_senders(const vector<shared_ptr<Node>>& senders) {
    this->senders = senders;
}

void Node::set_receivers(const vector<shared_ptr<Node>>& receivers) {
    this->receivers = receivers;
}

bool Node::is_last() {
    return receivers.empty();
}

void Node::compute(const function<double(double)>& activator) {
    if (!senders.empty()) {
        for (int i = 0; i < senders.size(); i++) {
            output += senders[i]->get_output() * weights[i];
        }
        lin_comb = output + bias;
    } else {
        lin_comb = input * weights[0] + bias;
    }
    output = activator(lin_comb);
}