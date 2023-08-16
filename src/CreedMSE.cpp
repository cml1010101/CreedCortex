#include <CreedMSE.hpp>
using namespace creed;
double MSE::calculate(Matrix y, Matrix yHat)
{
    return xt::average(xt::square(y - yHat))[0];
}