README
======

Welcome
-------
Welcome to the README of my peŕsonal C++11/cmake refererence project.
It's a kind of knowledge database and small test environment.
The purpose is - of course - to keep everything clean, simple and
well documented.

CMake
-----
Here's the way to go (at least for me):
 | mkdir build
 | cd build
 | cmake ..
 | make

A list of useful options:
 | cmake -G "CodeBlocks - Unix Makefiles" ..
 | cmake -DCMAKE_BUILD_TYPE=Debug ..


You also can do:
 | make check     (do not use make test since it does NOT build)
 | make run       (does run the test without "ctest")

For creating a RPM package (sudo is important):
 | sudo make package
