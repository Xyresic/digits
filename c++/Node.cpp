#include <iostream>

#include "Node.h"

Node::Node(function<double(double)> actualizer) {
    this->actualizer = actualizer;
}

Node::~Node() {

}

void Node::set_receivers(vector<Node> receivers) {
    this->receivers = receivers;
}

void Node::set_params(vector<double> weights, double bias) {
    this->weights = weights;
    this->bias = bias;
}

void Node::add_input(double input) {
    inputs.push_back(input);
}

bool Node::is_last() {
    return receivers.size() == 0;
}

void Node::compute() {
    for (int i = 0; i < inputs.size(); i++) {
        output += inputs[i] * weights[i];
    }
    output = actualizer(output + bias);
    inputs.clear();
}

void Node::propagate() {
    for (int i = 0; i < receivers.size(); i++) {
        receivers[i].add_input(output);
    }
}