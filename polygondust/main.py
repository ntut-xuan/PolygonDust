from __future__ import print_function
from argparse import ArgumentParser, Namespace

import pywavefront

from PolygonDust import Polygon, Point, RasterizationContext
from draw_util.rasterization_graphic_context import RasterizationGraphicContext, RasterizationGraphicContextBoundary

def initialize_argument_parser() -> ArgumentParser:
    parser: ArgumentParser = ArgumentParser()
    parser.add_argument("-i", "--input", help="Input a polygon with vertexs.")
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

    print("Input vertexs:", args.input)
    print("Particles edge:", args.particles, "m")

    edge: float = float(args.particles)

    scene: pywavefront.Wavefront = pywavefront.Wavefront(args.input, strict=True, encoding="utf-8", parse=False)
    scene.parse()

    polygon = Polygon([Point(vertice[0], vertice[1]) for vertice in scene.vertices])

    with RasterizationContext(edge) as raster_context:
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

            cells = raster_context.GetPolygonCell(0)

            counts: dict[str, int] = {}

            for point in cells:
                if point.GetY() not in counts:
                    counts[point.GetY()] = 1
                else:
                    counts[point.GetY()] += 1
                graphic_context.draw_cell(point.GetX(), point.GetY(), "red")

            graphic_context.show()

if __name__ == "__main__":
    main()
