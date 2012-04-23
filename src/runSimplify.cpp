#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include "simplify.h"
#include "obj.h"
using namespace std;


void usage(void){
    cout << "usage: simplify [OPTIONS] INPUT_FILE OUTPUT_FILE" << endl;
    cout << "Runs vertex clustering on the input mesh and outputs the refined mesh" << endl;
    cout << "Options" << endl;
    cout << "    -r NUM  Refines the mesh with cell radius NUM. Defaults to 0.001" << endl;
    exit(1);
}


string refine("-r");
int main(int argc, char **argv){
    if(argc != 3 && argc != 5)
        usage();

    if(argc == 5 && refine.compare(argv[1]))
       usage();


    float mesh_refinement = 0.001f;
    if(argc == 5){
       stringstream s(argv[2]);
       s >> mesh_refinement;
    }

    char *infile;
    char *outfile;
    if(argc == 3){
        infile = argv[1];
        outfile = argv[2];
    }
    else{
        infile = argv[3];
        outfile = argv[4];
    }

    Simplify simplify(mesh_refinement);
    simplify.load(infile);
    simplify.cluster();
    simplify.save(outfile);
}
