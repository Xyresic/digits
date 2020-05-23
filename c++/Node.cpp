#include <iostream>

#include "Node.h"

Node::Node(vector<double> weights, double bias) {
    this->weights = weights;
    this->bias = bias;
}

Node::~Node() {

}

void Node::setReceivers(vector<Node>* receivers) {
    this->receivers = receivers;
}

void Node::addInput(double input) {
    inputs.push_back(input);
}

bool Node::isLast() {
    return receivers->size() == 0;
}

void Node::compute(function<double(double)> activator) {
    for (int i = 0; i < inputs.size(); i++) {
        output += inputs[i] * weights[i];
    }
    linComb = output + bias;
    output = activator(linComb);
    inputs.clear();
}

void Node::propagate() {
    for (int i = 0; i < receivers->size(); i++) {
        receivers->at(i).addInput(output);
    }
}