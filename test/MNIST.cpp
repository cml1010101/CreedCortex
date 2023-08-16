#include <CreedCortex.hpp>
#include <fstream>
using namespace creed;
using namespace std;
int main(int argc, const char* argv[])
{
    xt::random::seed(123);
    Sequential model = Sequential(
        {
            std::make_shared<Dense>(392),
            std::make_shared<Sigmoid>(),
            std::make_shared<Dense>(196),
            std::make_shared<Sigmoid>(),
            std::make_shared<Dense>(10),
            std::make_shared<Sigmoid>(),
        }
    );
    ifstream in("datasets/mnist.csv");
    xt::xarray<int> data = xt::load_csv<int>(in);
    Matrix x = xt::view(data, xt::all(), xt::range(0, 784)) / 255.0;
    xt::xarray<int> yLabels = xt::view(data, xt::all(), 784);
    yLabels = yLabels.reshape({70000});
    Matrix y = xt::zeros<double>({70000, 10});
    for (size_t i = 0; i < 70000; i++)
    {
        y(i, yLabels(i)) = 1.0;
    }
    Matrix xTrain = xt::view(x, xt::range(0, 50000), xt::all());
    Matrix yTrain = xt::view(y, xt::range(0, 50000), xt::all());
    Matrix xTest = xt::view(x, xt::range(50000, 50200), xt::all());
    Matrix yTest = xt::view(y, xt::range(50000, 50200), xt::all());
    xTrain = xTrain.reshape({500, 100, 784}, xt::layout_type::row_major);
    yTrain = yTrain.reshape({500, 100, 10}, xt::layout_type::row_major);
    model.fit(1, xTrain, yTrain, xTest, yTest, {new MSE(), new Accuracy()}, new SimpleDerivative(), new SGD(0.01),
        [](size_t epoch, size_t batch, Matrix error) {
            cout << "Epoch #" << epoch + 1 << ", batch #" << batch + 1 << endl;
            cout << "Error: " << error[0] << endl << "Accuracy: " << error[1] * 100 << "%" << endl;
        }
    );
    return 0;
}