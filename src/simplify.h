#ifndef __SIMPLIFY_H
#define __SIMPLIFY_H

typedef int face_t[3];
typedef float vertex_t[3];

class Mesh {
    public:
    Mesh(char *fname);
    ~Mesh();

    private:

    face_t *faces;
    unsigned int num_faces;

    vertex_t *vertices;
    unsigned int num_vertices;

    bool *edges;
    bool* getEdges(int i);

};
#endif
