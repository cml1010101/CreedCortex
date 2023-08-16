#ifndef CREEDACTIVATIONS_HPP
#define CREEDACTIVATIONS_HPP
#include <CreedLayer.hpp>
namespace creed
{
    class Sigmoid : public Layer
    {
    private:
        Matrix y;
    public:
        Sigmoid() = default;
        virtual Matrix forward(Matrix x) override;
        virtual Matrix backward(Matrix yGrad) override;
    };
    class ReLU : public Layer
    {
    private:
        Matrix x;
        static double forward(double x);
        static double backward(double x, double yGrad);
    public:
        ReLU() = default;
        virtual Matrix forward(Matrix x) override;
        virtual Matrix backward(Matrix yGrad) override;
    };
}
#endif