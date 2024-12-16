# PolygonDust

[![Build and Test](https://github.com/ntut-xuan/PolygonDust/actions/workflows/build-and-test.yaml/badge.svg)](https://github.com/ntut-xuan/PolygonDust/actions/workflows/build-and-test.yaml) [![codecov](https://codecov.io/github/ntut-xuan/PolygonDust/graph/badge.svg?token=BBZ5OFOU8Y)](https://codecov.io/github/ntut-xuan/PolygonDust)

![未命名绘图 drawio](https://github.com/user-attachments/assets/56003f8d-1929-4cd1-ae04-4d9b6e151881)

## Description

PolygonDust is an application to measure the area size of polygon with support complex polygon overlap analysis. You can cut, union, or intersect any two polygon to make a complex ploygon.

PolygonDust use raster-based method to measure the area size of polygon instead of vector-based method. We use *adjustable error-rate* [1] to strive for the fast process of overlap analysis, cause vector-based ovelap analysis will not efficient when meet huge amount of vertexs of polygon [2].

PolygonDust accept Shapefile (Should be polygon or multipolygon) or Waveform object file. Please take a look about [Usage](#usage).

 * [1] We call it *adjustable error-rate* becasue the user can decide small size of particles and decrease the error-rate. With small particles may increase the accuracy but also increase the process time, large particles may increase the error-rate but faster.
 * [2] We reference the view of this paper [Rasterization Computing-Based Parallel Vector Polygon Overlay Analysis Algorithms Using OpenMP and MPI](https://ieeexplore.ieee.org/abstract/document/8335249), which declare that vector-based polygon overlap analysis may inefficient on the polygon with huge amount of vertexes.

## Installization

Please make sure that you already have Python environment, C++ compiler, CMake and Make.

```
pip install -r requirements.txt
pip install . -v
```

## Usage

```
usage: main.py [-h] [-i INPUT [INPUT ...]] [-s INPUT_SHPFILE [INPUT_SHPFILE ...]] [-p PARTICLES] [-o OPERATION]

options:
  -h, --help            show this help message and exit
  -i INPUT [INPUT ...], --input INPUT [INPUT ...]
                        Input a polygon with vertexs.
  -s INPUT_SHPFILE [INPUT_SHPFILE ...], --input_shpfile INPUT_SHPFILE [INPUT_SHPFILE ...]
                        Input a shapefile with vertexs.
  -p PARTICLES, --particles PARTICLES
                        Particles size (in pixel).
  -o OPERATION, --operation OPERATION
                        Polygon Operation (Union=U, Intersect=I, Cut=C), e.g. "UUIC"
```

You can try out with simple-polygon waveform object file we provided.

```
./polygondust/main.py -i simple-polygon1.obj -p 0.1
```

You can also try out with NYCU shapefile we provided.

```
./polygondust/main.py -s ./shapefile/NYCU_Campus.shp -p 1
```

We also provide Zhuhu (Which is the lake in NYCU) shapefile, you can union/cut/intersect with these shapefile.

### printing all polygon

```
./polygondust/main.py -s ./shapefile/NYCU_Campus.shp -s ./shapefile/Zhuhu.shp -p 1
```

### operating with polygons

```
./polygondust/main.py -s ./shapefile/NYCU_Campus.shp -s ./shapefile/Zhuhu.shp -p 1 -o "C"
```
