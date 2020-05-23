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
    double lin_comb = 0;
    double output = 0;

public:
    Node(vector<double> weights, double bias);
    ~Node();

    double get_output() {return output;}
    vector<Node>* get_receivers() {return receivers;}

    void set_receivers(vector<Node>* receivers);

    void add_input(double input);
    bool is_last();
    void compute(function<double(double)> activator);
    void propagate();
};


#endif //DIGITS_NODE_H
