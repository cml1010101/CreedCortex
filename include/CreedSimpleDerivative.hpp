#ifndef CREEDSIMPLEDERIVATIVE_HPP
#define CREEDSIMPLEDERIVATIVE_HPP
#include <CreedLoss.hpp>
namespace creed
{
    class SimpleDerivative : public Loss
    {
    public:
        SimpleDerivative() = default;
        virtual Matrix calculate(Matrix y, Matrix yHat) override;
    };
}
#endif