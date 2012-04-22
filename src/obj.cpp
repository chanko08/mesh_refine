#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

#include "obj.h"
using namespace std;

ObjFile::ObjFile(char *fname){
    ifstream file;
    file.open(fname);

    string line;
    while(getline(file,line)){
        if(line.size() == 0)
            continue;

        switch(line[0]){
            case 'v':
                addVector(line);
            break;

            case 'f':
                addFace(line);
            break;
        }
    }


}


ObjFile::~ObjFile(void){

}

void ObjFile::addVector(string vec){
    stringstream str(vec);
    char type;
    str >> type;
    
    vector<float> vertex;
    float val;

    str >> skipws >> val;
    vertex.push_back(val);

    str >> skipws  >> val;
    vertex.push_back(val);

    str >> skipws >> val;
    vertex.push_back(val);

    vertices.push_back(vertex);
}

void ObjFile::addFace(string face_str){
    stringstream str(face_str);
    char type;
    str >> type;

    vector<int> face;
    int val;

    while(!str.eof()){
        str >> val;
        face.push_back(val - 1);
    }

    faces.push_back(face);
}


vector<int> ObjFile::getFace(int i){
    assert((unsigned int)i < faces.size());
    return faces[i];
}

vector<float> ObjFile::getVertex(int i){
    assert((unsigned int)i < vertices.size());

    return vertices[i];
}

vector<vector<float> > ObjFile::getFaceVertices(int i){
    vector<int> face = getFace(i);

    vector<vector<float> > verts;
    
    vector<int>::iterator it;
    for(it = face.begin(); it != face.end(); it++){
        verts.push_back(getVertex(*it));
    }

    return verts;
}


unsigned int ObjFile::numFaces(void){
    return faces.size();
}

unsigned int ObjFile::numVertices(void){
    return vertices.size();
}


void ObjFile::saveToObj(char *fname, ObjFile obj){
    ofstream file;
    file.open(fname);

    {
        vector<vector<float> >::iterator it;
        for(it = obj.vertices.begin(); it != obj.vertices.end(); it++){
            vector<float>::iterator it2;
            file << "v";
            for(it2 = it->begin(); it2 != it->end(); it2++){
                file << " " <<  *it2;
            }
            file << endl;
        }
    }


    
    {
        vector<vector<int> >::iterator it;
        for(it = obj.faces.begin(); it != obj.faces.end(); it++){
            vector<int>::iterator it2;
            file << "f";
            for(it2 = it->begin(); it2 != it->end(); it2++){
                file << " " << (*it2) + 1;
            } 
            file << endl;
        }
    }
    file.close();
}
