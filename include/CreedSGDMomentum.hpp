#ifndef CREEDSGDMOMENTUM_HPP
#define CREEDSGDMOMENTUM_HPP
#include <CreedOptimizer.hpp>
namespace creed
{
    class SGDMomentum : public Optimizer
    {
    private:
        double lr, momentum;
        std::vector<Matrix> velocity;
    public:
        SGDMomentum() = default;
        inline SGDMomentum(double lr, double momentum)
        {
            this->lr = lr;
            this->momentum = momentum;
        }
        virtual void optimize(std::vector<Matrix*> parameters, std::vector<Matrix*> parameterGradients) override;
    };
}
#endif