#ifndef DIGITS_NODE_H
#define DIGITS_NODE_H


#include <functional>
#include <vector>
#include <memory>

struct Parameters {
    double bias;
    std::vector<double> weights;
};

class Node {
    private:
        double input;

        //calculation parameters
        std::vector<double> weights;
        double bias;

        //connections
        std::vector<std::shared_ptr<Node>> senders;
        std::vector<std::shared_ptr<Node>> receivers;

        //backpropagation parameters
        double lin_comb;
        double output = 0;
        double del_b = 0;
        std::vector<double> del_w;

    public:
        Node(const std::vector<double>& weights, double bias);
        ~Node() = default;

        double get_output() {return output;}
        std::vector<double> get_weights() {return weights;}
        Parameters get_new_params();
        std::vector<std::shared_ptr<Node>> receiver_ptrs() {return receivers;}
        std::vector<std::shared_ptr<Node>> sender_ptrs() {return senders;}

        void set_input(double input);
        void set_senders(const std::vector<std::shared_ptr<Node>>& senders);
        void set_receivers(const std::vector<std::shared_ptr<Node>>& receivers);

        bool is_first();
        bool is_last();
        void compute(const std::function<double(double)>& activator);
        void descend(const std::function<double(double)>& derivative, double expected);
        void descend(const std::function<double(double)>& derivative, int index);
};


#endif //DIGITS_NODE_H