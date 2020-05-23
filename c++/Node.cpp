#include <iostream>

#include "Node.h"

Node::Node(vector<double> weights, double bias) {
    this->weights = weights;
    this->bias = bias;
}

Node::~Node() {

}

void Node::set_receivers(vector<Node>* receivers) {
    this->receivers = receivers;
}

void Node::add_input(double input) {
    inputs.push_back(input);
}

bool Node::is_last() {
    return receivers->size() == 0;
}

void Node::compute(function<double(double)> activator) {
    for (int i = 0; i < inputs.size(); i++) {
        output += inputs[i] * weights[i];
    }
    lin_comb = output + bias;
    output = activator(lin_comb);
    inputs.clear();
}

void Node::propagate() {
    for (int i = 0; i < receivers->size(); i++) {
        receivers->at(i).add_input(output);
    }
}