#include <iostream>
#include <string>
#include <cstdlib>
#include <GL/glut.h>
#include <GL/glu.h>
#include "viewer.h"
using namespace std;

Viewer viewer;

void myDisplay(void){
   viewer.display(); 
}

void myMouse(int button, int state, int x, int y){
    viewer.mouse(button, state, x, y);
}

void myMouseMotion(int x, int y){
    viewer.mouse(x, y);

}

void myResize(int width, int height){
    viewer.resize(width, height);
}

void usage(void){
    cout << "usage: viewer [OPTIONS] FILE" << endl;
    cout << "Displays the inputted Wavefront OBJ file" << endl;
    cout << "Options:" << endl;
    cout << "    -nl     Displays mesh with no lines being drawn to distinguish faces" << endl;
    exit(1);
}


string noLines("-nl");
int main(int argc, char** argv) 
{
    if(argc != 2 && argc != 3)
       usage();

    if(argc == 3 && noLines.compare(argv[1]))
       usage(); 


    const int screenWidth = 800;
    const int screenHeight = 600;
    glutInit(&argc, argv); //initialize the toolkit
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  //set display mode
    glutInitWindowSize(screenWidth, screenHeight); //set window size
    glutInitWindowPosition(150, 150); //set window position on screen
    glutCreateWindow("Mesh Simplification (atbechan)"); //open the screen window  

    //register the callback function
    glutDisplayFunc(myDisplay); 
    glutMouseFunc(myMouse); 
    //glutKeyboardFunc(myKeyboard);
    glutMotionFunc(myMouseMotion);
    glutReshapeFunc(myResize);
    
    if(argc == 2)
        viewer.init(argv[1], true);
    else
        viewer.init(argv[2], false);

    glutMainLoop(); //go into a perpetual loop
    
}
