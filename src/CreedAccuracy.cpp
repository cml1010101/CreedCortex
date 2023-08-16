#include <CreedAccuracy.hpp>
using namespace creed;
double Accuracy::calculate(Matrix y, Matrix yHat)
{
    return xt::argmax(y) == xt::argmax(yHat);
}