#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <chrono>

#include "Node.h"

using namespace std;
using namespace std::chrono;

/* neural network */
//create activator function
double swish(double x) {
    return x / (1 + exp(-x));
}
function<double(double)> sigma = swish;
//activator derivative
double sigma_prime(double x) {
    return (1 + exp(-x) * (x + 1)) / pow(1 + exp(-x), 2);
}

//cost function (quadratic)
double cost(vector<double> results, vector<double> expected) {
    double cost = 0;
    for (int i = 0; i < results.size(); i++) {
        double diff = results[i] - expected[i];
        cost += diff * diff;
    }
    return cost;
}

fstream parameters(".\\params.csv");

/* utility */
//get index of element from vector
template <class generic>
int vec_index(vector<generic> vec, generic ele) {
    return distance(vec.begin(), find(vec.begin(), vec.end(), ele));
}

/* debug */
template <class iterable>
void print_iterable(iterable iter) {
    string result = "[";
    for (auto item : iter) {
        result += to_string(item) + ' ';
    }
    cout << result.substr(0, result.size() - 1) << ']' << endl;
}

int main() {
    vector<Node> top;
    vector<Node> carriage;
    vector<double> expected;
    string line;

    //create network
    if (parameters.is_open()) {
        while (getline(parameters, line)) {
            if (line == "" || line == "end") {
                if (carriage.size() != 0) {
                    for (int i = 0; i < top.size(); i++) {
                        top[i].set_receivers(&carriage);
                    }
                }
                if (line != "end") {
                    carriage = top;
                    top.clear();
                }
            } else {
                size_t pos;
                vector<double> weights;

                double bias = stod(line, &pos);
                line = line.substr(pos + 1);
                while (line != "") {
                    weights.push_back(stod(line, &pos));
                    line = line.substr(pos + 1);
                }

                Node current(weights, bias);
                top.push_back(current);
            }
        }
        parameters.close();
    } else {
        cout << "Unable to open file." << endl;
    }

    //retrieve inputs
    //get_inputs(); TODO (Simon)
    for (int i = 0; i < top.size(); i++) {
        top[i].add_input(1);
    }

    //feed forwards
    while (!top.front().is_last()) {
        for (int i = 0; i < top.size(); i++) {
            top[i].compute(sigma);
            top[i].propagate();
        }
        top = *top.front().get_receivers();
    }

    //get result
    vector<double> confidences;
    for (int i = 0; i < top.size(); i++) {
        top[i].compute(sigma);
        confidences.push_back(top[i].get_output());
    }
    print_iterable(confidences);
    cout << vec_index(confidences, *max_element(confidences.begin(), confidences.end()));

    //backpropagation


    //timing execution time
    //auto start = high_resolution_clock::now();
    //auto stop = high_resolution_clock::now();
    //auto duration = duration_cast<microseconds>(stop - start);
    //cout << duration.count();
    return 0;
}