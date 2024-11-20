from PIL import Image, ImageDraw
from dataclasses import dataclass


@dataclass
class RasterizationGraphicContextBoundary:
    min_x: float
    max_x: float
    min_y: float
    max_y: float


class RasterizationGraphicContext:
    def color_set(self, index: int):
        color_set = ["#F44336", "#3F51B5", "#8BC34A"]
        return color_set[index % len(color_set)]

    def __init__(self, edge: int, boundaryXY: RasterizationGraphicContextBoundary, padding: float = 50):
        self.edge = edge
        self.image_size = (5000, 5000)
        self.background_color = (255, 255, 255)
        self.image = Image.new("RGB", self.image_size, self.background_color)
        self.draw = ImageDraw.Draw(self.image)
        self.min_x = boundaryXY.min_x
        self.max_x = boundaryXY.max_x
        self.min_y = boundaryXY.min_y
        self.max_y = boundaryXY.max_y
        self.padding = padding

    def __enter__(self):
        return self

    def __exit__(self, type, value, traceback):
        pass

    def __transform_coordinate_xy_to_index_xy(self, coord_x: float, coord_y: float) -> tuple[int]:
        index_x = (coord_x - self.min_x) / self.edge
        index_y = (self.max_y - coord_y) / self.edge
        return (index_x, index_y)
    
    def __transform_index_xy_to_cells_boundary(self, index_x: float, index_y: float) -> tuple[int]:
        cells_x = (self.max_x - self.min_x) / self.edge
        cells_y = (self.max_y - self.min_y) / self.edge
        cells_x_width = (self.image_size[0] - self.padding * 2) // cells_x
        cells_y_width = (self.image_size[1] - self.padding * 2) // cells_y
        cells_width = min(cells_x_width, cells_y_width)
        return (
            self.padding + cells_width * index_x, 
            self.padding + cells_width * index_y,
            self.padding + cells_width * index_x + cells_width, 
            self.padding + cells_width * index_y + cells_width
        )
    
    def draw_boundary(self):
        self.draw.line((self.padding, self.padding, self.image_size[0]-self.padding, self.padding), width=10, fill="black")
        self.draw.line((self.padding, self.padding, self.padding, self.image_size[1]-self.padding), width=10, fill="black")
        self.draw.line((self.padding, self.image_size[1]-self.padding, self.image_size[0]-self.padding, self.image_size[1]-self.padding), width=10, fill="black")
        self.draw.line((self.image_size[0]-self.padding, self.padding, self.image_size[0]-self.padding, self.image_size[1]-self.padding), width=10, fill="black")

    def draw_grid(self):
        cells_x = (self.max_x - self.min_x) // self.edge
        cells_y = (self.max_y - self.min_y) // self.edge
        cells_x_width = (self.image_size[0] - self.padding * 2) // cells_x
        cells_y_width = (self.image_size[1] - self.padding * 2) // cells_y
        cells_width = min(cells_x_width, cells_y_width)
        cells_max_x = (self.image_size[0] - self.padding * 2) // cells_width
        cells_max_y = (self.image_size[1] - self.padding * 2) // cells_width
        
        for index_x in range(int(cells_max_x)):
            for index_y in range(int(cells_max_y)):
                cells_xy = self.__transform_index_xy_to_cells_boundary(index_x, index_y)
                self.draw.rectangle(cells_xy, outline="black")

    def draw_cell(self, x: int, y: int, color: str):
        index_x, index_y = self.__transform_coordinate_xy_to_index_xy(x, y)
        cells_xy = self.__transform_index_xy_to_cells_boundary(index_x, index_y)
        self.draw.rectangle(cells_xy, fill=color)

    def show(self):
        self.image.show()