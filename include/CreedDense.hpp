#ifndef CREEDDENSE_HPP
#define CREEDDENSE_HPP
#include <CreedLayer.hpp>
#include <CreedWeightInitializer.hpp>
namespace creed
{
    class Dense : public Layer
    {
    private:
        Matrix w, b, wGrad, bGrad, x;
        size_t size;
        bool initialized;
        std::shared_ptr<WeightInitializer> weightInitializer;
    public:
        Dense() = default;
        Dense(size_t size, std::shared_ptr<WeightInitializer> weightInitializer);
        virtual Matrix forward(Matrix x) override;
        virtual Matrix backward(Matrix yGrad) override;
    };
}
#endif