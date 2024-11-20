#!/bin/bash

# This script is intended to be used in automated testing
# Specifically, in a Linux environment with certain packages installed
# If you want to use this script, please copy this file and make changes
# However, we DO NOT guarantee this script would work on every machine

: ${CC:=gcc}
: ${CXX:=g++}

BUILD_DIR=coverage_build

rm -rf ./${BUILD_DIR}

cmake \
    -B $BUILD_DIR \
    -DCOVERAGE=ON \
    -DCMAKE_C_COMPILER=$CC \
    -DCMAKE_CXX_COMPILER=$CXX \

cmake --build $BUILD_DIR

"./${BUILD_DIR}/build/PolygonDust-gtest"

if [ "$1" = 'xml' ]; then
    cmake --build $BUILD_DIR --target polygondust-coverage-xml
fi

if [ "$1" = "html" ]; then
    gcovr . --exclude "_deps"  --exclude "test"  --exclude "pyb_includes" --exclude "coverage_build/_deps" --exclude "src/main_pyb.cpp" -b --exclude-unreachable-branches --html-details ./${BUILD_DIR}/index.html
fi

if [ "$1" = "branch" ]; then
    gcovr . --exclude "_deps"  --exclude "test"  --exclude "pyb_includes" --exclude "coverage_build/_deps" --exclude "src/main_pyb.cpp" -b --exclude-unreachable-branches
else
    gcovr . --exclude "_deps"  --exclude "test"  --exclude "pyb_includes" --exclude "coverage_build/_deps" --exclude "src/main_pyb.cpp"
fi