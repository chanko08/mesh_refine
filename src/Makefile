CC=g++

FLAGS=-Wall -g -Wconversion -Wextra
LIBS=-lGLEW -lglut -lX11 -lGL -lGLU

#the obj program source, headers and executable name
readObjSource = readObj.cpp obj.cpp
readObjHeader = obj.h
readObjExec = obj

viewerSource = viewer.cpp obj.cpp quaternion.cpp runViewer.cpp
viewerHeader = viewer.h quaternion.h
viewerExec = viewer

simplifySource = simplify.cpp obj.cpp runSimplify.cpp mesh.cpp
simplifyHeader = obj.h simplify.h mesh.h
simplifyExec = simplify


executables = $(readObjExec) $(viewerExec) $(simplifyExec)

all: $(executables)

clean:
	rm -f $(executables)


obj: $(readObjSource) $(readObjHeader)
	$(CC) -o $(readObjExec) $(FLAGS) $(readObjSource)

viewer: $(viewerSource) $(viewerHeader)
	$(CC) -o $(viewerExec) $(FLAGS) $(LIBS) $(viewerSource)

simplify: $(simplifySource) $(simplifyHeader)
	$(CC) -o $(simplifyExec) $(FLAGS) $(simplifySource)
