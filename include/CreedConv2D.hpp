#ifndef CREEDCONV2D_HPP
#define CREEDCONV2D_HPP
#include <CreedLayer.hpp>
#include <CreedWeightInitializer.hpp>
namespace creed
{
    class Conv2D : public Layer
    {
    private:
        Matrix kernels, kernelGrads, b, bGrad, x;
        bool initialized;
        size_t filters;
        std::shared_ptr<WeightInitializer> weightInitializer;
        std::vector<size_t> strides, kernelSize;
    public:
        Conv2D() = default;
        Conv2D(size_t filters, std::vector<size_t> kernelSize, std::shared_ptr<WeightInitializer> weightInitializer,
            std::vector<size_t> strides = {1, 1});
        virtual Matrix forward(Matrix x) override;
        virtual Matrix backward(Matrix yGrad) override;
    };
}
#endif