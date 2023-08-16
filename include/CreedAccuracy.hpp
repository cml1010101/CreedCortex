#ifndef CREEDACCURACY_HPP
#define CREEDACCURACY_HPP
#include <CreedMetric.hpp>
namespace creed
{
    class Accuracy : public Metric
    {
    public:
        virtual double calculate(Matrix y, Matrix yHat) override;
    };
}
#endif