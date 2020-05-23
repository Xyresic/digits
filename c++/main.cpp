#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>

#include "Node.h"

using namespace std;
using namespace std::chrono;

//create activator function
double rectLin(double input) {
    return input * (input > 0);
}
function<double(double)> RELU = rectLin;
//activator derivative
double reluPrime(double input) {
    return input > 0;
}

fstream parameters(".\\params.csv");

//get index of element from vector
int index(vector<double> vec, double ele) {
    return distance(vec.begin(), find(vec.begin(), vec.end(), ele));
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

int main() {
    vector<Node> top;
    vector<Node> carriage;
    string line;

    //create network
    if (parameters.is_open()) {
        while (getline(parameters, line)) {
            if (line == "" || line == "end") {
                if (carriage.size() != 0) {
                    for (int i = 0; i < top.size(); i++) {
                        top[i].setReceivers(&carriage);
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
        top[i].addInput(1);
    }

    //feed forwards
    while (!top.front().isLast()) {
        for (int i = 0; i < top.size(); i++) {
            top[i].compute(RELU);
            top[i].propagate();
        }
        top = *top.front().getReceivers();
    }

    //get result
    vector<double> confidences;
    for (int i = 0; i < top.size(); i++) {
        top[i].compute(RELU);
        confidences.push_back(top[i].getOutput());
    }
    cout << confidences[0] << endl;
    cout << index(confidences, *max_element(confidences.begin(), confidences.end()));

    //timing execution time
    //auto start = high_resolution_clock::now();
    //auto stop = high_resolution_clock::now();
    //auto duration = duration_cast<microseconds>(stop - start);
    //cout << duration.count();
    return 0;
}