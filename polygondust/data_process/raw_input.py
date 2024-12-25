from PolygonDust import Point, Polygon

class RawInput:
    def __init__(self, paths: list[str] | None):
        self.polygons: list[Polygon] = self.build(paths)
    
    def build(self, paths: list[str]):
        polygons: list[Polygon] = []

        if paths is None:
            return polygons

        for polygon_path in paths:
            vertex_list = []
            with open(polygon_path[0], "r") as file:
                print(polygon_path[0])
                vertex_lines = file.read().split('\n')
                for vertex_line in vertex_lines:
                    if(len(vertex_line) == 0):
                        continue
                    vertex_list.append(Point(float(vertex_line.split(", ")[0]), float(vertex_line.split(", ")[1])))
            polygon = Polygon(vertex_list)
            polygons.append(polygon)
        return polygons
    
    def get_result(self) -> list[Polygon]:
        return self.polygons