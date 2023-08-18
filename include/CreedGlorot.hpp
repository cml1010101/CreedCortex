#ifndef CREEDGLOROT_HPP
#define CREEDGLOROT_HPP
#include <CreedWeightInitializer.hpp>
namespace creed
{
    class Glorot : public WeightInitializer
    {
    public:
        virtual Matrix initialize(std::vector<size_t> shape) override;
    };
}
#endif