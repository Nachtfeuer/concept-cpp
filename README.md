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
   - provided new report for TAP format (https://testanything.org/)
     - understood by Jenkins (TAP plugin exists for it).
 - command line options
   - --shuffle-suites=true  (execution of suites in random order)
   - --shuffle-tests=true   (execution of tests in random order)
   - --filter=string        (does filter for suites)
   - --format=name          ("default" or "tap")
 - pattern classes like a factory.
 - math classes
   - 2d point, 2d vector, 2d line, ...
   - fibonacci algorithm (http://en.wikipedia.org/wiki/Fibonacci_number).
   - power of 2 algorithm.
 - document class
   - started with text document using regex for queries like word count.
     (using boost::regex)
 - algorithm functions like 'sorted' and 'shuffled'.
 - you can create HTML documentation with doxygen.
 - supports code coverage report (HTML as well as Cobertura compatible XML)
 - supports cppcheck
 - object serialization (started)
   - can dump simple objects with field of standard types and
     fields being again an object of fields to JSON format
   - minimal adjustment necessary for your custom data class.
 - object query framework like linq.
   - you can select a std::vector and use several times
     the method 'where' to provide a filter function.
   - count method


Next Action Items (planned)
---------------------------
 - unittests:
   - warn about:
     - suites with no test
     - tests with no assertion
   - providing an option --stop-on-error
   - providing new option --repeat-count for runner.
     (does repeat all suites several times).
 - singleton decorator class (remove singleton from factory).
 - writing big integer class supporting different multiplication algorithms.
 - sieve of Eratosthenes (http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes).
 - providing generic plugin handling.
 - object query framework like linq.
   - adding 'sum', 'min', 'max' and 'average'
 - object serialization
   - dump/wite for container of standard types and for container of objects.
   - read from JSON
 - providing doxygen mainpage.
 - providing wiki for some FAQ's on the project site.
 - logging


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
