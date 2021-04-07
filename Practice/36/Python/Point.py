import math

import copy

  

class Point:

    pass # Ваш код здесь

   def get_x(self):
        return self.x

    def set_x(self, x):
        self.x = x

    def get_y(self):
        return self.y

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

  

with open('data.txt') as fin:

    original = [Point(p) for p in fin.readline().split(', ')]

  

simulacrum = copy.deepcopy(original)

for p in simulacrum:

    print(p, end='')

    p.set_x(p.get_x() + 10)

    p.set_phi(p.get_phi() + 180*math.pi/180)

    p.set_y(-p.get_y())

    p.set_x(-p.get_x() - 10)

    print(p)

  

print('\nIt works!\n' if simulacrum == original else '\nIt not works!\n')
