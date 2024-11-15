from __future__ import print_function
from argparse import ArgumentParser, Namespace

import pywavefront

from PolygonDust import Polygon, Point, RasterizationContext
from draw_util.rasterization_graphic_context import RasterizationGraphicContext, RasterizationGraphicContextBoundary

def initialize_argument_parser() -> ArgumentParser:
    parser: ArgumentParser = ArgumentParser()
    parser.add_argument("-i", "--input", help="Input a polygon with vertexs.", action='append', nargs='+')
    parser.add_argument("-p", "--particles", help="Particles size (in pixel).")
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

    edge: float = float(args.particles)
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
            )
        ) as graphic_context:
            graphic_context.draw_grid()
            graphic_context.draw_boundary()

            for i in range(len(polygons)):
                cells = raster_context.GetPolygonCell(i)

                for point in cells:
                    graphic_context.draw_cell(point.GetX(), point.GetY(), graphic_context.color_set(i))

                graphic_context.show()

if __name__ == "__main__":
    main()
