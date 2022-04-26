#ifndef Runga_Kutta_Solver_H
#define Runga_Kutta_Solver_H

#include "ODE_Solver.h"

class Runge_Kutta_Solver : public ODE_Solver
{
public:
    /**
     * Construct a new Runge_Kutta_Solver object
* 
     * @param _x0 initial conditions 
     * @param _y0 initial conditions 
     * @param _xn final value 
     * @param _h step size
     * @param _func ODE equation as a function 
     */
    Runge_Kutta_Solver(double _x0, std::vector<double> _y0, double _xn, double _h,
                       std::function< void (const double &, const std::vector<double> &, std::vector<double> &) > _func);

    /**
     * Destroy the Runge_Kutta_Solver object
     * 
     * Destructor of parent class is overriden here. 
     * Parent has a virtual destructor. 
     */
    ~Runge_Kutta_Solver() {}

    /**
     * Solve ODE equation with Runge-Kutta Method.
     * 
     * Runge-Kutta method is an explicit euler method with more precision.
     * Detailed information can be found in README file.
     */
    void solver_method();
};

#endif