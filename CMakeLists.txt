cmake_minimum_required(VERSION 3.0.0)
project(ode-solver
    VERSION 1.0
    DESCRIPTION "ODE Solver Project"
    LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)  

add_executable(ode-solver
    src/ODE_Solver.h
    src/ODE_Solver.cpp
    src/Explicit_Euler_Solver.h
    src/Explicit_Euler_Solver.cpp
    src/Runge_Kutta_Solver.h
    src/Runge_Kutta_Solver.cpp
    src/unit_tests.h
    src/unit_tests.cpp   
    src/main.cpp)

target_compile_features(ode-solver PUBLIC cxx_std_17)

set (CMAKE_CXX_FLAGS "-pg -g -O3")
