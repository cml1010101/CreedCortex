#ifndef CREEDDENSE_HPP
#define CREEDDENSE_HPP
#include <CreedLayer.hpp>
namespace creed
{
    class Dense : public Layer
    {
    private:
        Matrix w, b, wGrad, bGrad, x;
        size_t size;
        bool initialized;
    public:
        Dense() = default;
        Dense(size_t size);
        virtual Matrix forward(Matrix x) override;
        virtual Matrix backward(Matrix yGrad) override;
    };
}
#endif