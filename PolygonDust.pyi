"""

        PolygonDust
        -----------------------

        .. currentmodule:: PolygonDust

        .. autosummary::
           :toctree: _generate

           Polygon
    
"""
from __future__ import annotations
__all__ = ['Point', 'Polygon']
class Point:
    """
    A Point class for create a point
    """
    @staticmethod
    def _pybind11_conduit_v1_(*args, **kwargs):
        ...
    def GetX(self) -> int:
        """
        Get the X of the point
        """
    def GetY(self) -> int:
        """
        Get the Y of the point
        """
    def __init__(self, arg0: int, arg1: int) -> None:
        ...
class Polygon:
    """
    A Polygon class for create a polygon
    """
    @staticmethod
    def _pybind11_conduit_v1_(*args, **kwargs):
        ...
    def GetArea(self) -> int:
        """
        Get the area of polygon
        """
    def __init__(self) -> None:
        ...
