#ifndef CREEDMNIST_HPP
#define CREEDMNIST_HPP
#include <CreedCore.hpp>
namespace creed
{
    std::tuple<Matrix, Matrix, Matrix, Matrix> loadMNIST(size_t trainBatches, size_t trainBatchSize, size_t testSize);
}
#endif