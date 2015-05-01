README
======

Welcome
-------
Welcome to the README of my personal C++11/cmake refererence project.
It's a kind of knowledge database and small test environment.
The purpose is - of course - to keep everything clean, simple and
well documented.


Current Content
---------------
 - implementation of an easy to use unittesting framework.
  - providing suite and tests with easy to write lambda functions.
  - providing hamcrest like matcher.
  - supports custom report generator: default is: console reporter
  - performance measurement for tests.
 - command line options
  - --shuffle-suites=true  (execution of suites in random order)
  - --shuffle-tests=true   (execution of tests in random order)
  - --filter=string        (does filter for suites)
 - pattern classes like a factory.
 - math classes like a 2d vector or a 2d line.
 - algorithm functions like 'sorted' and 'shuffled'.
 - you can create HTML documentation with doxygen.
 - supports code coverage report
 - supports cppcheck


Next Action Items (planned)
---------------------------
 - providing new report for TAP format (https://testanything.org/)
   - understood by Jenkins (plugin exists).
 - providing new option --repeat-count for runner.
   (does repeat all suites several times).
 - singleton decorator class (remove singleton from factory).
 - writing big integer class supporting different multiplication algorithms.
 - sieve of Eratosthenes (http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes).
 - power of 2 algorithm.
 - fibonacci algorithms (http://en.wikipedia.org/wiki/Fibonacci_number).
 - providing generic plugin handling.
 - object query like linq.
 - object serialization.
 - providing doxygen mainpage.
 - providing wiki for some FAQ's on the project site.


CMake
-----
Here's the minimum way to go:
```
  mkdir build
  cd build
  cmake ..
  make
```

A list of further useful options:
```
 cmake -G "CodeBlocks - Unix Makefiles" ..
 cmake -DCMAKE_BUILD_TYPE=Debug ..
 cmake -DBUILD_DOCUMENTATION=ON ..
```

You also can do:
```
 make check       (do not use make test since it does NOT build)
 make run         (does run the test without "ctest")
 make memcheck    (wraps use of the valgrind tool)
 make doc         (generates doxygen documentation)
 make coverage    (runs the tests and generates HTML coverage report)
 make cppcheck    (runs cppcheck agains the sources)
```

For creating a RPM package (sudo is important):
```
 sudo make package
```

Code Coverage
-------------
```
make coverage
```

I'm using this: http://ltp.sourceforge.net/coverage/lcov.php
When you run this then following dependencies are ensured:

 - compilation and linkage of the test binary
 - running the test
 - capturing the coverage data
 - generating the report

What remains ... at least what I do:

```
firefox coverage/index.html
```

You can keep that page open and when you run again the coverage
after you have added or modified tests then simply refresh the page.
