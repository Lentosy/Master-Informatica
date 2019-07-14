from pyquaternion import Quaternion
from math import sqrt

class Quaternion4D(Quaternion):
    def to_point(self):
        if(abs(int(self.w)) == 0):
            return Point3D(self.x, self.y, self.z)
        
class Point3D(object):
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def __str__(self):
        return f"Point3D({self.x} {self.y} {self.z})"

    def __sub__(self, other):
        self.x -= other.x
        self.y -= other.y
        self.z -= other.z
        return self

    def __add__(self, other):
        self.x += other.x
        self.y += other.y
        self.z += other.z
        return self
    
    def __mul__(self, scalar):
        self.x *= scalar
        self.y *= scalar
        self.z *= scalar
        return self

    def __rmul__(self, scalar):
        self.x *= scalar
        self.y *= scalar
        self.z *= scalar
        return self

    def __truediv__(self, scalar):
        self.x /= scalar
        self.y /= scalar
        self.z /= scalar
        return self

    

    def norm(self):
        return sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
    def to_quaternion(self):
        return Quaternion(w=0, x=self.x, y=self.y, z=self.z)

class Joint(object):
    def __init__(self, name, weight, point, quaternion):
        self.name = name
        self.point = point
        self.quaternion = quaternion
        self.weight = weight


    def __str__(self):
        return f"{self.name}\n\t{self.point}\n\t{repr(self.quaternion)}"


    def flatten(self):
        return [self.point.x, self.point.y, self.point.z, self.quaternion.x, self.quaternion.y, self.quaternion.z, self.quaternion.w]
