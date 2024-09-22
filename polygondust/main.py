from __future__ import print_function
from argparse import ArgumentParser, Namespace

import PolygonDust

def initialize_argument_parser() -> ArgumentParser:
    parser: ArgumentParser = ArgumentParser()
    parser.add_argument("-i", "--input", help="Input image.")
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

    print("Input image:", args.input)
    print("Particles size:", args.particles, "px")


if __name__ == "__main__":
    main()
