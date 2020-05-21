#ifndef DIGITS_NODE_H
#define DIGITS_NODE_H


#include <functional>
#include <vector>

using namespace std;

class Node {
private:
    //calculation parameters
    vector<long double> weights;
    long double bias;
    function<long double(long double)> actualizer;

    vector<Node> receivers;
    long double output = 0;

public:
    vector<long double> inputs;

    Node(function<long double(long double)> actualizer);
    ~Node();

    //getters
    long double get_output() {return output;}

    //setters
    void set_receivers(vector<Node> receivers);
    void set_params(vector<long double> weights, long double bias);

    void add_input(long double input);
    void compute();
    void propagate();
};


#endif //DIGITS_NODE_H
