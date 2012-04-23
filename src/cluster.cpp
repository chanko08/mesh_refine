#include "cluster.h"

Cluster::Cluster(float i, float j, float k, float rad, unsigned int ind){
    m_i = i;
    m_j = j;
    m_k = k;
    m_rad = rad;
    m_ind = ind;
}

bool Cluster::contains(float i, float j, float k){
    if(i > m_i + m_rad || i < m_i - m_rad)
        return false;

    if(j > m_j + m_rad || j < m_j - m_rad)
        return false;

    if(k > m_k + m_rad || k < m_k - m_rad)
        return false;

    return true;
}


void Cluster::add(unsigned int i){
    contained.push_back(i);
}
