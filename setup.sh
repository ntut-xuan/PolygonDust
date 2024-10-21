#!/bin/bash

python3 -m pip install . -v
pybind11-stubgen PolygonDust -o .