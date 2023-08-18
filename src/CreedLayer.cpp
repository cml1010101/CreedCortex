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
std::ostream& creed::operator<<(std::ostream& out, const Layer& layer)
{
    nlohmann::json json;
    for (size_t i = 0; i < layer.parameters.size(); i++)
    {
        json[i] = *layer.parameters[i];
    }
    out << json;
    return out;
}
std::ostream& creed::operator<<(std::ostream& out, Layer&& layer)
{
    nlohmann::json json;
    for (size_t i = 0; i < layer.parameters.size(); i++)
    {
        json[i] = *layer.parameters[i];
    }
    out << json;
    return out;
}
std::istream& creed::operator>>(std::istream& in, Layer& layer)
{
    nlohmann::json json;
    in >> json;
    for (size_t i = 0; i < layer.parameters.size(); i++)
    {
        *layer.parameters[i] = json[i];
    }
    return in;
}