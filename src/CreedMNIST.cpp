#include <CreedMNIST.hpp>
extern "C" char _binary_datasets_mnist_csv_start;
extern "C" char _binary_datasets_mnist_csv_size;
using namespace creed;
std::tuple<Matrix, Matrix, Matrix, Matrix> creed::loadMNIST(size_t trainBatches, size_t trainBatchSize, size_t testSize)
{
    std::string mnistText(&_binary_datasets_mnist_csv_start, (size_t)&_binary_datasets_mnist_csv_size);
    std::istringstream stream(mnistText);
    Matrix data = xt::load_csv<int>(stream);
    Matrix x = xt::view(data, xt::all(), xt::range(0, 784)) / 255.0;
    xt::xarray<int> yLabels = xt::view(data, xt::all(), 784);
    yLabels = yLabels.reshape({70000});
    Matrix y = xt::zeros<double>({70000, 10});
    for (size_t i = 0; i < 70000; i++)
    {
        y(i, yLabels(i)) = 1.0;
    }
    Matrix xTrain = xt::view(x, xt::range(0, trainBatches * trainBatchSize), xt::all());
    Matrix yTrain = xt::view(y, xt::range(0, trainBatches * trainBatchSize), xt::all());
    Matrix xTest = xt::view(x, xt::range(trainBatches * trainBatchSize, trainBatches * trainBatchSize + testSize), xt::all());
    Matrix yTest = xt::view(y, xt::range(trainBatches * trainBatchSize, trainBatches * trainBatchSize + testSize), xt::all());
    xTrain = xTrain.reshape({trainBatches, trainBatchSize, 784}, xt::layout_type::row_major);
    yTrain = yTrain.reshape({trainBatches, trainBatchSize, 10}, xt::layout_type::row_major);
    return {xTrain, yTrain, xTest, yTest};
}