import math

import copy

from enum import Enum, auto

class system_coord(Enum):
    Cartesian = auto()
    Polar = auto()

class Point:
    
    def __init__(self, a1=0, a2=0, coord_system=system_coord.Cartesian):
        if type(a1) != str:
            if system_coord.Cartesian:
                self.x = a1
                self.y = a2
            else:
                self.x = math.cos(a2) * a1
                self.y = math.sin(a2) * a1
        else:
            cord = a1.find(',')
            self.x = float(a1[1:cord].strip())
            self.y = float(a1[cord + 1:-2].strip())

    def __eq__(self, other):
        return (abs(self.x - other.x) < 1e-10) and (abs(self.y - other.y) < 1e-10)

    def __ne__(self, other):
        return not (self == other)

    def get_x(self):
        return self.x

    def get_y(self):
        return self.y
    
    def set_x(self, x):
        self.x = x
        
    def set_y(self, y):
        self.y = y

    def get_r(self):
        return math.hypot(self.x, self.y)

    def get_phi(self):
        return math.atan2(self.y, self.x)

    def set_phi(self, phi):
        r = self.get_r()
        self.x = r * math.cos(phi)
        self.y = r * math.sin(phi)

    def __repr__(self):
        return f'Point({self.x}, {self.y})'

    def __str__(self):
        return f'({self.x}, {self.y})'


with open('data.txt') as fin:
    original = [Point(p) for p in fin.readline().split(', ')]

simulacrum = copy.deepcopy(original)
for p in simulacrum:
    print(p, end='')
    p.set_x(p.get_x() + 10)
    p.set_phi(p.get_phi() + 180 * math.pi / 180)
    p.set_y(-p.get_y())
    p.set_x(-p.get_x() - 10)
    print(p)

print('\nIt works!\n' if simulacrum == original else '\nIt not works!\n')
