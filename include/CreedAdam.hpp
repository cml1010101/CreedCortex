#ifndef CREEDADAM_HPP
#define CREEDADAM_HPP
#include <CreedOptimizer.hpp>
namespace creed
{
    class Adam : public Optimizer
    {
    private:
        double lr, beta, gamma;
        size_t counter;
        std::vector<Matrix> momentum, velocity;
    public:
        Adam() = default;
        inline Adam(double lr, double beta, double gamma)
        {
            this->lr = lr;
            this->beta = beta;
            this->gamma = gamma;
            this->counter = 0;
        }
        virtual void optimize(std::vector<Matrix*> parameters, std::vector<Matrix*> parameterGradients) override;
    };
}
#endif