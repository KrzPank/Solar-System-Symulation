#ifndef MYGUI_H
#define MYGUI_H

#include "Camera.h"
#include "Object.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <string>
#include <iostream>

class MyGui
{
public:
    // przechowuje predkosc symulacji
    float timeRate = 1.0f;
    
    MyGui(); 

    void Render(Camera& camera, Object planets[]);

    void UpdateIntervals(Object objects[], int size);

    void Setup();

    void FrameInfo();

    void Delete();
};

#endif
