#include <iostream>
#include <chrono>

#include "Node.h"

using namespace std;
using namespace std::chrono;

long double rectlin(long double input) {
    return input > 0? input:0;
}
function<long double(long double)> RELU = rectlin;

int main() {
    //timing execution time
    //auto start = high_resolution_clock::now();
    //auto stop = high_resolution_clock::now();
    //auto duration = duration_cast<microseconds>(stop - start);
    //cout << duration.count();
    Node n(RELU);
    vector<long double> weights(2,1);
    n.set_params(weights, 0.5);
    n.add_input(0.457);
    n.add_input(0.2342);
    n.compute();
    cout << n.get_output() << endl;
    return 0;
}