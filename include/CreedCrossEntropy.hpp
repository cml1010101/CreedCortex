#ifndef CREEDCROSSENTROPY_HPP
#define CREEDCROSSENTROPY_HPP
#include <CreedMetric.hpp>
namespace creed
{
    class CrossEntropy : public Metric
    {
    private:
        virtual double calculate(Matrix y, Matrix yHat) override;
    };
}
#endif