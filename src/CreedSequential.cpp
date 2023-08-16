#include <CreedSequential.hpp>
using namespace creed;
Sequential::Sequential(std::vector<std::shared_ptr<Layer>> layers)
{
    this->layers = layers;
    for (auto layer : this->layers)
    {
        parameters.reserve(parameters.size() + layer->getParameters().size());
        auto layerParameters = layer->getParameters();
        parameters.insert(parameters.end(), layerParameters.begin(), layerParameters.end());
        parameterGradients.reserve(parameterGradients.size() + layer->getParameterGradients().size());
        auto layerParameterGradients = layer->getParameterGradients();
        parameterGradients.insert(parameterGradients.end(), layerParameterGradients.begin(),
            layerParameterGradients.end());
    }
}
Matrix Sequential::forward(Matrix x)
{
    Matrix y = x;
    for (auto layer : this->layers)
    {
        y = layer->forward(y);
    }
    return y;
}
Matrix Sequential::backward(Matrix yGrad)
{
    Matrix xGrad = yGrad;
    for (int i = this->layers.size() - 1; i >= 0; i--)
    {
        xGrad = this->layers[i]->backward(xGrad);
    }
    return xGrad;
}
Matrix Sequential::train(Matrix x, Matrix yHat, std::vector<Metric*> metrics, Loss* loss)
{
    Matrix y = forward(x);
    Matrix yGrad = loss->calculate(y, yHat);
    backward(yGrad);
    Matrix errors = xt::empty<double>({metrics.size()});
    for (size_t i = 0; i < metrics.size(); i++)
    {
        errors[i] = metrics[i]->calculate(y, yHat);
    }
    return errors;
}
Matrix Sequential::test(Matrix x, Matrix yHat, std::vector<Metric*> metrics)
{
    Matrix y = forward(x);
    Matrix errors = xt::empty<double>({metrics.size()});
    for (size_t i = 0; i < metrics.size(); i++)
    {
        errors[i] = metrics[i]->calculate(y, yHat);
    }
    return errors;
}
Matrix Sequential::trainBatch(Matrix x, Matrix yHat, std::vector<Metric*> metrics, Loss* loss)
{
    Matrix errors = xt::zeros<double>({metrics.size()});
    for (size_t i = 0; i < x.shape(0); i++)
    {
        errors += train(xt::view(x, i), xt::view(yHat, i), metrics, loss);
    }
    return errors / x.shape(0);
}
Matrix Sequential::testBatch(Matrix x, Matrix yHat, std::vector<Metric*> metrics)
{
    Matrix errors = xt::zeros<double>({metrics.size()});
    for (size_t i = 0; i < x.shape(0); i++)
    {
        errors += test(xt::view(x, i), xt::view(yHat, i), metrics);
    }
    return errors / x.shape(0);
}
void Sequential::updateParameters(Optimizer* optimizer)
{
    optimizer->optimize(parameters, parameterGradients);
}
void Sequential::fit(size_t epochs, Matrix xTrain, Matrix yTrain, Matrix xTest, Matrix yTest, std::vector<Metric*> metrics,
    Loss* loss, Optimizer* optimizer, std::function<void(size_t, size_t, Matrix)> testBatchCallback)
{
    for (size_t e = 0; e < epochs; e++)
    {
        for (size_t i = 0; i < xTrain.shape(0); i++)
        {
            trainBatch(xt::view(xTrain, i), xt::view(yTrain, i), metrics, loss);
            updateParameters(optimizer);
            auto error = testBatch(xTest, yTest, metrics);
            testBatchCallback(e, i, error);
        }
    }
}