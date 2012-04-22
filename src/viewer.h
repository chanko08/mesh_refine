#include <GL/glut.h>
#include "obj.h"

class Viewer {
    public:
    Viewer(void);
    ~Viewer(void);

    void init(char *objfilename);
    void display(void); 

    //mouse click and motion
    void mouse(int button, int state, int x, int y);
    void mouse(int x, int y);


    void keyboard(unsigned char key, int x, int y);

    void resize(int width, int height);

    private:
    ObjFile *obj;

    GLenum getBeginParam(unsigned int i);
    void changeAngles();
    void saveAngles();

    float cam_pos;

    int mouse_start_x;
    int mouse_start_y;

    int mouse_end_x;
    int mouse_end_y;

    int mouse_old_x;
    int mouse_old_y;

    int pitch;
    int old_pitch;

    int yaw;
    int old_yaw;

};
