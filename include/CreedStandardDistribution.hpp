#ifndef CREEDSTANDARDDISTRIBUTION_HPP
#define CREEDSTANDARDDISTRIBUTION_HPP
#include <CreedWeightInitializer.hpp>
namespace creed
{
    class StandardDistribution : public WeightInitializer
    {
    public:
        virtual Matrix initialize(std::vector<size_t> shape) override;
    };
}
#endif