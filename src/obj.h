#ifndef __OBJFILE_H
#define __OBJFILE_H

#include <vector>
#include <string>
class ObjFile {
    public:
    ObjFile(char *fname);

    ~ObjFile(void);

    std::vector<int> getFace(int i);
    std::vector<float> getVertex(int i);
    std::vector<std::vector<float> > getFaceVertices(int i);


    unsigned int numFaces(void);
    unsigned int numVertices(void);

    static void saveToObj(char *fname, ObjFile obj);
    private:
    std::vector<std::vector<int> > faces;
    std::vector<std::vector<float> > vertices;


    void addVector(std::string vec);
    void addFace(std::string face);
};

#endif
