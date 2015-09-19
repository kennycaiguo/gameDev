################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Camera.cpp \
../Collision.cpp \
../CollisionPlane.cpp \
../CollisionSphere.cpp \
../Constants.cpp \
../Controller.cpp \
../Game.cpp \
../GameDriver.cpp \
../Keyboard.cpp \
../Level.cpp \
../MainMenu.cpp \
../Math3d.cpp \
../Menu.cpp \
../ObjCollisionTestDriver.cpp \
../Object.cpp \
../ObjectComponents.cpp \
../ObjectLoader.cpp \
../Physics3d.cpp \
../Player.cpp \
../Point3d.cpp \
../SingleObject.cpp \
../Skybox.cpp \
../Text.cpp \
../Vector3d.cpp \
../main_1.cpp 

OBJ_SRCS += \
../arena_floor.obj \
../crate.obj \
../crate001test.obj \
../test.obj 

OBJS += \
./Camera.o \
./Collision.o \
./CollisionPlane.o \
./CollisionSphere.o \
./Constants.o \
./Controller.o \
./Game.o \
./GameDriver.o \
./Keyboard.o \
./Level.o \
./MainMenu.o \
./Math3d.o \
./Menu.o \
./ObjCollisionTestDriver.o \
./Object.o \
./ObjectComponents.o \
./ObjectLoader.o \
./Physics3d.o \
./Player.o \
./Point3d.o \
./SingleObject.o \
./Skybox.o \
./Text.o \
./Vector3d.o \
./main_1.o 

CPP_DEPS += \
./Camera.d \
./Collision.d \
./CollisionPlane.d \
./CollisionSphere.d \
./Constants.d \
./Controller.d \
./Game.d \
./GameDriver.d \
./Keyboard.d \
./Level.d \
./MainMenu.d \
./Math3d.d \
./Menu.d \
./ObjCollisionTestDriver.d \
./Object.d \
./ObjectComponents.d \
./ObjectLoader.d \
./Physics3d.d \
./Player.d \
./Point3d.d \
./SingleObject.d \
./Skybox.d \
./Text.d \
./Vector3d.d \
./main_1.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


