#include <iostream>
#include <CreedCortex.hpp>
using namespace creed;
using namespace std;
int main(int argc, const char* argv[])
{
    xt::random::seed(123);
    Dense dense = Dense(3);
    Sigmoid sigmoid = Sigmoid();
    Matrix in = xt::random::rand({6}, -1.0);
    cout << in << endl;
    Matrix out = sigmoid.forward(dense.forward(in));
    cout << out << endl;
    Matrix grad = dense.backward(sigmoid.backward(out - xt::random::rand({3}, -1.0)));
    cout << grad << endl;
    return 0;
}