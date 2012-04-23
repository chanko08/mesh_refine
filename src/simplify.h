#ifndef __SIMPLIFY_H
#define __SIMPLIFY_H
#include <vector>
#include "mesh.h"
#include "cluster.h"

class Simplify {
    public:
    Simplify(float rad);
    ~Simplify();

    void load(char *fname);
    void save(char *fname);
    void cluster();
    private:
        Mesh *mesh;
        std::vector<unsigned int> *verts;
        std::vector<Cluster> clusters;
        float *max_distances;
        float *max_thetas;
        float radius;


        void computeDistances();
        bool checkCluster(unsigned int index);
        unsigned int vertexToCluster(unsigned int);

    struct SimplifyComparator {
        SimplifyComparator(Simplify *simp) : s(simp) {};
        bool operator()(unsigned int a, unsigned int b);
        float computeDistance(unsigned int a);
        float computeTheta(unsigned int a);
        Simplify *s;
    };


};
#endif
