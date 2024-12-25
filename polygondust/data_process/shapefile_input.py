import fiona
from PolygonDust import Point, Polygon

class ShapefileInput:
    def __init__(self, paths: list[str] | None):
        self.polygons: list[Polygon] = self.build(paths)
    
    def build(self, paths: list[str] | None):
        polygons: list[Polygon] = []

        if paths is None:
            return polygons

        for shapefile_path in paths:
            with fiona.open(shapefile_path[0], "r") as shapefile:
                for feature in shapefile:
                    geometry = feature['geometry']
                
                    print(geometry)

                    # Ensure it's a polygon
                    if geometry['type'] == 'Polygon':
                        coordinates = geometry['coordinates'][0]  # Outer boundary
                        print(f"Shapefile {shapefile_path} have {len(coordinates)} vertexes.")
                        polygon = Polygon([Point(vertice[0], vertice[1]) for vertice in coordinates])
                        polygons.append(polygon)

                    if geometry['type'] == "MultiPolygon":
                        for i in range(len(geometry['coordinates'])):
                            coordinates = geometry['coordinates'][i][0]
                            print(f"Shapefile {shapefile_path} have {len(coordinates)} vertexes.")
                            polygon = Polygon([Point(vertice[0], vertice[1]) for vertice in coordinates])
                            polygons.append(polygon)
        return polygons
    
    def get_result(self) -> list[Polygon]:
        return self.polygons