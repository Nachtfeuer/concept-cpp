README
======

[![Build Status](https://travis-ci.org/Nachtfeuer/concept-cpp.svg?branch=master)](https://travis-ci.org/Nachtfeuer/concept-cpp)

### Table Of Contents
[**Welcome**](#welcome)  
[**Quick start**](#quick-start)  
[**Current Content**](#current-content)  
[**Next Action Items (planned)**](#next-action-items-planned)  
[**CMake**](#cmake)  
[**Code Coverage**](#code-coverage)  
[**Level Of Done**](#level-of-done)  
[**Version Policy**](#version-policy)  

Welcome
-------
Welcome to the README of my personal C++11/cmake reference project.
It's a kind of knowledge database and small test environment.
The purpose is - of course - to keep everything clean, simple and
well documented. Please keep in mind and read:

 - [**Level Of Done**](#level-of-done)
 - [**Version Policy**](#version-policy)  


Quick start
-----------
```
 git clone https://github.com/Nachtfeuer/concept-cpp.git
 cd concept-cpp
 mkdir build
 cd build
 cmake ..
 make run
```

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
   - is_not, is_equal, is_range, has_item, ...
 - command line options
   - --shuffle-suites=true  (execution of suites in random order)
   - --shuffle-tests=true   (execution of tests in random order)
   - --filter=string        (does filter for suites)
   - --format=name          ("default" or "tap")
 - pattern classes like a factory and singleton decorator.
 - types (special type traits)
   - is_container
 - math classes
   - 2d point, 2d vector, 2d line, ...
   - fibonacci algorithm (http://en.wikipedia.org/wiki/Fibonacci_number).
   - power of 2 algorithm.
   - fraction
   - factorization (probe)
   - prime function/classes
     - is_prime and sieve_of_eratosthenes
   - number functions
     - triangle, is_triangle, pentagonal, is_pentagonal, hexagonal, is_hexagonal
     - is_square, is_abundant, is_perfect, is_pandigital
   - digit functions
     - count, sum, is_pandigital
 - document class
   - started with text document using regex for queries like word count.
     (using boost::regex)
 - algorithm functions like 'sorted' and 'shuffled'.
 - you can create HTML documentation with doxygen.
   - also generates formulars in the doc for math (without Latex)
   - doxygen mainpage provided.
 - supports code coverage report (HTML as well as Cobertura compatible XML)
 - supports cppcheck
 - object query framework like linq.
   - you can select a std::vector, std::list or std::set and use several times
     the method 'where' to provide a filter function.
   - provides "count", "min", "max", "sum", "average" and "median" method
   - provides possibility to transform values by registering
     as many transform functions as you like.
   - extending given "where" clause to allow use of matcher
 - generator framework (range based) working same way
   as the object query framework
 - object serialization (started - consider this as **experimental** please)
   - can dump simple objects with field of standard types and
     fields being again an object of fields to JSON format
   - minimal adjustment necessary for your custom data class.

Next Action Items (planned)
---------------------------
 - unittests:
   - providing new option --stop-on-error
   - providing new option --repeat-count for runner.
     (does repeat all suites several times).
   - output: number of test (filter/all)
   - output: duration of all tests
 - extending hamcrest like matchers
   - for "contains" working with strings (string search)
 - extending math namespace:
   - writing big integer class supporting different multiplication algorithms.
   - different ways to calculate primes
   - calculating PI (configurable precision)
   - different mulitplication algorithms
   - fractions: reduce to lowest term by using gcd
 - object serialization
   - dump/wite for container of standard types and for container of objects.
   - read from JSON
 - logging
 - providing wiki for some FAQ's on the project site.
 - extending cmake for targeting to profile code.
 - providing generic plugin handling.


CMake
-----
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


Level Of Done
-------------
It's mainly about quality and about the tasks you have to consider on each implemenation
indepedent whether it's a new feature or a bug fix. Here's a list of things you <b>ALWAYS</b>
should do - at least for this project (also you should do it for all):

 - <b>clean code</b>
   - don't leave commented code (remove it)
   - ensure consistent style and don't do unfavorable things like long methods, high nested depths,
     too many parameters for a function or method or mixing spaces and tabs (don't use tabs).
 - <b>clean design</b>
   - ensure re-usable code (DRY)
   - KISS (keep it simple software)
 - <b>proper source code documentation</b>
   - use C++ comment style /// (not C style)
   - provide example(s) on how to use things where possible
   - don't document things that are obvious
   - when possible also provide formulas (see math::number for examples)
   - check your documentation before you commit (make doc)
 - <b>writing unit tests</b>
   - always write unit tests
   - ensure a line coverage above 90%
   - always run the tests before you commit your changes
 - <b>no compiler warnings</b>
   - keep compiler warnings extremely low
   - preferable: 0 warnings
 - <b>ensure consistent versioning</b>
   - read [**Version Policy**](#version-policy)
   - provide a version on each commit (see git log for examples)
 - <b>using other tools</b>
   - check for memory leaks and violatios (make memcheck)


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
