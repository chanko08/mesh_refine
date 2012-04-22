#include <iostream>
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

void myKeyboard(unsigned char key, int x, int y){
    viewer.keyboard(key, x, y);
}

void myResize(int width, int height){
    viewer.resize(width, height);
}

void usage(void){
    cout << "usage: viewer FILE" << endl;
    exit(1);
}

int main(int argc, char** argv) 
{
    if(argc != 2)
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
    glutKeyboardFunc(myKeyboard);
    glutMotionFunc(myMouseMotion);
    glutReshapeFunc(myResize);

    viewer.init(argv[1]);

    glutMainLoop(); //go into a perpetual loop
    
}
