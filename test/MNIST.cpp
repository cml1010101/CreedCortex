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
    auto data = loadMNIST(500, 100, 200);
    auto xTrain = std::get<0>(data);
    auto yTrain = std::get<1>(data);
    auto xTest = std::get<2>(data);
    auto yTest = std::get<3>(data);
    model.fit(1, xTrain, yTrain, xTest, yTest, {new MSE(), new Accuracy()}, new SimpleDerivative(), new SGD(0.01),
        [](size_t epoch, size_t batch, Matrix error) {
            cout << "Epoch #" << epoch + 1 << ", batch #" << batch + 1 << endl;
            cout << "Error: " << error[0] << endl << "Accuracy: " << error[1] * 100 << "%" << endl;
        }
    );
    return 0;
}