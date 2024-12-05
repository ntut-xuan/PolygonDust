import matplotlib.pyplot as plt
from matplotlib.patches import Polygon as PLTPloygon
from PolygonDust import Polygon, VectorizationContext

def vectorization(polygons: list[Polygon]):
    with VectorizationContext(polygons[0]) as context:

        for polygon in polygons[1:]:
            context.ClipPolygon(polygon)

        polygon_result = context.GetResult()

        print(polygon_result.GetVertex())

        fig,ax = plt.subplots()

        # cut_polygon: PLTPloygon = PLTPloygon([(point.GetX(), point.GetY()) for point in polygons[1].GetVertex()], color="red")
        plt_polygon: PLTPloygon = PLTPloygon([(point.GetX(), point.GetY()) for point in polygon_result.GetVertex()], color="blue")
        # ax.add_patch(cut_polygon)
        ax.add_patch(plt_polygon)
        ax.axis("equal")

        plt.show()