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
   - supports custom report generator: default is: console reporter
   - performance measurement for tests.
   - provided new report for TAP format (https://testanything.org/)
     - understood by Jenkins (TAP plugin exists for it).
   - generate failing test for a suite with no tests (assertion message explains)
   - a test also fails if it has not at least one assertion
 - providing hamcrest like matcher (own namespace, own folder).
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
 - object query framework like linq.
   - you can select a std::vector and use several times
     the method 'where' to provide a filter function.
   - provides "count", "min", "max" and "sum" method
   - provides possibility to transform values by registering
     as many transform functions as you like.
   - extending given "where" clause to allow use of matcher
 - object serialization (started - consider this as experimental please)
   - can dump simple objects with field of standard types and
     fields being again an object of fields to JSON format
   - minimal adjustment necessary for your custom data class.


Next Action Items (planned)
---------------------------
 - unittests:
   - providing an option --stop-on-error
   - providing new option --repeat-count for runner.
     (does repeat all suites several times).
 - extending hamcrest like matchers
   - for "contains" working with containers (element search)
   - for "contains" working with strings (string search)
 - singleton decorator class (remove singleton from factory).
 - providing generic plugin handling.
 - extending math namespace:
   - writing big integer class supporting different multiplication algorithms.
   - sieve of Eratosthenes (http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes).
   - different ways to calculate primes
   - caclulating PI (configurable precision)
   - different mulitplication algorithms
 - object query framework like linq.
   - adding 'average' and 'median'
 - object serialization
   - dump/wite for container of standard types and for container of objects.
   - read from JSON
 - providing doxygen mainpage.
 - providing wiki for some FAQ's on the project site.
 - logging
 - change log for RPM
 - extending cmake for targeting to profile code.


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


Version Policy
--------------
 - a version has the form **a.b.c**
 - "a" is the **major version** which is incremented by following reasons:
   - there's a set of **new** features with a lot of code which make it reasonable
     to increment the major version.
   - another reason would be the change of one or more interfaces which have been
     necessary to improve things. Needs to be well documented of course and
     should not happen to often.
 - "b" is the **minor version** which represents:
   - simple **new** features
   - simple **extensions** to given features
   - minor changes like adding missing documentation or style things.
 - "c" is the **bugfix counter** and is incremented on **bugfixes only**.
 - Following additional rules:
   - incrementing "b" resets "c" to zero (0.5.0, 1.0.0, 1.1.0, 1.2.0, 2.0.0, ...)
   - incrementing "a" resets "b" and "c" to zero (0.5.1, 1.0.0, 1.1.2, 2.0.0, ...)
   - each commit message (since policy has been introduced) should refer
     to a version by mentioning it in form: "a.b.c: title" in first line and
     as many details you like in following lines.
