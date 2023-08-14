#include <iostream>
#include <CreedCortex.hpp>
using namespace creed;
using namespace std;
int main(int argc, const char* argv[])
{
    Matrix mat(3, 3);
    mat <<  1, 2, 3,
            4, 5, 6,
            7, 8, 9;
    Matrix otherMat(1, 3);
    otherMat << 2, 2, 2;
    cout << mat.cross(mat) << endl;
    // cout << mat.cross(otherMat) << endl;
    return 0;
}