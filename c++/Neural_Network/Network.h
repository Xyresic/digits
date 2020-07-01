#ifndef DIGITS_NETWORK_H
#define DIGITS_NETWORK_H

#include <vector>

void initialize_network();
void run_network(double* inputs);
void descend_gradient(std::vector<double> expected);

#endif //DIGITS_NETWORK_H
