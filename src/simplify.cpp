#include <vector>
#include <fstream>
#include "obj.h"
#include "simplify.h"
#include "mesh.h"
using namespace std;

Simplify::Simplify(){};
Simplify::~Simplify(){
    delete mesh;
};

void Simplify::load(char *fname){
    mesh = new Mesh(fname);
}

void Simplify::save(char *fname){
   mesh->save(fname);
} 
