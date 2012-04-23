#ifndef __CLUSTER_H
#define __CLUSTER_H
#include <vector>
class Cluster {
    public:
    Cluster(float i, float j, float k, float rad, unsigned int ind);
    bool contains(float i, float j, float k);
    void add(unsigned int i);

    std::vector<unsigned int> contained;

    float m_i;
    float m_j;
    float m_k;
    float m_rad;
    unsigned int m_ind;
};
#endif
