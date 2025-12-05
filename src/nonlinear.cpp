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

int main()
{
    auto f = [](double x)
    { return x * x - 2.0; };

    auto df = [](double x)
    { return 2.0 * x; };

    double root = newton(f, df, 1.0, 1e-10, 1e-10, 100);
    std::cout << "root = " << root << "\n";
}