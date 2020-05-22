#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>

#include "Node.h"

using namespace std;
using namespace std::chrono;

//create actualization function
double rectlin(double input) {
    return input > 0? input:0;
}
function<double(double)> RELU = rectlin;

//read file
fstream parameters(".\\params.csv");

//get index of element from vector
int index(vector<double> vec, double ele) {
    return distance(vec.begin(), find(vec.begin(), vec.end(), ele));
}

int main() {
    vector<Node> top;
    vector<Node> carriage;
    string line;

    //create network
    if (parameters.is_open()) {
        while (getline(parameters, line)) {
            if (line == "" || line == "end") {
                for (int i = 0; i < top.size(); i++) {
                    top[i].set_receivers(carriage);
                }
                if (line != "end") {
                    carriage = top;
                    top.clear();
                }
            } else {
                Node current(RELU);
                size_t pos;
                vector<double> weights;

                double bias = stod(line, &pos);
                line = line.substr(pos + 1);
                while (line != "") {
                    weights.push_back(stod(line, &pos));
                    line = line.substr(pos + 1);
                }

                current.set_params(weights, bias);
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

    //cout << top.front().get_receivers().size() << endl;
    //propagate forwards

    while (!top.front().is_last()) {
        for (int i = 0; i < top.size(); i++) {
            top[i].compute();
            top[i].propagate();
        }

        cout << top.front().get_receivers().front().inputs.back() << endl;
        cout << top.back().get_receivers().front().inputs.back() << endl;
        top = top.front().get_receivers();
    }

    //get result
    vector<double> confidences;
    for (int i = 0; i < top.size(); i++) {
        top[i].compute();
        confidences.push_back(top[i].get_output());
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