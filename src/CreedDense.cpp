// #include <CreedDense.hpp>
// using namespace creed;
// Dense::Dense(size_t size)
// {
//     this->size = size;
//     this->initialized = false;
//     this->b = Matrix::Random(this->size, 1);
//     this->bGrad = Matrix::Constant(this->size, 1, 0);
// }
// Matrix Dense::forward(Matrix x)
// {
//     this->x = x;
//     if (!this->initialized)
//     {
//         this->initialized = true;
//         size_t inputSize = x.size();
//         this->w = Matrix::Random(this->size, inputSize);
//         this->wGrad = Matrix::Constant(this->size, inputSize, 0);
//     }
//     return (w * x).colwise() + b;
// }
// Matrix Dense::backward(Matrix yGrad)
// {
//     bGrad += yGrad;
//     wGrad += yGrad * x;
//     return w.transpose() * yGrad;
// }