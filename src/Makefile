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

executables = $(readObjExec) $(viewerExec)

all: obj viewer

clean:
	rm -f $(executables)


obj: $(readObjSource) $(readObjHeader)
	$(CC) -o $(readObjExec) $(FLAGS) $(readObjSource)

viewer: $(viewerSource) $(viewerHeader)
	$(CC) -o $(viewerExec) $(FLAGS) $(LIBS) $(viewerSource)
