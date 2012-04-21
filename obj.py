import sys

VERTEX = "v"
FACE = "f"
USEMTL = "usemtl"
COMMENT = "#"

def load_obj(obj_fname):
    vertices = []
    faces = []


    with open(obj_fname) as f:
        for line in f:
            words = line.strip().split()
            
            
            #words is empty
            if not words: continue
            
            prop = words[0]
            words = words[1:]

            if prop.startswith(COMMENT): continue

            if prop == VERTEX:
                vert = tuple([float(x) for x in words])
                vertices.append(vert)

            elif prop == FACE:
                face = [int(w.split("/")[0]) for w in words]
                faces.append(face)

    #all faces/verts have been loaded, now move vertices that are used to 
    #the respective faces
    for i,face in enumerate(faces):
        faces[i] =  [vertices[j-1] for j in face]

    return faces, vertices

def save_obj(fname, faces, vertices = None):
    if vertices is None: vertices = list(set((faces)))

    indices_to_save = []

    for face in faces:
        indices = []
        for v in face:
            indices.append(vertices.index(v))
        indices_to_save.append(indices)
    
    with open(fname,'w') as f:
        for vertex in vertices:
            v = "v {0} {1} {2}\n".format(*vertex)
            f.write(v)
        
        for indices in indices_to_save:
            face = "f "
            for index in indices:
                face += str(index) + " "
            face += "\n"
            f.write(face)
 
if __name__ == "__main__":
    if "-o" not in sys.argv:
        print "expecting obj file"
        sys.exit(1)

    obj = sys.argv[sys.argv.index("-o") + 1]
    faces, vertices = load_obj(obj)

    if "-p" in sys.argv:
        out = sys.argv[sys.argv.index("-p") + 1]
        save_obj(out, faces, vertices)

    for i,f in enumerate(faces):
        print "FACE #{0}".format(i)
        print f


                

        
