from __future__ import print_function
from argparse import ArgumentParser, Namespace

import pywavefront

from PolygonDust import Polygon, Point, RasterizationContext
from PIL import Image, ImageDraw

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
    print("Particles size:", args.particles, "px")

    scene: pywavefront.Wavefront = pywavefront.Wavefront(args.input, strict=True, encoding="utf-8", parse=False)
    scene.parse()

    polygon = Polygon([Point(vertice[0], vertice[1]) for vertice in scene.vertices])

    context = RasterizationContext(0.5)
    context.AddPolygon(polygon)

    cells: list = context.GetPolygonCell(0)
    print(cells)

if __name__ == "__main__":
    main()
