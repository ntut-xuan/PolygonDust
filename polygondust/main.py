from __future__ import print_function
from argparse import ArgumentParser, Namespace

import pywavefront

from PolygonDust import Polygon, Point, RasterizationContext
from draw_util.rasterization_graphic_context import RasterizationGraphicContext, RasterizationGraphicContextBoundary

def initialize_argument_parser() -> ArgumentParser:
    parser: ArgumentParser = ArgumentParser()
    parser.add_argument("-i", "--input", help="Input a polygon with vertexs.", action='append', nargs='+')
    parser.add_argument("-p", "--particles", help="Particles size (in pixel).")
    parser.add_argument("-o", "--operation", help="Polygon Operation (Union=U, Intersect=I, Cut=C), e.g. \"UUIC\"")
    return parser

def main():
    parser: ArgumentParser = initialize_argument_parser()
    args: Namespace = parser.parse_args()

    if args.input is None:
        print("Error: You need to input image file.")
        parser.print_help()
        return

    if args.particles is None:
        print("Error: You need to input particles size.")
        parser.print_help()
        return

    print("Input polygons:", len(args.input))
    print("Input vertexs:", args.input)
    print("Particles edge:", args.particles, "m")
    print("Operation:", args.operation)

    edge: float = float(args.particles)
    operation = str(args.operation)
    polygons: list[Polygon] = []

    for polygon_path in args.input:
        scene: pywavefront.Wavefront = pywavefront.Wavefront(polygon_path[0], strict=True, encoding="utf-8", parse=False)
        scene.parse()

        polygon = Polygon([Point(vertice[0], vertice[1]) for vertice in scene.vertices])
        polygons.append(polygon)

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
            if len(operation) == 0:
                for i in range(len(polygons)):
                    for point in raster_context.GetPolygonCell(i):
                        graphic_context.draw_cell(point.GetX(), point.GetY(), graphic_context.color_set(i))
            else:
                cells0 = raster_context.GetPolygonCell(0)
                for i in range(1, len(polygons)):
                    cells2 = raster_context.GetPolygonCell(i)
                    oper = operation[i-1]

                    if oper == 'U':
                        cells0.Union(cells2)

                    if oper == 'I':
                        cells0.Intersect(cells2)

                    if oper == 'C':
                        cells0.Cut(cells2)

                for point in cells0.GetCellSet():
                    graphic_context.draw_cell(point.GetX(), point.GetY(), graphic_context.color_set(0))

            graphic_context.show()

if __name__ == "__main__":
    main()
