#ifndef CREEDMSE_HPP
#define CREEDMSE_HPP
#include <CreedMetric.hpp>
namespace creed
{
    class MSE : public Metric
    {
    public:
        MSE() = default;
        virtual double calculate(Matrix y, Matrix yHat) override;
    };
}
#endif