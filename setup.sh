#!/bin/bash

rm -rf _deps .cache build CMakeFiles CMakeCache.txt cmake_install.cmake CTestTestfile.cmake Makefile PolygonDust-*.cmake PolygonDust.pyi PolygonDust.*.so
python3 -m pip install . -v
python3 -m pybind11_stubgen PolygonDust -o .