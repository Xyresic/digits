#ifndef DIGITS_NODE_H
#define DIGITS_NODE_H


#include <functional>
#include <vector>

using namespace std;

class Node {
private:
    //calculation parameters
    vector<double> weights;
    double bias;

    vector<double> inputs;
    vector<Node>* receivers = new vector<Node>;
    double linComb = 0;
    double output = 0;

public:
    Node(vector<double> weights, double bias);
    ~Node();

    double getOutput() {return output;}
    vector<Node>* getReceivers() {return receivers;}

    void setReceivers(vector<Node>* receivers);

    void addInput(double input);
    bool isLast();
    void compute(function<double(double)> activator);
    void propagate();
};


#endif //DIGITS_NODE_H
