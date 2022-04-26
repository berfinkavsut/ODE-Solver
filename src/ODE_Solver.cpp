#include "ODE_Solver.h"

void ODE_Solver::print_output()
{
    // Print x-values and y-values as a long list as a terminal output
    std::cout << '\t' << "X" << '\t' << "Y" << std::endl;
    int length = x_vals.size();

    for (int i = 0; i < length; i++)
    {
        std::cout << '\t' << x_vals[i] << '\t' << y_vals[i] << std::endl;
    }

    // Print final value
    std::cout << "Result: " << yn << std::endl; 
}

double ODE_Solver::get_yn()
{
    // return final value
    return yn;
}

std::vector<double> operator+(const std::vector<double> &v1, const std::vector<double> &v2)
{
    int n = v1.size();
    std::vector<double> result(n, 0);

    for (int i = 0; i < n; i++)
    {
        result[i] = v1[i] + v2[i];
    }

    return result;
}

std::vector<double> operator*(const double &num, const std::vector<double> &v1)
{
    int n = v1.size();

    std::vector<double> result(n, 0);
    for (int i = 0; i < n; i++)
    {
        result[i] = v1[i] * num;
    }

    return result;
}
