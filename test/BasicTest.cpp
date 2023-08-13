#include <CreedMatrix.hpp>
#include <iostream>
using namespace creed;
using namespace std;
int main(int argc, const char* argv[])
{
    Matrix<float, 1> vec = Matrix<float, 1>::ones({4});
    cout << vec << endl;
    return 0;
}