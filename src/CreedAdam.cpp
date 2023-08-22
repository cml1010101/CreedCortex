#include <CreedAdam.hpp>
using namespace creed;
void Adam::optimize(std::vector<Matrix*> parameters, std::vector<Matrix*> parameterGradients)
{
    if (velocity.size() != parameters.size() || momentum.size() != parameters.size())
    {
        velocity.clear();
        momentum.clear();
        for (size_t i = 0; i < parameters.size(); i++)
        {
            velocity.push_back(xt::zeros<double>(parameters[i]->shape()));
            momentum.push_back(xt::zeros<double>(parameters[i]->shape()));
        }
    }
    for (size_t i = 0; i < parameters.size(); i++)
    {
        velocity[i] = velocity[i] * gamma + (1 - gamma) * xt::square(*parameterGradients[i]);
        momentum[i] = momentum[i] * beta + (1 - beta) * *parameterGradients[i];
        auto v = velocity[i] / (1 - pow(gamma, counter + 1));
        auto m = momentum[i] / (1 - pow(beta, counter + 1));
        *parameters[i] -= (lr / sqrt(v + 1e-5)) * m;
        parameterGradients[i]->fill(0.0);
        counter++;
    }
}