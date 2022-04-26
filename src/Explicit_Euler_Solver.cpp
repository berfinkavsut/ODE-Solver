#include "Explicit_Euler_Solver.h"

Explicit_Euler_Solver::Explicit_Euler_Solver(double _x0, std::vector<double> _y0, double _xn, double _h,
                                             std::function< void (const double &, const std::vector<double> &, std::vector<double> &)>_func)

{
    // Set parameters by inputs
    x0 = _x0;
    y0 = _y0;
    xn = _xn;
    yn = 0;
    h = _h;
    func = _func;

    // Calculate the number of (x,y) values
    // according to first value, final value, and step size
    N = static_cast<int>((xn - x0) / h) + 1;

    // Allocate x-values and y-values, to be calculated later
    x_vals = std::vector<double>(N, 0);
    y_vals = std::vector<double>(N, 0);
}

void Explicit_Euler_Solver::solver_method()
{
    auto N_order = y0.size();
    std::vector<double> dydx(N_order,0);

    for (int i = 0; i < N - 1; i++)
    {
        // Save x-values and y-values
        x_vals[i] = x0;
        y_vals[i] = y0[0];

        // Euler Method
        // Increment y by step size times dy/dx
        // dy/dx can be thought as instantaneous slope
        // dydx = func(x0, y0)
        func(x0, y0, dydx);
        y0 = y0 + h * dydx; 
        // Increment x by step size
        x0 = x0 + h;
    }

    // Save final y-value (for display purposes)u
    yn = y0[0];

    // Save final x-value and y-value in solution vectors
    x_vals[N - 1] = x0;
    y_vals[N - 1] = y0[0];
}