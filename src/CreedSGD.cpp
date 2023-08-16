#include <CreedSGD.hpp>
using namespace creed;
void SGD::optimize(std::vector<Matrix*> parameters, std::vector<Matrix*> parameterGradients)
{
    for (size_t i = 0; i < parameters.size(); i++)
    {
        *parameters[i] -= this->lr * *parameterGradients[i];
        parameterGradients[i]->fill(0);
    }
}