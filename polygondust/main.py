from __future__ import print_function
from argparse import ArgumentParser, Namespace

import pywavefront

from PolygonDust import Polygon, Point
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

    polygon = Polygon([Point(int(vertice[0]), int(vertice[1])) for vertice in scene.vertices])
    boundary_cell: set[Point] = polygon.GetBoundaryCell(float(args.particles))

    print([(p.GetX(), p.GetY()) for p in boundary_cell])

    image_size = (500, 500)
    background_color = (255, 255, 255) 
    image = Image.new("RGB", image_size, background_color)
    draw = ImageDraw.Draw(image)

    max_x = -2147483647
    max_y = -2147483647
    for p in boundary_cell:
        max_x = max(p.GetX(), max_x)
        max_y = max(p.GetY(), max_y)

    offset = 5
    square_width = (500 - 2*offset) / ((max_x/float(args.particles))+1)
    squares = [(offset + (p.GetX()/float(args.particles)) * square_width, 500-offset-square_width-(p.GetY()/float(args.particles)) * square_width, square_width) for p in boundary_cell]

    for x, y, side_length in squares:
        draw.rectangle([x, y, x + side_length, y + side_length], fill="black", width=1)

    image.save("squares.png")
    image.show()

if __name__ == "__main__":
    main()
