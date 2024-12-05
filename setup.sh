#!/bin/bash

python3 -m pip install . -v
python3 -m pybind11_stubgen PolygonDust -o .