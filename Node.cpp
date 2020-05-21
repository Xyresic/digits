#include <iostream>
#include "Node.h"

Node::Node(function<long double(long double)> actualizer) {
    this->actualizer = actualizer;
}

Node::~Node() {

}

void Node::set_receivers(vector<Node> receivers) {
    this->receivers = receivers;
}

void Node::set_params(vector<long double> weights, long double bias) {
    this->weights = weights;
    this->bias = bias;
}

void Node::add_input(long double input) {
    inputs.push_back(input);
}

void Node::compute() {
    for (int i = 0; i < inputs.size(); i++) {
        output += inputs[i] * weights[i];
    }
    output = actualizer(output + bias);
    inputs.clear();
}

void Node::propagate() {
    for (Node receiver : receivers) {
        receiver.inputs.push_back(output);
    }
}