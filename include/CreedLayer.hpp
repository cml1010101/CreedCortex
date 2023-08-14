#ifndef LAYER_HPP
#define LAYER_HPP
#include <CreedCore.hpp>
namespace creed
{
    class Layer
    {
    protected:
        std::map<std::string, Matrix> parameters;
        std::map<std::string, Matrix> parameterGradients;
    public:
        Layer() = default;
        virtual Matrix forward(Matrix x) = 0;
        virtual Matrix backward(Matrix yGrad) = 0;
        std::map<std::string, Matrix> getParameters();
        std::map<std::string, Matrix> getParameterGradients();
    };
}
#endif