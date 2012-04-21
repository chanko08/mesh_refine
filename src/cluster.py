import sys
sys.path.append("../src")

import math
import itertools
from obj import load_obj, save_obj

class Mesh(object):
    def __init__(self, faces, vertices):
        self.faces = faces
        self.vertices = vertices

        #compute edge tables for vertices
        self.edges = []
        for i,v in enumerate(vertices):
            incidences = []
            for f in faces:
                if v in f:
                    j = (f.index(v) + 1) % len(f)
                    incidences.append(f[j])
            self.edges.append(incidences)

        k = lambda x: vertex_key(self.vertices, self.edges, x) 
        sorted(xrange(len(self.vertices)), key = k)


def dist(v,u):
    r = math.sqrt(sum([(i-j)**2 for i,j  in zip(v,u)])) 
    return r

def vec(p1,p2):
    return [p1[i] - p2[i] for i in xrange(len(p1))]

def dot(v1,v2):
    return sum([v1[i]*v2[i] for i in xrange(len(v1))])

def mag(v1):
    return math.sqrt(dot(v1,v1))

def incident_angle(v1,v2):
    r = dot(v1,v2) / (mag(v1) * mag(v2))
    
    if r > 1: return 0
    if r < -1: return math.pi

    return math.acos(r)

def vertex_key(vertices, edges, index):
    if not index: return 0
    v = vertices[index]
    e = edges[index]

    face_size = max([dist(v, u) for u in e])

    max_t = 0
    for u1 in e:
        for u2 in e:
            #find angle between these
            v1, v2 = vec(v,u1), vec(v,u2)
            t  = math.cos(incident_angle(v1,v2) / 2.0)
            if t > max_t:
                max_t = t

    return max_t, face_size
             




usage = """Usage: cluster [OPTIONS] INPUT_FILE OUTPUT_FILE
Performs centered-cell vertex clustering on a Wavefront OBJ file and outputs results to file

Options:
    -r RESOLUTION   Sets the amount of refinement to be done to a given mesh. Defaults to 10.0
"""

if __name__ == "__main__":
    if len(sys.argv) not in [3,5]:
        print usage
        sys.exit(1)
    elif "-r" in sys.argv and len(sys.argv) != 5:
        print usage
        sys.exit(1)
    elif "-r" in sys.argv and sys.argv.index("-r") > 1:
        print usage
        sys.exit(1)

    resolution = 10.0
    if "-r"  in sys.argv:
        i = sys.argv.index("-r") + 1
        resolution = float(sys.argv[i])

    infile = sys.argv[-2]
    outfile = sys.argv[-1]
    
    print "started"
    faces,vertices = load_obj(infile)
    Mesh(faces,vertices)
    print "done"
