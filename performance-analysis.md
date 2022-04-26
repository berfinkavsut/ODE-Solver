# Performance Analysis

+ For code performance analysis **gprof** was used.
+ The code was compiled with `-pg` flags to run gprof.
+ Performance results were obtained by `gprof ode-solver gmon.out > results.txt`.
+ Performance results can be found in performance folders  [performance](performance) 

### **Implementation of performance enhancement techniques** 

+ Multiple changes were implemented to the code in order to enhance the performance of code. Some were useful, others not, and some were difficult to implement. Changes were as follows:

    1. Initializing differential equation vector with constant size instead of extending it inside for loop - improved performance.
    2. Passing differential equation vector by reference to the differential function - improved performance.
    3. Dereferencing the data and sending it as const to the function - improved performance.
    4. Replacing loop with STL functions for overloaded operator functions - deteriorated the performance.
    5. Replacing all vectors with arrays - This would have improved performance but replacing the would have required to restructure the whole code from the base.
	
	
__________________________

### **Results before and after implementing steps individually** 
	
#### Results for original code

-------------------------------------------------------------------------------------------

~~~bash 

index % time    self  children    called     name
                                                 <spontaneous>
[1]     99.9    0.00    7.59                 main [1]
                0.00    7.59       2/2           unit_tests::test_case(int, double) [2]
                0.00    0.00       1/1           unit_tests::~unit_tests() [141]
                0.00    0.00       1/1           unit_tests::unit_tests() [154]
                0.00    0.00       1/1           bool std::operator==<char, std::char_traits<char>, std::allocator<char> >(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, char const*) [210]
-----------------------------------------------
                0.00    7.59       2/2           main [1]
[2]     99.9    0.00    7.59       2         unit_tests::test_case(int, double) [2]
                0.00    7.57       4/4           unit_tests::check(ODE_Solver*, double) [3]
                0.00    0.01       2/2           std::vector<double, std::allocator<double>

~~~                 

#### Results after implementing step 1

~~~bash 

-------------------------------------------------------------------------------------------

index % time    self  children    called     name
                                                 <spontaneous>
[1]     99.4    0.00    6.77                 main [1]
                0.00    6.77       2/2           unit_tests::test_case(int, double) [2]
                0.00    0.00       1/1           unit_tests::~unit_tests() [117]
                0.00    0.00       1/1           unit_tests::unit_tests() [130]
                0.00    0.00       1/1           bool std::operator==<char, std::char_traits<char>, std::allocator<char> >(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, char const*) [185]
-----------------------------------------------
                0.00    6.77       2/2           main [1]
[2]     99.4    0.00    6.77       2         unit_tests::test_case(int, double) [2]
                0.00    6.76       4/4           unit_tests::check(ODE_Solver*, double) [3]
                0.00    0.01       2/2           std::vector<double, std::allocator<double>

~~~ 

#### Results after implementing step 2

~~~bash 

-------------------------------------------------------------------------------------------

index % time    self  children    called     name
                                                 <spontaneous>
[1]     99.4    0.00    5.40                 main [1]
                0.00    5.40       2/2           unit_tests::test_case(int, double) [2]
                0.00    0.00       1/1           unit_tests::~unit_tests() [114]
                0.00    0.00       1/1           unit_tests::unit_tests() [128]
                0.00    0.00       1/1           bool std::operator==<char, std::char_traits<char>, std::allocator<char> >(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, char const*) [187]
-----------------------------------------------
                0.00    5.40       2/2           main [1]
[2]     99.4    0.00    5.40       2         unit_tests::test_case(int, double) [2]
                0.00    5.37       4/4           unit_tests::check(ODE_Solver*, double) [3]
                0.00    0.01       2/2           std::vector<double, std::allocator<double>

~~~                 

#### Results after implementing step 3

~~~bash 

-------------------------------------------------------------------------------------------

index % time    self  children    called     name
                                                 <spontaneous>
[1]     99.3    0.00    4.28                 main [1]
                0.00    4.28       2/2           unit_tests::test_case(int, double) [2]
                0.00    0.00       1/1           unit_tests::~unit_tests() [96]
                0.00    0.00       1/1           unit_tests::unit_tests() [120]
                0.00    0.00       1/1           bool std::operator==<char, std::char_traits<char>, std::allocator<char> >(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, char const*) [183]
-----------------------------------------------
                0.00    4.28       2/2           main [1]
[2]     99.3    0.00    4.28       2         unit_tests::test_case(int, double) [2]
                0.00    4.27       4/4           unit_tests::check(ODE_Solver*, double) [3]
                0.00    0.00       2/2

~~~          

### **Analysis**
          
1. Firstly, the differential equation vector (std::vector dydx) was not initialized with constant size. It was being extended by each iteration in for loop, which is inefficient in terms of memory allocation operation. Total computation time dropped from 7.59s to 6.77s. 

2. The differential functions are used inside ODE solvers. Here, we were passing the inputs by value, and returning the next condition vector. The functions are using copy-constructor when values are passed by value. This was an unnecessary operation. Instead, we modified dydx (i.e. differential equation vector) by giving references as inputs. This decreased run time from 6.77s to 5.40s.

3. After seeing the impact of pass-by-reference, we decided to give all inputs of differential functions with references. Then, the computation time decreased further from 5.40s to 4.28s. 

+  In total, the computation time dropped from 7.59s to 4.28s, which means it dropped by 43.6%. 
+  After using compiler flag `-O3`, final computation time dropped by **96%** in total. 

4. STL algorithms in `operator+` and `operator*` were expected to increase performance, however it actually deteriorated it. We think it might be resulted from having small-sized vectors in our operations. In large-sized vectors, the operators would consume less time with STL algorithms. The compiler optimization seems to be enough in our project. 

5. We know that arrays and std::array are better than pointer arrays and std::vector for small-sized vectors. Therefore, we tried to change data structure for all std::vectors wit small size. However, this solution could not be implemented since it required changing the whole structure of code. 



 
