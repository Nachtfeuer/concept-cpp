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
 - pattern classes like a factory.
 - math classes like a 2d vector.
 - you can create HTML documentation with doxygen.


Next Action Items (planned)
---------------------------
 - providing report generator for unittesting framework.
 - singleton decorator class (remove singleton from factory)
 - performance measurement for tests.
 - passsing command line parameters to runner (unittests)
 - generating Jenkins compatible report for unittests.
 - adding code coverage to cmake project.


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
```

For creating a RPM package (sudo is important):
```
 sudo make package
```

