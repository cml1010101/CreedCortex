#ifndef LAYER_HPP
#define LAYER_HPP
#include <CreedCore.hpp>
namespace creed
{
    class Layer
    {
    protected:
        std::vector<Matrix*> parameters;
        std::vector<Matrix*> parameterGradients;
    public:
        Layer() = default;
        virtual Matrix forward(Matrix x) = 0;
        virtual Matrix backward(Matrix yGrad) = 0;
        std::vector<Matrix*> getParameters();
        std::vector<Matrix*> getParameterGradients();
        friend std::ostream& operator<<(std::ostream& out, const Layer& layer);
        friend std::ostream& operator<<(std::ostream& out, Layer&& layer);
        friend std::istream& operator>>(std::istream& out, Layer& layer);
    };
    std::ostream& operator<<(std::ostream& out, const Layer& layer);
    std::ostream& operator<<(std::ostream& out, Layer&& layer);
    std::istream& operator>>(std::istream& out, Layer& layer);
}
#endif