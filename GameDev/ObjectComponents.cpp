
namespace ObjComp{

    /** face coordinate **/
    struct coordinate{
        float x, y, z;
        coordinate(float x, float y, float z);
    };

    /** Object Face triangle vs. quadrangle **/
    struct face{
        int faceNumber;
        bool isQuad;
        int faces[4];
        int textureCoord[4];
        int materialId;
        // triangle face
        face(int faceNumber, int face_1, int face_2, int face_3,
             int textureCoord_1, int textureCoord_2, int textureCoord_3, int materialId);
        // quad face
        face(int faceNumber, int face_1, int face_2, int face_3, int face_4,
             int textureCoord_1, int textureCoord_2, int textureCoord_3, int textureCoord_4, int materialId);

    };
    /**
        As per blender .mtl file (only a few used for now)
        http://people.sc.fsu.edu/~jburkardt/data/mtl/mtl.html
    **/
 /*   struct material{
        //aString name;
        //const char* name;
        float alpha; //material transparency
        float ns; // shininess of the material
        float ni; //intensity of the material
        float diffuse[3];
        float ambient[3];
        float specular[3];
        int illum;
        int textureId;
        material(const char* name, float alpha, float ns , float ni,
                 float* diffuse, float* ambient, float* specular,
                 int illum, int textureId);
    };*/
    /** U V Coordinates **/
    struct textureCoord{
        float u, v;
        textureCoord(float u, float v);
    };

}
