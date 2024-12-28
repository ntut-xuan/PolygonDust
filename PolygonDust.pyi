"""

        PolygonDust
        -----------------------

        .. currentmodule:: PolygonDust

        .. autosummary::
           :toctree: _generate

           Polygon
           Point
           RasterizationContext
           RasterizationCells
    
"""
from __future__ import annotations
import typing
__all__ = ['Point', 'Polygon', 'RasterizationCells', 'RasterizationContext', 'VectorizationContext']
class Point:
    """
    A Point class for create a point
    """
    @staticmethod
    def _pybind11_conduit_v1_(*args, **kwargs):
        ...
    def GetX(self) -> float:
        """
        Get the X of the point
        """
    def GetY(self) -> float:
        """
        Get the Y of the point
        """
    def __init__(self, arg0: float, arg1: float) -> None:
        ...
    def __repr__(self) -> str:
        ...
class Polygon:
    """
    A Polygon class for create a polygon
    """
    @staticmethod
    def _pybind11_conduit_v1_(*args, **kwargs):
        ...
    def GetArea(self) -> float:
        """
        Get the area of polygon
        """
    def GetVertex(self) -> list[Point]:
        """
        Get the vertexs of polygon
        """
    @typing.overload
    def __init__(self) -> None:
        ...
    @typing.overload
    def __init__(self, arg0: list[Point]) -> None:
        ...
class RasterizationCells:
    """
    A Rasterization Cell class for store the cell and do some operation
    """
    @staticmethod
    def _pybind11_conduit_v1_(*args, **kwargs):
        ...
    def Cut(self, arg0: RasterizationCells) -> None:
        """
        Get the cell set
        """
    def GetCellSet(self) -> set[Point]:
        """
        Get the cell set
        """
    def Intersect(self, arg0: RasterizationCells) -> None:
        """
        Get the cell set
        """
    def Union(self, arg0: RasterizationCells) -> None:
        """
        Get the cell set
        """
    def __init__(self, arg0: list[Point]) -> None:
        ...
class RasterizationContext:
    """
    A RasterizationContext class for add multiple polygon into rasterization
    """
    @staticmethod
    def _pybind11_conduit_v1_(*args, **kwargs):
        ...
    def AddPolygon(self, arg0: Polygon) -> None:
        """
        Add Polygon
        """
    def GetMaxX(self) -> float:
        """
        Get max X
        """
    def GetMaxY(self) -> float:
        """
        Get max Y
        """
    def GetMinX(self) -> float:
        """
        Get min X
        """
    def GetMinY(self) -> float:
        """
        Get min Y
        """
    def GetPolygonCell(self, arg0: int) -> RasterizationCells:
        """
        Get the cell of Polygon
        """
    def __enter__(self) -> RasterizationContext:
        ...
    def __exit__(self, arg0: typing.Any, arg1: typing.Any, arg2: typing.Any) -> None:
        ...
    def __init__(self, arg0: float) -> None:
        ...
class VectorizationContext:
    """
    A VectorizationContext class for add multiple polygon into vectorization
    """
    @staticmethod
    def _pybind11_conduit_v1_(*args, **kwargs):
        ...
    def ClipPolygon(self, arg0: Polygon) -> None:
        """
        Clip polygon
        """
    def GetIntersectPoint(self) -> list[Point]:
        """
        Get intersect points
        """
    def GetResult(self) -> list[Polygon]:
        """
        Get clipped polygon result
        """
    def __enter__(self) -> VectorizationContext:
        ...
    def __exit__(self, arg0: typing.Any, arg1: typing.Any, arg2: typing.Any) -> None:
        ...
    def __init__(self, arg0: Polygon) -> None:
        ...
