#include <iostream>
#include <vector>
#include <functional>

#include "Explicit_Euler_Solver.h"
#include "Runge_Kutta_Solver.h"
#include "unit_tests.h"

int main()
{

    std::string input; // input for main menu

    std::cout << "Please select on of the following options: " << std::endl;
    std::cout << "(1) for unit tests" << std::endl;
    std::cout << "(2) for solving custom problem" << std::endl;
    std::cout << "Input number: ";
    std::cin >> input;

    while (1)
    {

        if (input == "1")
        {
            // run unit tests
            unit_tests test_;
            bool show_time = true;
            test_.test_case(1);
            test_.test_case(2);
            break;
        }

        else if (input == "2")
        {
            // solve custom problem
            std::cout << "Solving custom problem" << std::endl
                      << std::endl;

            int type; // type of solver method
            int N;    // highest order of ODE

            double x0;      // initial value, input through cin
            double h;       // step size, input through cin
            double xn;      // x-value to evaluate y(x_n)
            double temp_y0; // temp y0 to get initial conditions vector y0

            std::vector<double> y0; // initial conditions, input through cin

            //*******************************************************************
            // Please insert your ODE equation as explained in README.md file!
            // dy/dx is equivalent to f(x,y).
            //*******************************************************************
            auto diff_func = [](const double &x, const std::vector<double> &y, std::vector<double> &dydx)

            {
                int n = y.size();

                // prepare dy/dx as a vector
                // here, we are transforming higher-order ODEs
                // to multiple first-order ODEs
                // std::vector<double> dydx;
                for (int i = 0; i < (n - 1); i++)
                {
                    dydx[i] = (y[i + 1]);
                }

                // ODE equation is inserted here!
                // dydx[n-1] = (y[0] - x); // first example
                dydx[n-1] = (-4 * y[0] + 5 * y[1]); // second example
                // dydx[n - 1] = 5 * y[0] - 3; // third example

                // return dydx;
            };


            // Highest Order of ODE
            std::cout << "Highest Order of ODE: " << std::endl;
            std::cin >> N;

            while (std::cin.fail() || N <= 0)
            {
                std::cout << "Wrong input!" << std::endl;
                std::cin.clear();
                std::cin.ignore(256, '\n');

                std::cout << "Insert the inputs again:" << std::endl;
                std::cin >> N;
            }

            // Initial condition x0
            std::cout << "Insert initial condition x0: " << std::endl;
            std::cin >> x0;
            while (std::cin.fail())
            {
                std::cout << "Wrong input!" << std::endl;
                std::cin.clear();
                std::cin.ignore(256, '\n');

                std::cout << "Insert the inputs again:" << std::endl;
                std::cin >> x0;
            }

            // Initial condition y0
            std::cout << "For inital condition y0, enter initial values in ascending order until (N-1)th order!" << std::endl;
            std::cout << "Insert initial condition y0:" << std::endl;
            for (int i = 0; i < N; i++)
            {
                std::cin >> temp_y0;
                while (std::cin.fail())
                {
                    std::cout << "Wrong input!" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(256, '\n');

                    std::cout << "Insert the inputs again:" << std::endl;
                    std::cin >> temp_y0;
                }
                y0.push_back(temp_y0);
            }

            // Final value xn 
            std::cout << "Insert the x-value to approximate y(x): " << std::endl;
            std::cin >> xn;
            while (std::cin.fail())
            {
                std::cout << "Wrong input!" << std::endl;
                std::cin.clear();
                std::cin.ignore(256, '\n');

                std::cout << "Insert the inputs again:" << std::endl;
                std::cin >> xn;
            }

            // Step size 
            std::cout << "Insert the step size for ODE solver: " << std::endl;
            std::cin >> h;
            while (std::cin.fail() || h <= 0)
            {
                std::cout << "Wrong input!" << std::endl;
                std::cin.clear();
                std::cin.ignore(256, '\n');

                std::cout << "Insert the inputs again:" << std::endl;
                std::cin >> h;
            }
            
            // If xn < x0, take negative of step size for iterative solvers. 
            if (xn < x0)
            {
                h = -1 * h;
            }

            ODE_Solver *solver_ptr;
            std::cout << "State the type of solver to be used " << std::endl;
            std::cout << "[1] Explicit Euler Method " << std::endl;
            std::cout << "[2] Runge-Kutta Method " << std::endl;
            std::cin >> type;

            // Run-time polymorphism
            if (type == 1)
            {
                Explicit_Euler_Solver exp_euler_solver(x0, y0, xn, h, diff_func); // stored in stack
                solver_ptr = &exp_euler_solver;                                   // set solver to EXplicit Euler Method
                solver_ptr->solver_method();                                      // virtual function, binded at runtime
                solver_ptr->print_output();
            }
            else if (type == 2)
            {
                Runge_Kutta_Solver runga_kutta_solver(x0, y0, xn, h, diff_func); // stored in stack
                solver_ptr = &runga_kutta_solver;                                // set solver to Runge-Kutta Merhod
                solver_ptr->solver_method();                                     // virtual function, binded at runtime
                solver_ptr->print_output();
            }

            break;
        }
        else
        {
            std::cout << "Wrong input! Enter valid number:";
            std::cin >> input;
        }
    }

    return 0;
}
