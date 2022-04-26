#include "Runge_Kutta_Solver.h"

Runge_Kutta_Solver::Runge_Kutta_Solver(double _x0, std::vector<double> _y0, double _xn, double _h,
                                       std::function< void (const double &, const std::vector<double> &, std::vector<double> &)> _func)
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

void Runge_Kutta_Solver::solver_method()
{
    auto N_order = y0.size();

    std::vector<double> k1(N_order,0);
    std::vector<double> k2(N_order,0);
    std::vector<double> k3(N_order,0);
    std::vector<double> k4(N_order,0);
    std::vector<double> T4(N_order,0);

    for (int i = 0; i < N - 1; i++)
    {
        // save x and y values
        x_vals[i] = x0;
        y_vals[i] = y0[0];

        // 4th Order Runge-Kutta Method
        // dydx = func(x0, y0) 
        func(x0, y0, k1);
        func(x0 + 0.5 * h, y0 + (0.5 * h) * k1, k2);
        func(x0 + 0.5 * h, y0 + (0.5 * h) * k2, k3);
        func(x0 + h, y0 + h * k3, k4);

        T4 = (0.16667) * (k1) + (0.33333) * (k2) + (0.33333) * (k3) + (0.16667) * (k4);

        // Increment y by step size times T4
        // T4 can be thought as instantaneous slope,
        // with more precision than just using dy/dx
        y0 = y0 + h * T4;

        // Increment x by step size
        x0 = x0 + h;
    }

    // Save final y-value (for display purposes)
    yn = y0[0];

    // Save final x-value and y-value in solution vectors
    x_vals[N - 1] = x0;
    y_vals[N - 1] = y0[0];
}
