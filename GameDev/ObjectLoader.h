#ifndef OBJECTLOADER_H_INCLUDED
#define OBJECTLOADER_H_INCLUDED
#ifndef GL_UNSIGNED_SHORT_5_6_5
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <map>
#include "CollisionPlane.h"


    /** face coordinate **/
    struct coordinate{
        float x, y, z;
        coordinate(float a, float b, float c);
    };

    /** Object Face triangle vs. quadrangle **/
    struct face{
        int faceNumber;
        bool isQuad;
        int faces[4];
        int textureCoord[4];
        int materialId;
        // triangle face
        face(int fn, int f1, int f2, int f3, int texCoord_1, int texCoord_2, int texCoord_3, int matId);
        // quad face
        face(int fn, int f1, int f2, int f3, int f4, int texCoord_1, int texCoord_2, int texCoord_3, int texCoord_4, int matId);

    };
    /**
        As per blender .mtl file (only a few used for now)
        http://people.sc.fsu.edu/~jburkardt/data/mtl/mtl.html
    **/
    struct material{
        std::string name;
        float alpha; //material transparency
        float ns; // shininess of the material
        float ni; //intensity of the material
        float diffuse[3];
        float ambient[3];
        float specular[3];
        int illum;
        int textureId;
        material(const char* na, float alp, float n_s , float n_i,
                 float* diff, float* amb, float* spec,
                 int il, int texId);
    };
    /** U V Coordinates **/
    struct textureCoord{
        float u, v;
        textureCoord(float a, float b);
    };
class ObjectLoader{

    public:
        ObjectLoader();
        ~ObjectLoader();
        int load(const std::string& filename, std::vector<CollisionPlane>*collPlane);


    private:
        std::vector<std::string*> coord;
        std::vector<coordinate*> vertex;
        std::vector<face*> faces;
        std::vector<coordinate*> normals;
        std::vector<unsigned int> texture;
        std::vector<unsigned int> lists;
        std::vector<material*> materials;
        std::vector<textureCoord*> textureCoordinate;
        std::vector<coordinate*> vertexNormals;
        bool isMaterial;
        bool isNormals;
        bool isTexture;
        bool isVertexNormal;
        std::vector<std::string> loadedTextures;
        std::vector<int> loadedTexturesNum;
        std::ofstream out;

        // helpers
        unsigned int loadTexture(const char* filename);
        void cleanUp();
        void smoothNormals();


};



#endif // OBJECTLOADER_H_INCLUDED
