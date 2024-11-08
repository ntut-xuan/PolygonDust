"""

        PolygonDust
        -----------------------

        .. currentmodule:: PolygonDust

        .. autosummary::
           :toctree: _generate

           Polygon
           Point
    
"""
from __future__ import annotations
import typing
__all__ = ['Point', 'Polygon']
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
    def GetBoundaryCell(self, arg0: float) -> list[Point]:
        """
        Get the boundary cell of polygon
        """
    def GetPolygonCell(self, arg0: float) -> list[Point]:
        """
        Get the polygon cell of polygon
        """
    def GetVertexs(self) -> list[Point]:
        """
        Get the vertexs of polygon
        """
    @typing.overload
    def __init__(self) -> None:
        ...
    @typing.overload
    def __init__(self, arg0: list[Point]) -> None:
        ...
