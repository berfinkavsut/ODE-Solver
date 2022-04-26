#ifndef Explicit_Euler_Solver_H
#define Explicit_Euler_Solver_H

#include "ODE_Solver.h"

class Explicit_Euler_Solver : public ODE_Solver
{
public:
    /**
     * Construct a new Explicit_Euler_Solver object
     * 
     * @param _x0 initial conditions 
     * @param _y0 initial conditions 
     * @param _xn final value 
     * @param _h step size
     * @param _func ODE equation as a function 
     */
    Explicit_Euler_Solver(double _x0, std::vector<double> _y0, double _xn, double _h,
                         std::function< void (const double &, const std::vector<double> &, std::vector<double> &)> _func);


    /**
     * Destructor of parent class is overriden here. 
     * Parent has a virtual destructor. 
     */
    ~Explicit_Euler_Solver() {}

    /**
     * Solve ODE equation with Explicit Euler Method. 
     * 
     * Detailed information can be found in README file.
     */
    void solver_method();
};

#endif