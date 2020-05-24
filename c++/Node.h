#ifndef DIGITS_NODE_H
#define DIGITS_NODE_H


#include <functional>
#include <vector>
#include <memory>

using namespace std;

class Node {
private:
    //calculation parameters
    vector<double> weights;
    double bias;

    vector<shared_ptr<Node>> senders;
    vector<shared_ptr<Node>> receivers;
    double input;
    double lin_comb;
    double output = 0;

public:
    Node(const vector<double>& weights, double bias);
    ~Node() = default;

    double get_output() {return output;}
    double get_lin_comb() {return lin_comb;}
    vector<shared_ptr<Node>> receiver_ptrs() {return receivers;}
    vector<shared_ptr<Node>> sender_ptrs() {return senders;}

    void set_input(double input);
    void set_senders(const vector<shared_ptr<Node>>& senders);
    void set_receivers(const vector<shared_ptr<Node>>& receivers);

    bool is_last();
    void compute(const function<double(double)>& activator);
};


#endif //DIGITS_NODE_H
