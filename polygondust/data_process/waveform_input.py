import pywavefront
from PolygonDust import Point, Polygon

class WaveformInput:
    def __init__(self, paths: list[str] | None):
        self.polygons: list[Polygon] = self.build(paths)
    
    def build(self, paths: list[str]):
        polygons: list[Polygon] = []

        if paths is None:
            return polygons

        for polygon_path in paths:
            scene: pywavefront.Wavefront = pywavefront.Wavefront(polygon_path[0], strict=True, encoding="utf-8", parse=False)
            scene.parse()

            polygon = Polygon([Point(vertice[0], vertice[1]) for vertice in scene.vertices])
            polygons.append(polygon)
        return polygons
    
    def get_result(self) -> list[Polygon]:
        return self.polygons