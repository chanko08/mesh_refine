#ifndef __MESH_H
#define __MESH_H

typedef int face_t[3];
typedef float vertex_t[3];

class Mesh {
    public:
    Mesh(char *fname);
    ~Mesh();


    void save(char *fname);
    unsigned int numFaces();
    unsigned int numVertices();

    face_t *faces;
    vertex_t *vertices;

    bool* getEdges(int i);


    private:
    unsigned int num_vertices;
    unsigned int num_faces;

    bool *edges;

};
#endif
