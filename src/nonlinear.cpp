#include <functional>
#include <cmath>
#include <iostream>

double newton(
    const std::function<double(double)> &f,
    const std::function<double(double)> &df,
    double x0,
    double x_tol,
    double f_tol,
    int n_max,
    bool verbose = false)
{
    double x = x0;

    for (int n = 1; n <= n_max; n++)
    {
        double fx = f(x);
        double dfx = df(x);

        if (dfx == 0.0)
        {
            break; // avoid division by 0
        }

        double d = fx / dfx;
        x = x - d;

        if (verbose)
        {
            std::cout << "iter " << n
                      << "  x = " << x
                      << "  f(x) = " << f(x)
                      << "  step = " << d << '\n';
        }

        if (std::abs(d) <= x_tol or std::abs(fx) <= f_tol)
        {
            return x;
        }
    }

    return x;
}

double secant(
    const std::function<double(double)> &f,
    double x0,
    double x1,
    double x_tol,
    double f_tol,
    int n_max,
    bool verbose = false)
{
    double f0 = f(x0);
    double f1 = f(x1);

    for (int n = 1; n <= n_max; n++)
    {
        if (f1 - f0 == 0.0)
        {
            break; // avoid division by 0
        }

        double d = (x1 - x0) * f1 / (f1 - f0);

        x0 = x1;
        f0 = f1;
        x1 = x1 - d;
        f1 = f(x1);

        if (verbose)
        {
            std::cout << "iter " << n
                      << "  x = " << x1
                      << "  f(x) = " << f1
                      << "  step = " << d << '\n';
        }

        if (std::abs(d) <= x_tol or std::abs(f1) <= f_tol)
        {
            return x1;
        }
    }

    return x1;
}

int main()
{
    auto f = [](double x)
    { return x * x - 2.0; };

    auto df = [](double x)
    { return 2.0 * x; };

    double root = newton(f, df, 1.0, 1e-10, 1e-10, 100);
    std::cout << "root = " << root << "\n";
}