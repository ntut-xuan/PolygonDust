from __future__ import print_function
from argparse import ArgumentParser, Namespace

import pywavefront

from PolygonDust import Polygon, Point

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

    polygon = Polygon([Point(int(vertice[0]), int(vertice[1])) for vertice in scene.vertices])
    vertexs = polygon.GetVertexs()

    for vertex in vertexs:
        print(vertex.GetX(), vertex.GetY())


if __name__ == "__main__":
    main()
