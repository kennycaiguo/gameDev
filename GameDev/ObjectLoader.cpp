#include "ObjectLoader.h"

/** Structure constructors...
    (see ObjectComponents.cpp)
**/
// coords
coordinate::coordinate(float a, float b, float c){
    x = a;
    y = b;
    z = c;
}
//triangle face
face::face(int fn, int f1, int f2, int f3, int texCoord_1, int texCoord_2, int texCoord_3, int matId){
    faceNumber = fn;
    isQuad = false;
    faces[0] = f1;
    faces[1] = f2;
    faces[2] = f3;
    textureCoord[0] = texCoord_1;
    textureCoord[1] = texCoord_2;
    textureCoord[2] = texCoord_3;
    materialId = matId;
}
// quad face
face::face(int fn, int f1, int f2, int f3, int f4, int texCoord_1, int texCoord_2, int texCoord_3, int texCoord_4, int matId){
    faceNumber = fn;
    isQuad = true;
    faces[0] = f1;
    faces[1] = f2;
    faces[2] = f3;
    faces[3] = f4;
    textureCoord[0] = texCoord_1;
    textureCoord[1] = texCoord_2;
    textureCoord[2] = texCoord_3;
    textureCoord[3] = texCoord_4;
    materialId = matId;
}
// material
material::material(const char* na, float alp, float n_s , float n_i, float* diff, float* amb, float* spec, int il, int texId){
        name = na;
        alpha = alp;
        ns = n_s;
        ni = n_i;
        diffuse[0] = diff[0];
        diffuse[1] = diff[1];
        diffuse[2] = diff[2];
        ambient[0] = amb[0];
        ambient[1] = amb[1];
        ambient[2] = amb[2];
        specular[0] = spec[0];
        specular[1] = spec[1];
        specular[2] = spec[2];
        illum = il;
        textureId = texId;
}
// texture coordinates
textureCoord::textureCoord(float a, float b){
    u = a;
    v = b;
}
// default constructor
ObjectLoader::ObjectLoader(){
    //type flags
    isMaterial = false;
    isNormals = false;
    isTexture = false;
    isVertexNormal = false;
	out.open("objreport.txt");
}
// destructor
ObjectLoader::~ObjectLoader(){
	for(std::vector<unsigned int>::const_iterator it = texture.begin(); it != texture.end(); it++){
		glDeleteTextures(1,&(*it));
	}
	for(std::vector<unsigned int>::const_iterator it=lists.begin();it!=lists.end();it++){
		glDeleteLists(*it,1);
	}
}
// load
int ObjectLoader::load(const std::string& filename, std::vector<CollisionPlane>* collPlane){

    //type flags
    isMaterial = false;
    isNormals = false;
    isTexture = false;
    isVertexNormal = false;
    // open file
    std::ifstream in(filename.c_str());
    if(!in.is_open()){
        out << "Could not open file->" << filename << std::endl;
        return -1;
    }
    // get the relative path
    std::string path = filename.substr(0, ((filename.find_last_of('/') + 1 != std::string::npos) ? (filename.find_last_of('/') + 1) : 0));
    out << filename << std::endl;
    char buf[256]; // holds (up to 256 characters in length) found in each line of the file
    int curMatId = 0;
    bool isCollisionMaterial = false;
    int z = 0;
    int h = -1;
    // parse through ot he eof
    while(!in.eof()){
        in.getline(buf, 256);
        coord.push_back(new std::string(buf));
    }
    out << "coord size :" << coord.size() << std::endl;
    for(int i = 0; i < coord.size(); i++){
        if((*coord[i])[0] == '#'){ // check for a comment in the first position of the line
            continue;
        }else if((*coord[i])[0] == 'v' && (*coord[i])[1] == ' '){ // check to see if vertices
            float tmpx, tmpy, tmpz;
            sscanf(coord[i]->c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz);
            vertex.push_back(new coordinate(tmpx, tmpy, tmpz));
            out << "v " << tmpx << " " << tmpy << " " << tmpz << std::endl;
        }else if((*coord[i])[0] == 'v' && (*coord[i])[1] == 'n'){ // check to see if vert normal
            float tmpx, tmpy, tmpz;
            sscanf(coord[i]->c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
            normals.push_back(new coordinate(tmpx, tmpy, tmpz));
            out << "vn " << tmpx << " " << tmpy << " " << tmpz << std::endl;
        }else if((*coord[i])[0] == 'f'){ // check to see if face
            int a, b, c, d, e;
            if(isCollisionMaterial && collPlane != NULL){ // collsion plane
                //sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
                sscanf(coord[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b, &e, &b);
                collPlane->push_back(CollisionPlane(normals[b-1]->x, normals[b-1]->y, normals[b-1]->z,
                                                    vertex[a-1]->x, vertex[a-1]->y, vertex[a-1]->z,
                                                    vertex[c-1]->x, vertex[c-1]->y, vertex[c-1]->z,
                                                    vertex[d-1]->x, vertex[d-1]->y, vertex[d-1]->z,
                                                    vertex[e-1]->x, vertex[e-1]->y, vertex[e-1]->z));
            } else{ // not a collison plane
                if(count(coord[i]->begin(), coord[i]->end(), ' ') == 4){ // four elements in a line....is this the face descriptor
                    if(coord[i]->find("//") != std::string::npos){ // does ->// exist int the line...ie...nothing in slot two
                        sscanf(coord[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b, &e, &b);
                        faces.push_back(new face(b, a, c, d, e, 0, 0, 0, 0, curMatId));
                    }else if(coord[i]->find("/") != std::string::npos){ // something in slot two
                        int t[4];
                         sscanf(coord[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &a, &t[0], &b, &c, &t[1], &b, &d, &t[2], &b, &e, &t[3], &b);
                         out << t[0] << " " << t[1] << " " << t[2] << " " << t[3] << " "
                             << a << " " << b << " " << c << " " << d << " " << e << std::endl;
                         faces.push_back(new face(b, a, c, d, e, t[0], t[1], t[2], t[3], curMatId));
                    }else{
                        sscanf(coord[i]->c_str(), "f %d %d %d %d", &a, &b, &c, &d);
                        faces.push_back(new face(-1, a, b, c, d, 0, 0, 0, 0, curMatId));
                    }
                }else{ // only three elements in a line...is this a face descriptor
                    if(coord[i]->find("//") != std::string::npos){ // does ->// exist int the line...ie...nothing in slot two
                        sscanf(coord[i]->c_str(), "f %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b);
                        faces.push_back(new face(b, a, c, d, 0, 0, 0, curMatId));
                    }else if(coord[i]->find("/") != std::string::npos){ // something in slot two
                        int t[3];
                         sscanf(coord[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &a, &t[0], &b, &c, &t[1], &b, &d, &t[2], &b);
                         faces.push_back(new face(b, a, c, d, t[0], t[1], t[2], curMatId));
                    }else{
                        sscanf(coord[i]->c_str(), "f %d %d %d", &a, &b, &c);
                        faces.push_back(new face(-1, a, b, c, 0, 0, 0, curMatId));
                    }
                }
            }
        }else if((*coord[i])[0] == 'u' && (*coord[i])[1] == 's' && (*coord[i])[2] == 'e'){
            char tmp[200];
            sscanf(coord[i]->c_str(), "usemtl %s", tmp);
            out << "tmp: " << tmp << std::endl;
            if(strcmp(tmp, "collision") == 0){
                isCollisionMaterial = true;
            }else{
                isCollisionMaterial = false;
                for(int j = 0; j < materials.size(); j++){
                    out << "materials size: " << materials.size() << std::endl;
                    out << "tmp name: " << tmp << std::endl;
                    out << "materials name: " << materials[j]->name.c_str() << std::endl;
                    if(strcmp(materials[j]->name.c_str(), tmp) == 0){
                        curMatId = j;
                        out << "current material id=" << j << std::endl;
                        break;
                    }
                }
            }

        }else if((*coord[i])[0] == 'm' && (*coord[i])[1] == 't' && (*coord[i])[2] == 'l' && (*coord[i])[3] == 'l'){
            char filename1[200];
            sscanf(coord[i]->c_str(), "mtllib %s", filename1);
            std::string filename2 = path + filename1; // concatenate file name with path
            std::ifstream mtlin(filename2.c_str()); // open material file
            if(!mtlin.is_open()){
                out << "Could not open the material file " << filename2 << std::endl;
                cleanUp();
                return -1;
            }
            isMaterial = true;
            std::vector<std::string> tmp;
            char c[200];
            while(!mtlin.eof()){
                mtlin.getline(c, 200);
                tmp.push_back(c);
            }
            char name[200];
            char tmpFileName[200];
            float amb[3], dif[3], spec[3], alpha, ns, ni;
            int illum;
            unsigned int texId;
            bool isMat = false;
            strcpy(tmpFileName, "\0");
            for(int k=  0; k < tmp.size(); k++){
                if(tmp[k][0] == '#')
                    continue;
                if(tmp[k][0] == 'n' && tmp[k][1] == 'e' && tmp[k][2] == 'w'){
                    if(isMat){
                        if(strcmp(tmpFileName, "\0") != 0 && strcmp(tmpFileName, "collision") != 0){ // is this material collision
                            materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, texId));
                            out << "tmpFileName " << tmpFileName << std::endl;
                            strcpy(tmpFileName, "\0");
                        }else{
                            out << "tmpFileName " << tmpFileName << std::endl;
                            materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, -1));
                        }
                    }
                    isMat = false;
                    sscanf(tmp[k].c_str(), "newmtl %s", name);
                    out << "newmtl " << name << std::endl;
                }else if(tmp[k][0] == 'N' && tmp[k][1] == 's'){
                    sscanf(tmp[k].c_str(), "Ns %f", &ns);
                    isMat = true;
                }else if(tmp[k][0] == 'K' && tmp[k][1] == 'a'){
                    sscanf(tmp[k].c_str(), "Ka %f %f %f", &amb[0], &amb[1], &amb[2]);
                    isMat = true;
                }else if(tmp[k][0] == 'K' && tmp[k][1] == 'd'){
                    sscanf(tmp[k].c_str(), "Kd %f %f %f", &dif[0], &dif[1], &dif[2]);
                    isMat = true;
                }else if(tmp[k][0] == 'K' && tmp[k][1] == 's'){
                    sscanf(tmp[k].c_str(), "Ks %f %f %f", &spec[0], &spec[1], &spec[2]);
                    isMat = true;
                }else if(tmp[k][0] == 'N' && tmp[k][1] == 'i'){
                    sscanf(tmp[k].c_str(), "Ni %f", &ni);
                    isMat = true;
                }else if(tmp[k][0] == 'd' && tmp[k][1] == ' '){
                    sscanf(tmp[k].c_str(), "d %f", &alpha);
                    isMat = true;
                }else if(tmp[k][0] == 'i' && tmp[k][1] == 'l'){
                    sscanf(tmp[k].c_str(), "illum %d", &illum);
                    isMat = true;
                }else if(tmp[k][0] == 'm' && tmp[k][1] == 'a'){
                    sscanf(tmp[k].c_str(), "map_Kd %s", tmpFileName);
                    bool loaded = 0;
                    out << "Opening image " << tmpFileName << std::endl;
                    std::string filename2 = path + tmpFileName;
                    for(int m = 0; m < loadedTextures.size(); m++){
                        if(loadedTextures[m] == filename2){
                            out << "loading " << filename2 << std::endl;
                            texId = loadedTexturesNum[m];
                            loaded = 1;
                            break;
                        }
                    }
                    if(loaded == 0)
                        texId = loadTexture(filename2.c_str());
                    isMat = true;
                }
            }
            if(isMat){
                if(strcmp(tmpFileName, "\0") != 0){
                    out << "tmpFileName " << tmpFileName << std::endl;
                    out << "name " << name << std::endl;
                    out << "alpha " << alpha << std::endl;
                    out << "ns " << ns << std::endl;
                    out << "ni " << ni << std::endl;
                    out << "dif " << dif << std::endl;
                    out << "amb " << amb << std::endl;
                    out << "spec " << spec << std::endl;
                    out << "illum " << illum << std::endl;
                    out << "textId " << texId << std::endl;
                    materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, texId));
                }else{
                   out << "tmpFileName " << tmpFileName << std::endl;
                   out << "name " << name << std::endl;
                    out << "alpha " << alpha << std::endl;
                    out << "ns " << ns << std::endl;
                    out << "ni " << ni << std::endl;
                    out << "dif " << dif << std::endl;
                    out << "amb " << amb << std::endl;
                    out << "spec " << spec << std::endl;
                    out << "illum " << illum << std::endl;
                    out << "textId " << texId << std::endl;
                   materials.push_back(new material(name, alpha, ns, ni, dif, amb, spec, illum, -1));
                }
            }
        }else if((*coord[i])[0] == 'v' && (*coord[i])[1] == 't'){
            float u, v;
            sscanf(coord[i]->c_str(), "vt %f %f", &u, &v);
            textureCoordinate.push_back(new textureCoord(u, 1-v));
            isTexture = true;
        }
    }
    if(materials.size() == 0){
       isMaterial = false;
    }else{
        isMaterial = true;
    }
    out << "numVertex :" << vertex.size() << " " << normals.size() << " " << faces.size() << " " << materials.size() << std::endl;
    // draw
    if(isVertexNormal){
        smoothNormals();
    }
    int num;
    num = glGenLists(1);
    glNewList(num, GL_COMPILE);
    int last = -1;
    for(int i = 0; i < faces.size(); i++){
        if(last != faces[i]->materialId && isMaterial){
            out << "material id :" << faces[i]->materialId << std::endl;
            float diff[] = {materials[faces[i]->materialId]->diffuse[0],
                               materials[faces[i]->materialId]->diffuse[1],
                               materials[faces[i]->materialId]->diffuse[2], 1.0};
            float amb[] = {materials[faces[i]->materialId]->ambient[0],
                               materials[faces[i]->materialId]->ambient[1],
                               materials[faces[i]->materialId]->ambient[2], 1.0};
            float spec[] = {materials[faces[i]->materialId]->specular[0],
                               materials[faces[i]->materialId]->specular[1],
                               materials[faces[i]->materialId]->specular[2], 1.0};
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
			glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
			glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
			glMaterialf(GL_FRONT, GL_SHININESS, materials[faces[i]->materialId]->ns);
            glColor3f(diff[0], diff[1], diff[2]);
			last=faces[i]->materialId;
			out << "1....." << std::endl;
            if(materials[faces[i]->materialId]->textureId == -1)
				glDisable(GL_TEXTURE_2D);
			else{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, materials[faces[i]->materialId]->textureId);
			}
        }
        if(faces[i]->textureCoord[0] == 0){
            isTexture = false;
        }else{
             isTexture = true;
        }
        out << "2....." << std::endl;
        isNormals = false;
        if(faces[i]->isQuad){
            glBegin(GL_QUADS);
                out << "faces[i]->textureCoord[0]-1 " << faces[i]->faceNumber - 1 << std::endl;
                if(isNormals)
                    glNormal3f(normals[faces[i]->faceNumber-1]->x, normals[faces[i]->faceNumber-1]->y, normals[faces[i]->faceNumber-1]->z);

                if(isTexture && materials[faces[i]->materialId]->textureId != -1)
                    glTexCoord2f(textureCoordinate[faces[i]->textureCoord[0]-1]->u,textureCoordinate[faces[i]->textureCoord[0]-1]->v);

                if(isVertexNormal)
                    glNormal3f(vertexNormals[faces[i]->faces[0]-1]->x,vertexNormals[faces[i]->faces[0]-1]->y,vertexNormals[faces[i]->faces[0]-1]->z);

				out << "faces[i]->faces[0]-1: " << faces[i]->faces[0]-1 << " " << faces[i]->faces[1]-1 << " " << faces[i]->faces[2]-1 << " " << faces[i]->faces[3]-1 << " "  << std::endl;
				glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);

				if(isTexture && materials[faces[i]->materialId]->textureId != -1)
					glTexCoord2f(textureCoordinate[faces[i]->textureCoord[1]-1]->u,textureCoordinate[faces[i]->textureCoord[1]-1]->v);

				if(isVertexNormal)
					glNormal3f(vertexNormals[faces[i]->faces[1]-1]->x,vertexNormals[faces[i]->faces[1]-1]->y,vertexNormals[faces[i]->faces[1]-1]->z);

				glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);

				if(isTexture && materials[faces[i]->materialId]->textureId != -1)
					glTexCoord2f(textureCoordinate[faces[i]->textureCoord[2]-1]->u,textureCoordinate[faces[i]->textureCoord[2]-1]->v);

				if(isVertexNormal)
					glNormal3f(vertexNormals[faces[i]->faces[2]-1]->x,vertexNormals[faces[i]->faces[2]-1]->y,vertexNormals[faces[i]->faces[2]-1]->z);

				glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);

				if(isTexture && materials[faces[i]->materialId]->textureId != -1)
					glTexCoord2f(textureCoordinate[faces[i]->textureCoord[3]-1]->u,textureCoordinate[faces[i]->textureCoord[3]-1]->v);

				if(isVertexNormal)
					glNormal3f(vertexNormals[faces[i]->faces[3]-1]->x,vertexNormals[faces[i]->faces[3]-1]->y,vertexNormals[faces[i]->faces[3]-1]->z);

				glVertex3f(vertex[faces[i]->faces[3]-1]->x,vertex[faces[i]->faces[3]-1]->y,vertex[faces[i]->faces[3]-1]->z);
			glEnd();

        }else{
			glBegin(GL_TRIANGLES);
				if(isNormals)
					glNormal3f(normals[faces[i]->faceNumber-1]->x,normals[faces[i]->faceNumber-1]->y,normals[faces[i]->faceNumber-1]->z);

				if(isTexture && materials[faces[i]->materialId]->textureId != -1)
					glTexCoord2f(textureCoordinate[faces[i]->textureCoord[0]-1]->u,textureCoordinate[faces[i]->textureCoord[0]-1]->v);

				if(isVertexNormal)
					glNormal3f(vertexNormals[faces[i]->faces[0]-1]->x,vertexNormals[faces[i]->faces[0]-1]->y,vertexNormals[faces[i]->faces[0]-1]->z);


				glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);

				if(isTexture && materials[faces[i]->materialId]->textureId != -1)
					glTexCoord2f(textureCoordinate[faces[i]->textureCoord[1]-1]->u,textureCoordinate[faces[i]->textureCoord[1]-1]->v);


				if(isVertexNormal)
					glNormal3f(vertexNormals[faces[i]->faces[1]-1]->x,vertexNormals[faces[i]->faces[1]-1]->y,vertexNormals[faces[i]->faces[1]-1]->z);

				glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);


				if(isTexture && materials[faces[i]->materialId]->textureId != -1)
					glTexCoord2f(textureCoordinate[faces[i]->textureCoord[2]-1]->u,textureCoordinate[faces[i]->textureCoord[2]-1]->v);


				if(isVertexNormal)
					glNormal3f(vertexNormals[faces[i]->faces[2]-1]->x,vertexNormals[faces[i]->faces[2]-1]->y,vertexNormals[faces[i]->faces[2]-1]->z);

				glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
			glEnd();
		}
    }
    glEndList();
    out << "3....." << std::endl;
    cleanUp();
    lists.push_back(num);
    return num;
}

void ObjectLoader::cleanUp(){
	for(int i=0; i < coord.size(); i++)
		delete coord[i];
	for(int i=0; i < faces.size(); i++)
		delete faces[i];
	for(int i=0; i < normals.size(); i++)
		delete normals[i];
	for(int i=0; i < vertex.size(); i++)
		delete vertex[i];
	for(int i=0; i < materials.size(); i++)
		delete materials[i];
	for(int i=0; i < textureCoordinate.size(); i++)
		delete textureCoordinate[i];
	for(int i=0; i < vertexNormals.size(); i++)
		delete vertexNormals[i];
	coord.clear();
	faces.clear();
	normals.clear();
	vertex.clear();
	materials.clear();
	textureCoordinate.clear();
	vertexNormals.clear();
}
/*
unsigned int ObjectLoader::loadTexture(const char* filename)
{
	unsigned int num;
	glGenTextures(1,&num);
	SDL_Surface* img=SDL_LoadBMP(filename);
	glBindTexture(GL_TEXTURE_2D,num);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img->w,img->h,0,GL_RGB,GL_UNSIGNED_SHORT_5_6_5,img->pixels);
	glTexEnvi(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	SDL_FreeSurface(img);
	texture.push_back(num);
	loadedTextures.push_back(filename);
	loadedTexturesNum.push_back(num);
	return num;
}
*/
unsigned int ObjectLoader::loadTexture(const char* filename){
	SDL_Surface* img = IMG_Load(filename);
	out << "filename :" << filename << std::endl;
	SDL_PixelFormat form = {NULL,32,4,0,0,0,0,8,8,8,8,0xff000000,0x00ff0000,0x0000ff00,0x000000ff,0,255};
	SDL_Surface* img2 = SDL_ConvertSurface(img, &form, SDL_SWSURFACE);
	unsigned int num;
	glGenTextures(1,&num);
	glBindTexture(GL_TEXTURE_2D,num);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img2->w,img2->h,0,GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,img2->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	std::cout << glGetError() << std::endl;
	SDL_FreeSurface(img);
	SDL_FreeSurface(img2);
	texture.push_back(num);
	loadedTextures.push_back(filename);
	loadedTexturesNum.push_back(num);
	return num;
}

void ObjectLoader::smoothNormals(){
    for(int i=1;i<vertex.size()+1;i++){
        float vecX=0.0,vecY=0.0,vecZ=0.0;
        int num=0;
        for(int j=0;j<faces.size();j++){
            if(faces[j]->faces[0]==i || faces[j]->faces[1]==i || faces[j]->faces[2]==i || faces[j]->faces[3]==i){
                vecX+=normals[faces[j]->faceNumber-1]->x;
                vecY+=normals[faces[j]->faceNumber-1]->y;
                vecZ+=normals[faces[j]->faceNumber-1]->z;
                num++;
            }
        }
        if(num){
            vecX/=num;
            vecY/=num;
            vecZ/=num;
        }
        float d=sqrt(vecX*vecX+vecY*vecY+vecZ*vecZ);
        if(d){
            vecX/=d;
            vecY/=d;
            vecZ/=d;
        }
        vertexNormals.push_back(new coordinate(vecX,vecY,vecZ));
	}
}









