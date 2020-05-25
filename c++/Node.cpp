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
    if (senders.empty()) {
        lin_comb = input * weights[0] + bias;
    } else {
        for (int i = 0; i < senders.size(); i++) {
            output += senders[i]->output * weights[i];
        }
        lin_comb = output + bias;
    }
    output = activator(lin_comb);
}

void Node::descend(const function<double(double)>& derivative, double expected) {
    del_b = -2 * (output - expected) * derivative(lin_comb);
    for(int i = 0; i < senders.size(); i++) {
        del_w.push_back(del_b * senders[i]->output);
    }
}

void Node::descend(const function<double (double)> &derivative, int index) {
    for (auto& i : receivers) {
        del_b += i->del_b * i->weights[index] * lin_comb;
    }
    if (senders.empty()){
        del_w.push_back(del_b * input);
    } else {
        for (int i = 0; i < senders.size(); i++) {
            del_w.push_back(del_b * senders[i]->output);
        }
    }
}