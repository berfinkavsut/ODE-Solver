#include "unit_tests.h"

bool unit_tests::check(ODE_Solver *ptr, double yn_real)
{
    // Accuracy tolerance
    double tol_acc = 0.1;

    // Solve the ODE with güven ODE solver
    ptr->solver_method();

    // Get the estime of solver
    yn = ptr->get_yn();
    std::cout << "Approximated value: " << yn << std::endl;

    // Check if result is inside error bound
    if (abs(yn_real - yn) < tol_acc)
    {
        return true;
    }
    return false;
}

void unit_tests::test_case(int test_case, double step_size)
{
    // set step size 
    h = step_size;

    // TEST CASE 1
    if (test_case == 1)
    {
        // Parameters for test #1
        x0 = 0;
        y0 = {3, 0};
        xn = 1;
        yn_real = -43.725;

        // ODE for test #1
        unit_test = [](const double &x, const std::vector<double> &y, std::vector<double> &dydx)
        {    
            int n = y.size();
            // std::vector<double> dydx;
            for (int i = 0; i < (n - 1); i++)
            {
                dydx[i] = (y[i + 1]);
            }
            dydx[n-1] = (-4 * y[0] + 5 * y[1]);

            // return dydx;
        };
    }

    // TEST CASE 2
    else if (test_case == 2)
    {
        // Parameters for test #2
        x0 = 0;
        y0 = {0.5};
        xn = 1;
        yn_real = 0.6409;

        // ODE for test #2
        unit_test = [](const double &x, const std::vector<double> &y, std::vector<double> &dydx)
        {
            // std::vector<double> dydx;
            dydx[0] = (y[0] - x);
            // return dydx;
        };
    }

    std::cout << "\n--------------- TEST CASE #" << test_case << "-------------------\n\n";
    std::cout << "Expected value:" << yn_real << std::endl << std::endl;

    //*********************************************EXPLICIT METHOD*********************************************************
    ODE_Solver *exp_ptr;
    Explicit_Euler_Solver exp_euler_solver(x0, y0, xn, h, unit_test);
    exp_ptr = &exp_euler_solver;

    // start = std::chrono::system_clock::now();  // start-time
    check_unit_test = check(exp_ptr, yn_real); // solver method inside check function
    // end = std::chrono::system_clock::now();    // end-time

    if (check_unit_test == true)
    {
        std::cout << "Explicit Euler Method: passed."
                  << std::endl;
    }
    else
    {
        std::cout << "Explicit Euler Method: failed."
                  << std::endl;
    }

    //*********************************************RUNGE-KUTTA METHOD******************************************************
    Runge_Kutta_Solver runge_kutta_solver(x0, y0, xn, h, unit_test);
    exp_ptr = &runge_kutta_solver;

    // start = std::chrono::system_clock::now();  // start-time
    check_unit_test = check(exp_ptr, yn_real); // solver method inside check function
    //end = std::chrono::system_clock::now();    // end-time

    if (check_unit_test == true)
    {
        std::cout << "Runge-Kutta Method: passed."
                  << std::endl;
    }
    else
    {
        std::cout << "Runge-Kutta Method: failed."
                  << std::endl;
    }
}

