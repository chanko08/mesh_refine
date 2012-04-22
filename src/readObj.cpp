#include <iostream>
#include <cstdlib>
#include "obj.h"


using namespace std;
static void usage(void){
    cout << "Usage: obj [OPTIONS] FILE" << endl;
    cout << "Outputs Wavefron OBJ graphics file in a more human readable format" << endl;
    cout << "Options:" << endl;
    cout << "    -p    Re-output OBJ file into another file" << endl;
    exit(1);
}

int main(int argc, char **argv){
    if(argc != 2 && argc != 4){
        usage();
    } 

    char *file = argv[argc - 1];
    ObjFile obj(file);


    {
        cout << "face" << endl;
        vector<int> face = obj.getFace(0);
        vector<int>::iterator it;
        for(it = face.begin(); it != face.end(); it++){
            cout << *it << endl;
        }
    }


    {

        cout << "vector" << endl;
        vector<float> vertex = obj.getVertex(0);
        vector<float>::iterator it;
        for(it = vertex.begin(); it != vertex.end(); it++){
            cout << *it << endl; 
        }
    }


    {
        cout << "face vertices" << endl;
        vector<vector<float> > verts = obj.getFaceVertices(0);
        vector<vector<float> >::iterator it;
        for(it = verts.begin(); it != verts.end(); it++){
            vector<float>::iterator it2;
            cout << "\tvertex:" << endl;
            for(it2 = (*it).begin(); it2 != (*it).end(); it2++){
                cout << "\t" << *it2 << endl;
            }
        }
    
    }
}
