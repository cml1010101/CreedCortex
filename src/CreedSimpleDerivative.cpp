#include <CreedSimpleDerivative.hpp>
using namespace creed;
Matrix SimpleDerivative::calculate(Matrix y, Matrix yHat)
{
    return y - yHat;
}