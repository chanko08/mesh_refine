CC=g++

FLAGS=-Wall -g -Wconversion -Wextra
LIBS=-lGLEW -lglut -lX11 -lGL -lGLU

OUTDIR=../bin

#the obj program source, headers and executable name
readObjSource = readObj.cpp obj.cpp
readObjHeader = obj.h
readObjExec = obj

viewerSource = viewer.cpp obj.cpp quaternion.cpp runViewer.cpp
viewerHeader = viewer.h quaternion.h
viewerExec = viewer

simplifySource = simplify.cpp obj.cpp runSimplify.cpp mesh.cpp cluster.cpp
simplifyHeader = obj.h simplify.h mesh.h cluster.h
simplifyExec = simplify


executables = $(readObjExec) $(viewerExec) $(simplifyExec)

all: $(executables)

clean:
	rm -f $(OUTDIR)/$(readObjExec) $(OUTDIR)/$(viewerExec) $(OUTDIR)/$(simplifyExec)


obj: $(readObjSource) $(readObjHeader)
	$(CC) -o $(OUTDIR)/$(readObjExec) $(FLAGS) $(readObjSource)

viewer: $(viewerSource) $(viewerHeader)
	$(CC) -o $(OUTDIR)/$(viewerExec) $(FLAGS) $(LIBS) $(viewerSource)

simplify: $(simplifySource) $(simplifyHeader)
	$(CC) -o $(OUTDIR)/$(simplifyExec) $(FLAGS) $(simplifySource)
