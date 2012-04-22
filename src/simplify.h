#ifndef __SIMPLIFY_H
#define __SIMPLIFY_H
#include "mesh.h"

class Simplify {
    public:
    Simplify();
    ~Simplify();

    void load(char *fname);
    void save(char *fname);

    private:
        Mesh *mesh;


};
#endif
