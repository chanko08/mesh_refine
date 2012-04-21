import math

class Quaternion(object):
    def __init__(self, r, im):
        self.real = r
        self.imaginary = im
    
    def __neg__(self):
        return Quaternion(self.real, [-i for i in self.imaginary])

    def __add__(self, other):
        r = self.real + other.real
        im = [self.imaginary[i] + other.imaginary[i] for i in xrange(3)]

        return Quaterion(r,im)

    def __sub__(self, other):
        r = self.real - other.real
        im = [self.imaginary[i] - other.imaginary[i] for i in xrange(3)]

        return Quaternion(r,im)

    def __mul__(self, other):
        a1, a2 = self.real, other.real
        b1,c1,d1 = self.imaginary
        b2,c2,d2 = other.imaginary
            
        r = a1*a2 - b1*b2 - c1*c2 - d1*d2
        
        im = [0,0,0]
        im[0] += a1*b2 + b1*a2 + c1*d2 - d1*c2
        im[1] += a1*c2 - b1*d2 + c1*a2 + d1*b2
        im[2] += a1*d2 + b1*c2 - c1*b2 + d1*a2

        return Quaternion(r,im)


def cos(deg):
    return math.cos(deg / 180.0 * math.pi)

def sin(deg):
    return math.sin(deg / 180.0 * math.pi)


EPSILON = 0.0000001
def rotate_pt(pt, vec, rot):
    pt = Quaternion(0,pt)
    vec = Quaternion(cos(rot / 2.0), [sin(rot/2.0) * x for x in vec])

    pt = vec * pt * -vec
    assert  -EPSILON < pt.real < EPSILON
    return pt.imaginary



