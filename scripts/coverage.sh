#!/bin/bash

# This script is intended to be used in automated testing
# Specifically, in a Linux environment with certain packages installed
# If you want to use this script, please copy this file and make changes
# However, we DO NOT guarantee this script would work on every machine

: ${CC:=gcc}
: ${CXX:=g++}

BUILD_DIR=coverage_build

cmake \
    -B $BUILD_DIR \
    -DCOVERAGE=ON \
    -DCMAKE_C_COMPILER=$CC \
    -DCMAKE_CXX_COMPILER=$CXX \

cmake --build $BUILD_DIR

"./${BUILD_DIR}/build/polygondust-gtest"

if [ "$1" == 'xml' ] 
then
    cmake --build $BUILD_DIR --target polygondust-coverage-xml;
else
    cmake --build $BUILD_DIR --target polygondust-coverage;
fi