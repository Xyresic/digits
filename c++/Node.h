#ifndef DIGITS_NODE_H
#define DIGITS_NODE_H


#include <functional>
#include <vector>
#include <memory>

using namespace std;

class Node {
private:
    double input;

    //calculation parameters
    vector<double> weights;
    double bias;

    //connections
    vector<shared_ptr<Node>> senders;
    vector<shared_ptr<Node>> receivers;

    //backpropagation parameters
    double lin_comb;
    double output = 0;
    double del_b = 0;
    vector<double> del_w;

public:
    Node(const vector<double>& weights, double bias);
    ~Node() = default;

    double get_output() {return output;}
    vector<shared_ptr<Node>> receiver_ptrs() {return receivers;}
    vector<shared_ptr<Node>> sender_ptrs() {return senders;}

    void set_input(double input);
    void set_senders(const vector<shared_ptr<Node>>& senders);
    void set_receivers(const vector<shared_ptr<Node>>& receivers);

    bool is_last();
    void compute(const function<double(double)>& activator);
    void descend(const function<double(double)>& derivative, double expected);
    void descend(const function<double(double)>& derivative, int index);
};


#endif //DIGITS_NODE_H
