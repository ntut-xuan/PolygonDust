"""

        Pybind11 example plugin
        -----------------------

        .. currentmodule:: PolygonDust

        .. autosummary::
           :toctree: _generate

           add
           subtract
    
"""
from __future__ import annotations
__all__ = ['Polygon']
class Polygon:
    @staticmethod
    def _pybind11_conduit_v1_(*args, **kwargs):
        ...
    def GetArea(self) -> int:
        ...
    def __init__(self) -> None:
        ...
