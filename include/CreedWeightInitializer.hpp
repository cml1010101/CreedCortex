#ifndef CREEDWEIGHTINITIALIZER_HPP
#define CREEDWEIGHTINITIALIZER_HPP
#include <CreedCore.hpp>
namespace creed
{
    class WeightInitializer
    {
    public:
        virtual Matrix initialize(std::vector<size_t> shape) = 0;
    };
}
#endif