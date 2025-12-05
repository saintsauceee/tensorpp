#ifndef NEWTON_HPP
#define NEWTON_HPP

#include <functional>

double newton(
    const std::function<double(double)> &f,
    const std::function<double(double)> &df,
    double x0,
    double x_tol,
    double f_tol,
    int n_max,
    bool verbose = false

);

#endif