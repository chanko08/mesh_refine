#include <vector>
#include <fstream>
#include "obj.h"
#include "mesh.h"
using namespace std;

Mesh::Mesh(char *fname){
    ObjFile obj(fname);
    
    //have to convert to an all triangle mesh
    num_faces = 0;
    for(unsigned int i = 0; i < obj.numFaces(); i++){
        vector<int> vertices = obj.getFace(i);
        num_faces += vertices.size() - 2;
    }


    //now we know exactly how many triangle faces there are, now allocate
    //space for them
    faces = new face_t[num_faces];
    int cur_face = 0;

    for(unsigned int i = 0; i < obj.numFaces(); i++){
        vector<int> vertices = obj.getFace(i);
        for(unsigned int j = 2; j < vertices.size(); j++){
            faces[cur_face][0] = vertices[0];
            faces[cur_face][1] = vertices[j - 1];
            faces[cur_face][2] = vertices[j];

            cur_face ++;
        }
    }


    //now load the vertices into the mesh
    num_vertices = obj.numVertices();
    vertices = new vertex_t[num_vertices];
    for(unsigned int i = 0; i < obj.numVertices(); i++){
        vector<float> vertex = obj.getVertex(i);
        vertices[i][0] = vertex[0];
        vertices[i][1] = vertex[1];
        vertices[i][2] = vertex[2];
    }


    //keep track of what vertices are incident to what vertices
    edges = new bool[num_vertices * num_vertices];
    for(unsigned int i = 0; i < num_faces; i++){
        edges[faces[i][0] * num_vertices + faces[i][1]] = true;
        edges[faces[i][0] * num_vertices + faces[i][2]] = true;
        
        edges[faces[i][1] * num_vertices + faces[i][0]] = true;
        edges[faces[i][1] * num_vertices + faces[i][2]] = true;
        
        edges[faces[i][2] * num_vertices + faces[i][1]] = true;
        edges[faces[i][2] * num_vertices + faces[i][0]] = true;
    }

}

Mesh::~Mesh(){
    delete [] faces;
    delete [] vertices;
    delete [] edges;
}

bool* Mesh::getEdges(int i){
    return &(edges[i * num_vertices]);
}

void Mesh::save(char *fname){
    ofstream file;
    file.open(fname);
    for(unsigned int i = 0; i < num_vertices; i++){
        file << "v " << vertices[i][0]  << " " << vertices[i][1] << " " << vertices[i][2] << "\n";
    }

    for(unsigned int i = 0; i < num_faces; i++){
        file << "f " << faces[i][0] + 1 << " " << faces[i][1] + 1 << " " << faces[i][2] + 1 << "\n"; 
    
    }

    file.close();
}
