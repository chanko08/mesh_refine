#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "obj.h"
#include "simplify.h"
#include "mesh.h"
#include "cluster.h"
using namespace std;

Simplify::Simplify(float r){
    radius = r;
};
Simplify::~Simplify(){
    delete mesh;
};

void Simplify::load(char *fname){
    mesh = new Mesh(fname);

    //sort the vectors based on the how good they are for 
    //mesh simplification
    verts = new vector<unsigned int>(mesh->numVertices(),0);
    max_distances = new float[mesh->numVertices()];
    max_thetas = new float[mesh->numVertices()];

    for(unsigned int i = 0; i < mesh->numVertices(); i++){
        (*verts)[i] = i;
        max_distances[i] = 0.0f;
        max_thetas[i] = 0.0f;
    }


    for(unsigned int i = 0; i < mesh->numVertices(); i++){
        bool *edges = mesh->getEdges(i);
        for(unsigned int j = 0; j < mesh->numVertices(); j++){
            if(edges[j] == false)
                continue;
            
            //get max distance
            float dot = mesh->vertices[i][0] * mesh->vertices[j][0]
                       + mesh->vertices[i][1] * mesh->vertices[j][1]
                       + mesh->vertices[i][2] * mesh->vertices[j][2];
            float dist = sqrt(dot);

            if(max_distances[i] < dist)
                max_distances[i] = dist;

            //get max theta angle
            float costheta = cos(acos(dot / dist) / 2);

            if(max_thetas[i] < costheta)
                max_thetas[i] = costheta;
        }
    }

    sort(verts->begin(), verts->end(), SimplifyComparator(this));
}

void Simplify::save(char *fname){
    ofstream file;
    file.open(fname);
    //first save the cluster vertices
    vector<Cluster>::iterator it;
    for(it = clusters.begin(); it != clusters.end(); it++){
        unsigned int i = it->m_ind;
        file << "v " 
             << mesh->vertices[i][0] << " " 
             << mesh->vertices[i][1] << " "
             << mesh->vertices[i][2] << endl; 
    }

    //no save the faces, converting the old vertices to the new clusters
    for(unsigned int i = 0; i < mesh->numFaces(); i++){
        file << "f "
             << vertexToCluster(mesh->faces[i][0]) + 1 << " " 
             << vertexToCluster(mesh->faces[i][1]) + 1 << " "
             << vertexToCluster(mesh->faces[i][2]) + 1 << endl; 
    }
    
    file.close();

    cout << "there are " << clusters.size() << " clusters" << endl;
    cout << (unsigned int) -1 << endl;
}


bool Simplify::checkCluster(unsigned int index){
    vector<Cluster>::iterator it;
    for(it = clusters.begin(); it != clusters.end(); it++){

        if(it->contains(mesh->vertices[index][0], mesh->vertices[index][1], mesh->vertices[index][2]))
            return true;
    }
    return false;
}



unsigned int Simplify::vertexToCluster(unsigned int index){
    vector<Cluster>::iterator it;
    unsigned int i = 0;
    for(it = clusters.begin(); it != clusters.end(); it++){

        if(it->contains(mesh->vertices[index][0], mesh->vertices[index][1], mesh->vertices[index][2])){            
            return i;
        }
        i++;
    }

    return -1;
}

void Simplify::cluster(){
    vector<unsigned int>::iterator it;
    for(it = verts->begin(); it != verts->end(); it++){
        unsigned int vector_index = *it;
        int inCluster = checkCluster(vector_index);
        //vertex in this cluster, so add it
        if(inCluster){
            continue;
        }

        //this vertex isn't in a cluster, so create a cluster for this vertex
        Cluster c(mesh->vertices[vector_index][0], mesh->vertices[vector_index][1], mesh->vertices[vector_index][2], radius, vector_index);
        clusters.push_back(c);
    }
}

bool Simplify::SimplifyComparator::operator()(unsigned int a, unsigned int b){
    float EPSILON = 0.0000001f;

    float a_dist = s->max_distances[a];
    float a_theta = s->max_thetas[a];

    float b_dist = s->max_distances[b];
    float b_theta = s->max_thetas[b];

    
    if(a_dist - b_dist < EPSILON)
        return a_theta < b_theta;

    return a_dist < b_dist;
}
