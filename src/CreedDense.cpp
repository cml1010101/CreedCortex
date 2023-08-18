#include <CreedDense.hpp>
using namespace creed;
Dense::Dense(size_t size, std::shared_ptr<WeightInitializer> weightInitializer)
{
    this->weightInitializer = weightInitializer;
    this->size = size;
    this->initialized = false;
    this->b = weightInitializer->initialize({this->size});
    this->bGrad = xt::zeros_like(this->b);
    this->parameters = {&w, &b};
    this->parameterGradients = {&wGrad, &bGrad};
}
Matrix Dense::forward(Matrix x)
{
    this->x = x;
    if (!this->initialized)
    {
        this->initialized = true;
        size_t inputSize = x.size();
        this->w = this->weightInitializer->initialize({this->size, inputSize});
        this->wGrad = xt::zeros_like(this->w);
    }
    return xt::linalg::dot(w, x) + b;
}
Matrix Dense::backward(Matrix yGrad)
{
    this->bGrad += yGrad;
    this->wGrad += xt::linalg::outer(yGrad, x);
    return xt::linalg::dot(xt::transpose(w), yGrad);
}