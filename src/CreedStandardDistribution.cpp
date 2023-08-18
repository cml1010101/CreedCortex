#include <CreedStandardDistribution.hpp>
using namespace creed;
Matrix StandardDistribution::initialize(std::vector<size_t> shape)
{
    return xt::random::rand<double>(shape, -1);
}