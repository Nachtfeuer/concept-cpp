@echo off
set MINGW_HOME=C:\ProgramData\chocolatey\lib\mingw\tools\install\mingw64
set CMAKE_HOME=C:\ProgramData\chocolatey\lib\cmake.portable\tools\cmake-3.16.2-win64-x64
set MAKE_HOME=C:\ProgramData\chocolatey\lib\make\tools\install
set UNZIP_HOME=C:\ProgramData\chocolatey\lib\unzip\tools
set BOOST_ROOT=%CD%\build.boost\boost_1_72_0
set Path=%MINGW_HOME%\bin;%CMAKE_HOME%\bin;%MAKE_HOME%\bin;%UNZIP_HOME%;%Path%

if exist build (
    rmdir /s /q build
)

if not exist build.boost (
    mkdir build.boost
    cd build.boost

    echo Download boost ...
    curl -s -L https://dl.bintray.com/boostorg/release/1.72.0/source/boost_1_72_0.zip -oboost.zip
    echo Unpack boost ...
    unzip boost.zip > nul
    echo Build boost ...
    cd boost_1_72_0
    bootstrap gcc --with-libraries=date_time,filesystem,system,iostreams,regex,python,test,program_options
    .\b2 threading=multi --prefix=%BOOST_ROOT% -d0 

    cd ..\..
)


set BOOST_INCLUDEDIR=%BOOST_ROOT%
set BOOST_LIBRARYDIR=%BOOST_ROOT%\stage\lib
set BOOST_USE_STATIC_LIBS=ON

mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DBoost_ARCHITECTURE:STRING=-x64
make
