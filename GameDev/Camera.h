#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include "Vector3d.h"
#include "Point3d.h"
#include "Math3d.h"

class Camera{

    public:
        // constructors/destructor
        Camera();
        Camera(const Vector3d& location);
        Camera(const Vector3d& location, const float& yaw, const float& pitch);
        Camera(const Vector3d& location, const float& yaw, const float& pitch, const float& speed, const float& mousespeed);
        ~Camera();
        // member functions
        void keyboardControl();
        void joystickControl(SDL_Joystick* joystick);
        void update();
        Vector3d getCameraVector() const;
        void setCameraLocation(const Vector3d& newPosition);
        Vector3d getCameraLocation() const;
        float getCameraYaw() const;
        float getCameraPitch() const;
        void lookAt(const float& yaw, const float& pitch);
        void mouseIn();
        void mouseOut();
        bool isMouseIn();
        void lockCamera();
        void moveCamera(const float& direction);
        void moveCamera(const float& direction, float velocity);
        void moveCameraUp(const float& direction);
        void setCameraSpeed(float speed);
        void setMouseCameraSpeed(float speed, float ms);

    private:
        Vector3d location;
        float cameraYaw;
        float cameraPitch;
        float cameraSpeed;
        float mouseSpeed;
        bool mi;
};



#endif // CAMERA_H_INCLUDED
