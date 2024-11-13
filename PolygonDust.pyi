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
__all__ = ['Point', 'Polygon', 'RasterizationContext']
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
    @typing.overload
    def __init__(self) -> None:
        ...
    @typing.overload
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
    def GetPolygonCell(self, arg0: int) -> list[Point]:
        """
        Get the cell of Polygon
        """
    def __init__(self, arg0: float) -> None:
        ...
