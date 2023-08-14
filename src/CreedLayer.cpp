#include <CreedLayer.hpp>
using namespace creed;
std::map<std::string, Matrix> Layer::getParameters()
{
    return parameters;

}
std::map<std::string, Matrix> Layer::getParameterGradients()
{
    return parameterGradients;
}