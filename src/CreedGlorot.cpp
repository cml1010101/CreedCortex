#include <CreedGlorot.hpp>
using namespace creed;
Matrix Glorot::initialize(std::vector<size_t> shape)
{
    double range = sqrt(6.0 / xt::sum(xt::adapt(shape))());
    return xt::random::rand<double>(shape, -range, range);
}