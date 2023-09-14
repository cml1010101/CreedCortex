#include <CreedConv2D.hpp>
using namespace creed;
using namespace xt::placeholders;
Conv2D::Conv2D(size_t filters, std::vector<size_t> kernelSize, std::shared_ptr<WeightInitializer> weightInitializer,
    std::vector<size_t> strides)
{
    this->strides = strides;
    this->weightInitializer = weightInitializer;
    this->filters = filters;
    this->kernelSize = kernelSize;
    this->initialized = false;
    this->parameters = {&kernels, &b};
    this->parameterGradients = {&kernelGrads, &bGrad};
}
Matrix Conv2D::forward(Matrix x)
{
    this->x = x;
    std::vector<size_t> outputShape = {x.shape(1) - kernels.shape(1) + 1, x.shape(2) - kernels.shape(2) + 1};
    if (!this->initialized)
    {
        this->kernels = weightInitializer->initialize({filters, x.shape(0), kernelSize[0], kernelSize[1]});
        this->kernelGrads = xt::zeros_like(kernels);
        this->b = weightInitializer->initialize(outputShape);
        this->bGrad = xt::zeros_like(this->b);
    }
    Matrix y = b;
    for (size_t c = 0; c < x.shape(0); c++)
    {
        for (size_t f = 0; f < y.shape(0); f++)
        {
            for (size_t i = 0; i < outputShape[0]; i++)
            {
                for (size_t j = 0; j < outputShape[1]; j++)
                {
                    y(f, i, j) += xt::view(x, f, c);
                }
            }
        }
    }
    return y;
}