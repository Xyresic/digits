#ifndef DIGITS_NODE_H
#define DIGITS_NODE_H


class Node {
private:
    long double weights[10];
    long double bias;
    long double actualizer();
    Node receivers[10];

public:
    long double inputs[10];

    Node();
    ~Node();

    void compute();
};


#endif //DIGITS_NODE_H
