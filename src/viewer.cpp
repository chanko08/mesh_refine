#include <vector>
#include <GL/glut.h>
#include <GL/glu.h>
#include "viewer.h"
#include "obj.h"
#include "quaternion.h"

#include <iostream>
using namespace std;

Viewer::Viewer(){
    cam_pos = 4;
    mouse_start_x = 0;
    mouse_start_y = 0;

    mouse_end_x = 0;
    mouse_end_y = 0;

    mouse_old_x = 0;
    mouse_old_y = 0;

    pitch = 0;
    old_pitch = 0;

    yaw = 0;
    old_yaw = 0;
}

Viewer::~Viewer(){}

void Viewer::init(char *fname, bool lines){
    obj = new ObjFile(fname);
    drawLines = lines;

    computeDepth();
    computeCenter();

    glClearColor(1,1,1,1);
    glEnable(GL_DEPTH_TEST);

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
}

void Viewer::resize(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (1.0 * width) / height, 0.1, 20);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void Viewer::display(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    vector<float> cam(3,0);
    cam[0] = cam_pos;

    vector<float> y_axis(3,0);
    y_axis[1] = 1;

    vector<float> z_axis(3,0);
    z_axis[2] = 1;

    cam = rotatePoint(cam, y_axis, pitch);
    cam = rotatePoint(cam, z_axis, yaw);

    vector<float> up(3,0);
    up[1] = 1;
    up = rotatePoint(up, y_axis, pitch);
    up = rotatePoint(up, z_axis, yaw);
    


    gluLookAt(cam[0], cam[1], cam[2], 0, 0, 0, up[0], up[1], up[2]);



    glTranslatef(-center[0], -center[1], -center[2]);
    glColor3f(1,0,0);
    for(unsigned int i = 0; i < obj->numFaces(); i++){
        vector<vector<float> > verts = obj->getFaceVertices(i);
        GLenum begin = getBeginParam(verts.size());
        
        //draw the shape with a filled color
        glColor3f(1,0,0);
        glBegin(begin);
        {
            vector<vector<float> >::iterator it;
            for(it = verts.begin(); it != verts.end(); it++){
                vector<float> v = *it;
                glVertex3f(v[0], v[1], v[2]);
            }
            glEnd();
        }

        if(drawLines){
            //draw the shape with an outline
            glPolygonMode(GL_FRONT, GL_LINE);
            glDepthFunc(GL_LEQUAL);
            glColor3f(0,0,0);
            glBegin(begin);
            {    
                vector<vector<float> >::iterator it;
                for(it = verts.begin(); it != verts.end(); it++){
                    vector<float> v = *it;
                    glVertex3f(v[0], v[1], v[2]);
                }
            }
            glEnd();
            glPolygonMode(GL_FRONT,GL_FILL);
            glDepthFunc(GL_LESS);
        }

    }
    
    glutSwapBuffers();
}

//mouse click
void Viewer::mouse(int button, int state, int x, int y){
    //for mouse click
    if(button == 3){
        cam_pos -= 0.1f;
        glutPostRedisplay();
        return;
    }
    else if(button == 4){
        cam_pos += 0.1f;
        glutPostRedisplay();
        return;
    }



    //for left click
    int pressed = 0;
    if(state == pressed){
        mouse_start_x = x;
        mouse_start_y = y; 
    }
    else{
        mouse_end_x = x;
        mouse_end_y = y;

        saveAngles();
    }

    glutPostRedisplay();
}

//mouse motion
void Viewer::mouse(int x, int y){
    mouse_end_x = x;
    mouse_end_y = y;
    changeAngles();
    glutPostRedisplay();
}

void Viewer::changeAngles(){
    if(mouse_old_x == mouse_end_x && mouse_old_y == mouse_end_y){
        return;
    }

    int dx = mouse_end_x - mouse_start_x;
    int dy = mouse_end_y - mouse_start_y;

    pitch = (old_pitch - dx) % 360;
    yaw = (old_yaw - dy) % 360;

    if(pitch < 0)
        pitch += 360;

    if(yaw < 0)
        yaw += 360;

    mouse_old_x = mouse_end_x;
    mouse_old_y = mouse_end_y;
}

void Viewer::saveAngles(){
    changeAngles();
    old_pitch = pitch;
    old_yaw = yaw;
}


GLenum Viewer::getBeginParam(unsigned int i){
    if(i == 3){
        return GL_TRIANGLES;
    }
    else if(i == 4){
        return GL_QUADS;
    }
    return GL_POLYGON;
}


void Viewer::computeDepth(void){
    float m = 0;
    for(unsigned int i = 0; i < obj->numVertices(); i++){
        vector<float> v = obj->getVertex(i);

        if(v[0] > m)
            m = v[0];
        if(v[1] > m)
            m = v[1];
        if(v[2] > m)
            m = v[2];
    }


    depth = m;
    cam_pos = depth + 4;
}


void Viewer::computeCenter(void){
    center.push_back(0);
    center.push_back(0);
    center.push_back(0);

    unsigned int size = obj->numVertices();
    for(unsigned int i = 0; i < size; i++){
        vector<float> v = obj->getVertex(i);
        center[0] += v[0];
        center[1] += v[1];
        center[1] += v[2];
    }


    center[0] /= (float) size;
    center[1] /= (float) size;
    center[2] /= (float) size;

}
