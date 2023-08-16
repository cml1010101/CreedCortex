#include <CreedLayer.hpp>
using namespace creed;
std::vector<Matrix*> Layer::getParameters()
{
    return parameters;
}
std::vector<Matrix*> Layer::getParameterGradients()
{
    return parameterGradients;
}