#include <CreedSGDMomentum.hpp>
using namespace creed;
void SGDMomentum::optimize(std::vector<Matrix*> parameters, std::vector<Matrix*> parameterGradients)
{
    if (velocity.size() != parameters.size())
    {
        velocity.clear();
        for (size_t i = 0; i < parameters.size(); i++)
        {
            velocity.push_back(xt::zeros<double>(parameters[i]->shape()));
        }
    }
    for (size_t i = 0; i < parameters.size(); i++)
    {
        velocity[i] *= this->momentum;
        velocity[i] += this->lr * *parameterGradients[i];
        *parameters[i] -= velocity[i];
        parameterGradients[i]->fill(0);
    }
}