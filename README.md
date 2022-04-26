# ODE Solver 

## Euler Method 

Euler method is a numerical method to solve ordinary differential equations (ODEs). Euler method is a first-order ODE solver method. Since any higher-order ODE can be transformed to a first-order ODE problem, it can be used with higher-order ODEs, as well. The transformation step from first-order to higher-orders by vectorization is explained in [Euler Method](https://en.wikipedia.org/wiki/Euler_method). 

## Explicit Euler Method 

In **Sprint 1**, we implemented Explicit Euler method. First-order explicit Euler method is as follows: 

$`y\prime(x) = f(x,y)`$ and $`y(x_0) = y_0`$

The $`f(x,y)`$ function is defined from the differential equation by seperating $`y\prime(x)`$, i.e. highest-order term, on the left side and rest stays on the right side.  

In each iteration step, x values are increased by step size of h. 

$`x_{n+1} = x_n + h`$ 

y values are increased at each step by adding the differential increase to the previous y value. 

$`y_{n+1} = y_n + hf(x_n, y_n)`$ 

Every ODE needs initial condition to be solved. For $`N^{th}`$-order ODE, we need the initial condition values from $`y(x_0)`$ until  $`y^{N-1}(x_0)`$. In higher-order case, y becomes a vector. 

$`y = (y(x), y^{\prime}(x), ... , y^{N-1}(x) )`$  

## Runge-Kutta Method

In **Sprint 2**, we have implemented additionally Runge-Kutta Method. 

In each iteration step, x values are increased by step size of h as before. 

$`x_{n+1} = x_n + h`$ 

y values are increased as follows: 

$`y_{n+1} = y_n + (1/6)hf(x_n, y_n)`$ 

$`k_1 = f(x_n, y_n)`$ 
$`k_2 = f(x_n + h/2, y_n + hk_1/2)`$ 
$`k_3 = f(x_n + h/2, y_n + hk_2/2)`$ 
$`k_4 = f(x_n + h, y_n + hk_3)`$ 

Runge-Kutta Method can also solve higher-order ODEs with the same way as explained in Explicit Euler Method.  

## How to Build and Run Project?

**_Example Problem 1_**

In the first example, our ODE is $`y^{\prime}(x) = y(x) - x`$. The term with the highest-order is on left side of the equation, so that we can define $`y^{\prime}(x) = f(x,y)`$ as in first-order ODE case. When the user is inserting their differential equation in the code, they should follow this fashion. 

Inside main.cpp file, the user should enter the differential equation inside the lambda function diff_func() in main() function. The user only needs to modify this line: 

```
dydx.push_back(y[0] - x);   

```

**_Example Problem 2_**

In the second example, our ODE is $`y^{\prime\prime}(x) = 4y(x) - 5y^{\prime}(x)`$. Similarly, the user should enter the differential equation inside diff_func(). The modified line should be as follows: 

```
dydx.push_back(-4 * y[0] + 5* y[1]);   

```
After modifying the differential equation, the project is ready to build and run. 

To build ode-solver project, change directory to build folder. Run the following lines in terminal. 

```
rm -r *
cmake ..
make -f Makefile 
./ode-solver 
```
## How to Navigate through Menu?

After running the project, you will be introduced to a menu with 2 options:
```
Please select on of the following options: 
(1) for unit tests
(2) for solving custom problem
```
1) **Run the unit tests:** Simply runs the 2 unit tests and shows that ODE solvers are working fine. Unit tests are explained in detail in example problems. 
2) **Solve your custom problem:** For this you will have to _edit_ the main.cpp. First you should _add_ your custom differential equation and _input_ initial conditons from the _terminal_.

To make it further clear, look at the following examples.

**_Example Problem 1_**

The initial condition values for our problem are $`x_{0} = 0, x_{n} = 1, h = 0.001, y(x_0) = 0.5`$. 

To add the initial conditons, you will run ode-solver and enter values as shown below:

```
Please select on of the following options: 
(1) for unit tests
(2) for solving custom problem
Input number: 2

Solving custom problem

Highest Order of ODE: 
1
Insert initial condition x0: 
0
For inital condition y0, enter initial values in ascending order until (N-1)th order!
Insert initial condition y0:
0.5
Insert the x-value to approximate y(x): 
1
Insert the step size for ODE solver: 
0.001
State the type of solver to be used 
[1] Explicit Euler Method 
[2] Runge-Kutta Method 

```
You can choose the ODE solver method here. 

The expected result is 0.6409.

**_Example Problem 2_**

The initial condition values for our problem are 
$`x_{0} = 0, x_{n} = 1, h = 0.001, y(x_0) = 3, y^{\prime}(x_0) = 0. `$

To add the initial conditions, you will run ode-solver and enter values as shown below:
```
Please select on of the following options: 
(1) for unit tests
(2) for solving custom problem
Input number: 2

Solving custom problem

Highest Order of ODE: 
1
Insert initial condition x0: 
0
For inital condition y0, enter initial values in ascending order until (N-1)th order!
Insert initial condition y0:
3
0
Insert the x-value to approximate y(x): 
1
Insert the step size for ODE solver: 
0.001
State the type of solver to be used 
[1] Explicit Euler Method 
[2] Runge-Kutta Method 

```

The expected result is -43.725.








