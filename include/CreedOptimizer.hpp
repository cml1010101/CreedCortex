#ifndef CREEDOPTIMIZER_HPP
#define CREEDOPTIMIZER_HPP
#include <CreedCore.hpp>
namespace creed
{
    class Optimizer
    {
    public:
        virtual void optimize(std::vector<Matrix*> parameters, std::vector<Matrix*> parameterGradients) = 0;
    };
}
#endif