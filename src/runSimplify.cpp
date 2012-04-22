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
    cout << "    -r NUM  Refines the mesh NUM times. Defaults to 10" << endl;
    exit(1);
}


string refine("-r");
int main(int argc, char **argv){
    if(argc != 3 && argc != 5)
        usage();

    if(argc == 5 && refine.compare(argv[1]))
       usage();


    int mesh_refinement = 10;
    if(argc == 5){
       stringstream s(argv[2]);
       s >> mesh_refinement;
    }

    if(mesh_refinement < 1)
        usage();

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

    Mesh m(infile);
}
