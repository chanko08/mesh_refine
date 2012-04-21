import sys
sys.path.append("../src")

from PyQt4 import QtCore
from PyQt4 import QtGui
from PyQt4 import QtOpenGL
from OpenGL import GLU
from OpenGL.GL import *

from obj import load_obj
from quaternion import rotate_pt

class ViewerWidget(QtOpenGL.QGLWidget):
    def __init__(self, ofile, parent = None):
        super(QtGui.QWidget, self).__init__(parent)
        self.setFixedWidth(600)

        self.faces, self.vertices = load_obj(ofile)

        self.cam_pos = 5
 
        self.mouse_start = (0,0)
        self.mouse_end = (0,0)
        self.mouse_old = (0,0)

        self.pitch = 0
        self.old_pitch = 0

        self.yaw = 0
        self.old_yaw = 0
   

    def initializeGL(self):
        glClearColor(1,1,1,1)
        glEnable(GL_DEPTH_TEST)
        
        glCullFace(GL_BACK)
        glEnable(GL_CULL_FACE)
        
		
    def resizeGL(self, width, height):
        if height == 0: height = 1
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity();
        GLU.gluPerspective(45, (1.0 * width) / height, 0.1, 20)
        glViewport(0, 0, width, height)

        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()  


    def paintGL(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glLoadIdentity()
       
        cam = rotate_pt([self.cam_pos, 0, 0], [0,1,0], self.pitch)
        cam = rotate_pt(cam, [0,0,1], self.yaw)

        up = rotate_pt([0,1,0],[0,1,0],self.pitch)
        up = rotate_pt(up, [0,0,1], self.yaw)
        GLU.gluLookAt(cam[0],cam[1],cam[2], 0,0,0, up[0],up[1],up[2])


        for f in self.faces:
            glColor(1, 0, 0)
            p = self.begin_param(f)

            glBegin(p)
            map(glVertex, f)
            glEnd()

            glPolygonMode(GL_FRONT, GL_LINE)
            glDepthFunc(GL_LEQUAL)
            glColor(0,0,0)
            
            glBegin(p)
            map(glVertex, f)
            glEnd()
            glPolygonMode(GL_FRONT,GL_FILL)
            glDepthFunc(GL_LESS)


    def begin_param(self,face):
        l = len(face)
        if l == 3:
            return GL_TRIANGLES
        elif l == 4:
            return GL_QUADS
        
        return GL_POLYGON

    def save_angles(self):
        self.change_angles()
        self.old_pitch = self.pitch
        self.old_yaw = self.yaw

        return self.pitch, self.yaw
    
    def change_angles(self):
        if self.mouse_old == self.mouse_end:
            return

        startx,endx = self.mouse_start[0], self.mouse_end[0]
        starty,endy = self.mouse_start[1], self.mouse_end[1]

        dx = endx - startx
        dy = endy - starty

        self.pitch = (self.old_pitch - dx) % 360
        self.yaw = (self.old_yaw - dy) % 360

        self.mouse_old = self.mouse_end
        return self.pitch, self.yaw


    def mousePressEvent(self, e):
        p = e.pos()
        self.mouse_start = p.x(), p.y()


    def mouseReleaseEvent(self, e):
        p = e.pos()
        self.mouse_end = p.x(), p.y()
        
        self.save_angles()

        self.updateGL()

    
    def mouseMoveEvent(self, e):
        p = e.pos()
        self.mouse_end = p.x(), p.y()
        self.change_angles()
        self.updateGL()


    def wheelEvent(self, e):
        self.cam_pos += e.delta() / 100.0
        self.cam_pos = min(self.cam_pos, 20)
        self.cam_pos = max(self.cam_pos, 0.1)
        self.updateGL()


class MainWindow(QtGui.QMainWindow):
    def __init__(self, ofile):
        QtGui.QMainWindow.__init__(self)

        self.resize(800, 600)
        self.setWindowTitle('Mesh Simplification Project (atbechan)')
        
        self.viewer = ViewerWidget(ofile, self)
        self.setCentralWidget(self.viewer)

        self.initActions()
        
        
    def initActions(self):
        self.exitAction = QtGui.QAction('Quit', self)
        self.exitAction.setStatusTip('Exit application')
        self.connect(self.exitAction, QtCore.SIGNAL('triggered()'), self.close)





if __name__ == "__main__":
    if len(sys.argv) != 2:
        print """usage: viewer FILE"""

        sys.exit(1)

    obj_file = sys.argv[1]

    app = QtGui.QApplication(sys.argv)
    win = MainWindow(obj_file)
    win.show()
    sys.exit(app.exec_())
