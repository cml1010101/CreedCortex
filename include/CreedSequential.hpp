#ifndef CREEDSEQUENTIAL_HPP
#define CREEDSEQUENTIAL_HPP
#include <CreedLayer.hpp>
#include <CreedLoss.hpp>
#include <CreedMetric.hpp>
#include <CreedOptimizer.hpp>
namespace creed
{
    class Sequential : public Layer
    {
    private:
        std::vector<std::shared_ptr<Layer>> layers;
    public:
        Sequential() = default;
        Sequential(std::vector<std::shared_ptr<Layer>> layers);
        virtual Matrix forward(Matrix x) override;
        virtual Matrix backward(Matrix yGrad) override;
        virtual Matrix train(Matrix x, Matrix yHat, std::vector<Metric*> metrics, Loss* loss);
        virtual Matrix test(Matrix x, Matrix yHat, std::vector<Metric*> metrics);
        virtual Matrix trainBatch(Matrix x, Matrix yHat, std::vector<Metric*> metrics, Loss* loss);
        virtual Matrix testBatch(Matrix x, Matrix yHat, std::vector<Metric*> metrics);
        virtual void updateParameters(Optimizer* optimizer);
        virtual void fit(size_t epochs, Matrix xTrain, Matrix yTrain, Matrix xTest, Matrix yTest, std::vector<Metric*> metrics,
            Loss* loss, Optimizer* optimizer, std::function<void(size_t, size_t, Matrix)> testBatchCallback);
        virtual Sequential& operator<<(std::shared_ptr<Layer> layer);
    };
}
#endif