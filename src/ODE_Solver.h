//ODE_Solver.h
#ifndef ODE_Solver_H
#define ODE_Solver_H

#include <iostream>
#include <vector>
#include <functional>

class ODE_Solver
{
protected:     // child classes can access protected members
    double h;  // Step size
    double x0; // Initial condition
    double xn; // Last result
    double yn; // Last result

    int N; // # of elements in x-axis

    std::vector<double> y0;     // Initial conditions
    std::vector<double> x_vals; // ODE solver x-values
    std::vector<double> y_vals; // ODE solver estimates

    std::function< void (const double &, const std::vector<double> &, std::vector<double> &) > func; // ODE equation as a function input

public:
    /**
     * Get the yn object
     * 
     * @return double 
     */
    double get_yn();

    /**
     * Print output a list in terminal.
     * 
     */
    void print_output();

    /**
     * Destroy the ode solver object
     * 
     * Destructor is a virtual function, 
     * since we are using run-time polymorphism.
     * Each solver is implementing their own destructor.
     */
    virtual ~ODE_Solver() {}

    /**
     * Solve the ODE equation.  
     * 
     * This functions solves ODE equations with given initial conditions and final value. 
     * The x-values and y-values, i.e. estimates, are saved in the object. 
     * Solver method is a virtual function,
     * since each solver is overriding. 
     */
    virtual void solver_method() = 0;
};

/**
 * Sum two vectors. 
 * 
 * This function is used later in solver_method of each ODE solver. 
 * It is for solving higher-order equations as formulated multiple first-order equations.  
 * 
 * @param v1 vector #1
 * @param v2 vector #2 
 * @return std::vector<double> 
 */
std::vector<double> operator+(const std::vector<double> &v1, const std::vector<double> &v2);

/**
 * Multiply vector with a scalar.
* 
 * @param num scalar 
 * @param v1 vector
 * @return std::vector<double> 
 */
std::vector<double> operator*(const double &num, const std::vector<double> &v1);

#endif