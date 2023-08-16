#ifndef CREEDSGD_HPP
#define CREEDSGD_HPP
#include <CreedOptimizer.hpp>
namespace creed
{
    class SGD : public Optimizer
    {
    private:
        double lr;
    public:
        SGD() = default;
        inline SGD(double lr)
        {
            this->lr = lr;
        }
        virtual void optimize(std::vector<Matrix*> parameters, std::vector<Matrix*> parameterGradients) override;
    };
}
#endif