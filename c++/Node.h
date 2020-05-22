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
    function<double(double)> actualizer;

    vector<Node>* receivers = new vector<Node>;
    double output = 0;

public:
    vector<double> inputs;

    Node(function<double(double)> actualizer);
    ~Node();

    //getters
    double get_output() {return output;}
    vector<Node>* get_receivers() {return receivers;}

    //setters
    void set_receivers(vector<Node>* receivers);
    void set_params(vector<double> weights, double bias);

    void add_input(double input);
    bool is_last();
    void compute();
    void propagate();
};


#endif //DIGITS_NODE_H
