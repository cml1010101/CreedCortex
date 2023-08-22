#include <CreedActivations.hpp>
using namespace creed;
Matrix Sigmoid::forward(Matrix x)
{
    return this->y = (1 / (1 + xt::exp(-x)));
}
Matrix Sigmoid::backward(Matrix yGrad)
{
    return this->y * (1 - this->y) * yGrad;
}
double ReLU::forward(double x)
{
    return x > 0 ? x : 0;
}
Matrix ReLU::forward(Matrix x)
{
    this->x = x;
    return xt::vectorize(ReLU::forward)(x);
}
double ReLU::backward(double x, double yGrad)
{
    return x > 0 ? yGrad : 0;
}
Matrix ReLU::backward(Matrix yGrad)
{
    return xt::vectorize(ReLU::backward)(this->x, yGrad);
}
Matrix Softmax::forward(Matrix x)
{
    return xt::exp(x) / xt::sum(xt::exp(x));
}
Matrix Softmax::backward(Matrix yGrad)
{
    return yGrad;
}