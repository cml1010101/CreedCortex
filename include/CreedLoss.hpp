#ifndef CREEDLOSS_HPP
#define CREEDLOSS_HPP
#include <CreedCore.hpp>
namespace creed
{
    class Loss
    {
    public:
        virtual Matrix calculate(Matrix y, Matrix yHat) = 0;
    };
}
#endif