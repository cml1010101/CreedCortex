#include <CreedCrossEntropy.hpp>
using namespace creed;
double CrossEntropy::calculate(Matrix y, Matrix yHat)
{
    return xt::sum(-yHat * xt::log(y) - (1 - yHat) * xt::log(1 - y))();
}