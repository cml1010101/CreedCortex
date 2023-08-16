#ifndef CREEDMETRIC_HPP
#define CREEDMETRIC_HPP
#include <CreedCore.hpp>
namespace creed
{
    class Metric
    {
    public:
        virtual double calculate(Matrix y, Matrix yHat) = 0;
    };
}
#endif