from __future__ import print_function
from argparse import ArgumentParser, Namespace

import pywavefront
import fiona

from PolygonDust import Polygon, Point, RasterizationContext
from data_process.waveform_input import WaveformInput
from data_process.raw_input import RawInput
from data_process.shapefile_input import ShapefileInput
from draw_util.rasterization_graphic_context import RasterizationGraphicContext, RasterizationGraphicContextBoundary
from vectorization.vectorization_context import vectorization

def initialize_argument_parser() -> ArgumentParser:
    parser: ArgumentParser = ArgumentParser()
    parser.add_argument("-i", "--input_waveform", help="Input a polygon with vertexs.", action='append', nargs='+')
    parser.add_argument("-r", "--input_raw", help="Input a raw polygon with vertexs.", action='append', nargs='+')
    parser.add_argument("-s", "--input_shpfile", help="Input a shapefile with vertexs.", action='append', nargs='+')
    parser.add_argument("-p", "--particles", help="Particles size (in pixel).")
    parser.add_argument("-o", "--operation", help="Polygon Operation (Union=U, Intersect=I, Cut=C), e.g. \"UUIC\"")
    parser.add_argument("-v", "--vector", help="Use vector clipping", action='store_true')
    parser.add_argument("--no-show", help="Don't show the polygon presentation", action='store_true')
    return parser

def main():
    parser: ArgumentParser = initialize_argument_parser()
    args: Namespace = parser.parse_args()

    if args.input_waveform is None and args.input_shpfile is None and args.input_raw is None:
        print("Error: You need to input image file.")
        parser.print_help()
        return

    if args.vector is None and args.particles is None:
        print("Error: You need to input particles size.")
        parser.print_help()
        return

    # print("Input polygons:", len(0 if args.input is None else len(args.input)))
    # print("Input shapefiles:", len(0 if args.input_shpfile is None else len(args.input_shpfile)))

    if args.input_waveform is not None:
        print("Input vertexs:", args.input_waveform)
    
    if args.input_shpfile is not None:
        print("Input shapefile vertexs:", args.input_shpfile)
    
    print("Particles edge:", args.particles, "m")
    print("Operation:", args.operation)

    polygons: list[Polygon] = []

    polygons.extend(WaveformInput(args.input_waveform).get_result())
    polygons.extend(RawInput(args.input_raw).get_result())
    polygons.extend(ShapefileInput(args.input_shpfile).get_result())

    if args.vector:
        vectorization(polygons, args.no_show)
        return 0
    
    edge: float = float(args.particles)
    operation = str(args.operation)

    with RasterizationContext(edge) as raster_context:
        for polygon in polygons:
            raster_context.AddPolygon(polygon)
        
        with RasterizationGraphicContext(
            edge, 
            RasterizationGraphicContextBoundary(
                raster_context.GetMinX(), 
                raster_context.GetMaxX(), 
                raster_context.GetMinY(), 
                raster_context.GetMaxY()
            ),
            padding=150
        ) as graphic_context:
            if args.operation is None or len(operation) == 0:
                print(f"Printing {len(polygons)} polygons.")
                for i in range(len(polygons)):
                    cellset = raster_context.GetPolygonCell(i).GetCellSet()
                    print(len(cellset))
                    for point in cellset:
                        graphic_context.draw_cell(point.GetX(), point.GetY(), graphic_context.color_set(i))
                    print("Area: ", len(cellset) * edge * edge)
            else:
                cells0 = raster_context.GetPolygonCell(0)
                for i in range(1, len(polygons)):
                    cells2 = raster_context.GetPolygonCell(i)
                    oper = operation[i-1]

                    print(f"Operating Polygon {i+1}")

                    if oper == 'U':
                        cells0.Union(cells2)

                    if oper == 'I':
                        cells0.Intersect(cells2)

                    if oper == 'C':
                        print(f"Process opreation CUT on polygon {i+1}")
                        cells0.Cut(cells2)

                print(f"Drawing {len(cells0.GetCellSet())} cells.")
                for point in cells0.GetCellSet():
                    graphic_context.draw_cell(point.GetX(), point.GetY(), graphic_context.color_set(0))
                
                print("Area: ", len(cells0.GetCellSet()) * edge * edge)

            graphic_context.show()

if __name__ == "__main__":
    main()
