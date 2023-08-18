#ifndef CREEDCORE_HPP
#define CREEDCORE_HPP
#include <xtensor/xarray.hpp>
#include <xtensor/xtensor.hpp>
#include <xtensor/xrandom.hpp>
#include <xtensor/xvectorize.hpp>
#include <xtensor/xcsv.hpp>
#include <xtensor/xsort.hpp>
#include <xtensor/xadapt.hpp>
#include <xtensor/xjson.hpp>
#include <nlohmann/json.hpp>
#include <xtensor-blas/xlinalg.hpp>
namespace creed
{
    using Matrix = xt::xarray<double, xt::layout_type::dynamic>;
    template<int N>
    using Tensor = xt::xtensor<double, N>;
}
#endif