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
double cost(const vector<double>& results, const vector<double>& expected) {
    double cost = 0;
    for (int i = 0; i < results.size(); i++) {
        double diff = results[i] - expected[i];
        cost += diff * diff;
    }
    return cost;
}

fstream parameters(".\\params.dat");

/* utility */
//get index of element from vector
template <class generic>
int vec_index(const vector<generic>& vec, const generic& ele) {
    return distance(vec.begin(), find(vec.begin(), vec.end(), ele));
}

string to_string(Node input) {
    return to_string(input.get_output());
}

/* debug */
template <class iterable>
void print_iterable(const iterable& iter) {
    if (iter.empty()) {
        cout << "[]" << endl;
    } else {
        string result = "[";
        for (auto item : iter) {
            result += to_string(item) + ' ';
        }
        cout << result.substr(0, result.size() - 1) << ']' << endl;
    }
}

int main() {
    vector<shared_ptr<Node>> top;
    vector<shared_ptr<Node>> carriage;
    vector<double> expected;
    string line;

    expected.push_back(1); //test value

    //create network
    if (parameters.is_open()) {
        while (getline(parameters, line)) {
            if (line.empty() || line == "end") {
                if (!top.empty()) {
                    for (auto& i : carriage) {
                        i->set_receivers(top);
                    }
                    for (auto& i : top) {
                        i->set_senders(carriage);
                    }
                }
                top = carriage;
                carriage.clear();
            } else {
                size_t pos;
                vector<double> weights;

                double bias = stod(line, &pos);
                line = line.substr(pos + 1);
                while (!line.empty()) {
                    weights.push_back(stod(line, &pos));
                    line = line.substr(pos + 1);
                }

                carriage.emplace_back(make_shared<Node>(weights, bias));
            }
        }
        parameters.close();
    } else {
        cout << "Unable to open file." << endl;
    }

    //retrieve inputs
    //get_inputs(); TODO (Simon)
    for (auto& i : top) {
        i->set_input(1);
    }

    //feed forwards
    while (!top[0]->is_last()) {
        for (auto& i : top) {
            i->compute(sigma);
        }
        top = top[0]->receiver_ptrs();
    }

    //get result
    vector<double> confidences;
    for (auto& i : top) {
        i->compute(sigma);
        confidences.push_back(i->get_output());
    }
    cout << "Results: ";
    print_iterable(confidences);
    //cout << vec_index(confidences, *max_element(confidences.begin(), confidences.end())) << endl;
    cout << "Expected: ";
    print_iterable(expected);
    cout << "Cost: " << cost(confidences, expected) << endl;

    //backpropagation


    //timing execution time
    //auto start = high_resolution_clock::now();
    //auto stop = high_resolution_clock::now();
    //auto duration = duration_cast<microseconds>(stop - start);
    //cout << duration.count();
    return 0;
}