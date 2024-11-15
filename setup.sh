#!/bin/bash

rm -rf _deps .cache build CMakeFiles CMakeCache.txt cmake_install.cmake CTestTestfile.cmake Makefile PolygonDust-*.cmake PolygonDust.*.so
python3 -m pip install . -v
pybind11-stubgen PolygonDust -o .