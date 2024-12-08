import matplotlib.pyplot as plt
from matplotlib.patches import Polygon as PLTPloygon
from PolygonDust import Polygon, VectorizationContext

def vectorization(polygons: list[Polygon], no_show=False):
    with VectorizationContext(polygons[0]) as context:

        for polygon in polygons[1:]:
            context.ClipPolygon(polygon)

        polygon_result = context.GetResult()

        print("Area", polygon_result.GetArea())

        if not no_show:
            fig, ax = plt.subplots()

            result_polygon: PLTPloygon = PLTPloygon([(point.GetX(), point.GetY()) for point in polygon_result.GetVertex()], color="yellow")
            plt_polygon: PLTPloygon = PLTPloygon([(point.GetX(), point.GetY()) for point in polygons[0].GetVertex()], color="blue")
            cut_polygon: PLTPloygon = PLTPloygon([(point.GetX(), point.GetY()) for point in polygons[1].GetVertex()], color="red")
            ax.add_patch(plt_polygon)
            ax.add_patch(cut_polygon)
            ax.add_patch(result_polygon)
            ax.axis("equal")

            plt.show()