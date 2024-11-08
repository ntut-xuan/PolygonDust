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

    polygon = Polygon([Point(vertice[0], vertice[1]) for vertice in scene.vertices])
    polygonCell: set[Point] = polygon.GetPolygonCell(float(args.particles))
    boundaryCell: set[Point] = polygon.GetBoundaryCell(float(args.particles))
    size: float = polygon.GetArea()

    # print([(p.GetX(), p.GetY()) for p in polygonCell])

    image_size = (500, 500)
    background_color = (255, 255, 255) 
    image = Image.new("RGB", image_size, background_color)
    draw = ImageDraw.Draw(image)

    max_x = -2147483647
    max_y = -2147483647
    for p in polygonCell:
        max_x = max(p.GetX(), max_x)
        max_y = max(p.GetY(), max_y)

    offset = 5
    square_width = min((500 - 2*offset) / ((max_x/float(args.particles))+3), (500 - 2*offset) / ((max_y/float(args.particles))+3))
    polygon_squares = [(offset + (p.GetX()/float(args.particles)) * square_width, 500-offset-square_width-(p.GetY()/float(args.particles)) * square_width, square_width) for p in polygonCell]
    boundary_squares = [(offset + (p.GetX()/float(args.particles)) * square_width, 500-offset-square_width-(p.GetY()/float(args.particles)) * square_width, square_width) for p in boundaryCell]

    for x, y, side_length in polygon_squares:
        draw.rectangle([x, y, x + side_length, y + side_length], fill="orange", width=1)

    for x, y, side_length in boundary_squares:
        draw.rectangle([x, y, x + side_length, y + side_length], fill="black", width=1)

    for x, y, side_length in boundary_squares:
        draw.rectangle([x, y, x + side_length, y + side_length], outline="red", width=1)

    approx_size = (len(polygonCell) + len(boundaryCell)) * (float(args.particles))*float(args.particles)
    print("Block:", len(polygonCell) + len(boundaryCell))
    print("Size:", approx_size)
    print("Error Rate (%)", (approx_size - size) * 100 / size)

    image.save("squares.png")
    image.show()

if __name__ == "__main__":
    main()
