//unit_tests.h
#ifndef unit_tests_H
#define unit_tests_H

#include <iostream>
#include <vector>
#include <fstream>

#include "ODE_Solver.h"
#include "Explicit_Euler_Solver.h"
#include "Runge_Kutta_Solver.h"

class unit_tests
{
private:
    // members of ODE solvers
    bool check_unit_test; // flag for unit test results

    double h; // Step size
    double x0;        // Initial condition
    double xn;        // Last result
    double yn;        // Last result
    double yn_real;   // Real result

    std::vector<double> y0; // Initial conditions

    std::function<void (const double & , const std::vector<double> &, std::vector<double> & )> unit_test; // ODE  given as a lambda function

public:

    /**
     * Solve ODE by given ODE solver method.
     * Compare with real result with respect to accuracy tolerance. 
     * Return whether the solver method could pass the test case or not. 
     * 
     * @param ptr pointer for ODE_Solver object (for run-time polymorphism)
     * @param yn_real real result to check the estimate of ODE solver method 
     * @return true, if the estimate of solver method is inside error bound.
     * @return false, otherwise. 
     */
    bool check(ODE_Solver *ptr, double yn_real);

    /**
     * Test ODE Solver with given test case #. 
     * 
     * Here, 3 test cases are provided.
     * Expected and approximated values are printed. 
     * Computation times of solver methods are displayed if desired. 
     * 
     * @param test_case # of test case
     * @param show_time flag for showing computation time of solver methods
     */
    void test_case(int test_case, double step_size = 1e-6);

  
    
};

#endif