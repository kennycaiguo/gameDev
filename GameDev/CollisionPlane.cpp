#include "CollisionPlane.h"

CollisionPlane::CollisionPlane(float norm_x, float norm_y, float norm_z,
                               float vert1_x, float vert1_y, float vert1_z,
                               float vert2_x, float vert2_y, float vert2_z,
                               float vert3_x, float vert3_y, float vert3_z,
                               float vert4_x, float vert4_y, float vert4_z){
    // intialize the normal
    this->normal.changeVectorComponents(norm_x, norm_y, norm_z);
    // intialize vert 1
    this->planeVertex[0].changeVectorComponents(vert1_x, vert1_y, vert1_z);
    // intialize vert 2
    this->planeVertex[1].changeVectorComponents(vert2_x, vert2_y, vert2_z);
    // intialize vert 3
    this->planeVertex[2].changeVectorComponents(vert3_x, vert3_y, vert3_z);
    // intialize vert 4
    this->planeVertex[3].changeVectorComponents(vert4_x, vert4_y, vert4_z);

}

CollisionPlane::CollisionPlane(Vector3d normal, Vector3d vert1, Vector3d vert2, Vector3d vert3, Vector3d vert4){
        // intialize the normal
    this->normal.changeVectorComponents(normal.getX(), normal.getY(), normal.getZ());
    // intialize vert 1
    this->planeVertex[0].changeVectorComponents(vert1.getX(), vert1.getY(), vert1.getZ());
    // intialize vert 2
    this->planeVertex[1].changeVectorComponents(vert2.getX(), vert2.getY(), vert2.getZ());
    // intialize vert 3
    this->planeVertex[2].changeVectorComponents(vert3.getX(), vert3.getY(), vert3.getZ());
    // intialize vert 4
    this->planeVertex[3].changeVectorComponents(vert4.getX(), vert4.getY(), vert4.getZ());
}

CollisionPlane::~CollisionPlane(){
    std::cout << "CollisionPlane destroyed" << std::endl;
}
// Used to see if the normal is a valid normal and != 0
bool CollisionPlane::isPlaneNormalValid(){
    return (this->getPlaneNormal().getX() != 0 &&
            this->getPlaneNormal().getY() != 0 &&
            this->getPlaneNormal().getZ() != 0);
}

/** Accessor Methods **/
// get vertex 1 of this plane
Vector3d CollisionPlane::getPlaneVertex1(){
    return this->planeVertex[0];
}
// get vertex 2 of this plane
Vector3d CollisionPlane::getPlaneVertex2(){
    return this->planeVertex[1];
}

// get vertex 3 of this plane
Vector3d CollisionPlane::getPlaneVertex3(){
    return this->planeVertex[2];
}

// get vertex 4 of this plane
Vector3d CollisionPlane::getPlaneVertex4(){
    return this->planeVertex[3];
}
// returns this plane normal
Vector3d CollisionPlane::getPlaneNormal(){
    return this->normal;
}


