import matplotlib.pyplot as plt
from matplotlib.patches import Polygon as PLTPloygon
from PolygonDust import Polygon, VectorizationContext

def vectorization(polygons: list[Polygon], no_show=False):
    with VectorizationContext(polygons[0]) as context:

        for polygon in polygons[1:]:
            context.ClipPolygon(polygon)

        polygon_result = context.GetResult()

        print(len(polygon.GetVertex()))

        print("Area", sum([polygon.GetArea() for polygon in polygon_result]))

        if not no_show:
            fig, ax = plt.subplots()
            
            plt_polygon: PLTPloygon = PLTPloygon([(point.GetX(), point.GetY()) for point in polygons[0].GetVertex()], color="blue")
            cut_polygon: PLTPloygon = PLTPloygon([(point.GetX(), point.GetY()) for point in polygons[1].GetVertex()], color="red")
            ax.add_patch(plt_polygon)
            ax.add_patch(cut_polygon)
            
            for polygon in polygon_result:
                result_polygon: PLTPloygon = PLTPloygon([(point.GetX(), point.GetY()) for point in polygon.GetVertex()], color="orange")
                ax.add_patch(result_polygon)
                
            for intersect_point in context.GetIntersectPoint():
                ax.plot(intersect_point.GetX(), intersect_point.GetY(), "bo")

            ax.axis("equal")

            plt.show()