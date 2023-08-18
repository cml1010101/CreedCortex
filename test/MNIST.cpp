#include <CreedCortex.hpp>
#include <fstream>
using namespace creed;
using namespace std;
int main(int argc, const char* argv[])
{
    xt::random::seed(123);
    Sequential model = Sequential(
        {
            make_shared<Dense>(392),
            make_shared<Sigmoid>(),
            make_shared<Dense>(196),
            make_shared<Sigmoid>(),
            make_shared<Dense>(10),
            make_shared<Sigmoid>(),
        }
    );
    if (filesystem::exists("mnist.json"))
    {
        std::ifstream file("mnist.json");
        file >> model;
        file.close();
    }
    auto data = loadMNIST(1, 100, 200);
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
    {
        std::ofstream file("mnist.json");
        file << model;
        file.close();
    }
    return 0;
}