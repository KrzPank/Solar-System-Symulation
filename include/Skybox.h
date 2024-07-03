#ifndef SKYBOX_CLASS_H
#define SKYBOX_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VAO.h"
#include "VBO.h"
#include "Camera.h"
#include "Texture.h"
#include "Shader.h"

const float skyboxVertices[] =
    {
    	//   Coordynaty
    	-1.0f, -1.0f,  1.0f,//        7--------6
    	 1.0f, -1.0f,  1.0f,//       /|       /|
    	 1.0f, -1.0f, -1.0f,//      4--------5 |
    	-1.0f, -1.0f, -1.0f,//      | |      | |
    	-1.0f,  1.0f,  1.0f,//      | 3------|-2
    	 1.0f,  1.0f,  1.0f,//      |/       |/
    	 1.0f,  1.0f, -1.0f,//      0--------1
    	-1.0f,  1.0f, -1.0f
    };

// kolejnosc wiezcholkow
const unsigned int skyboxIndices[] =
    {
    	1, 5, 6, 6, 2, 1,
        0, 3, 7, 7, 4, 0,
    	4, 7, 6, 6, 5, 4,
    	0, 1, 2, 2, 3, 0,
    	0, 4, 5, 5, 1, 0,
    	3, 2, 6, 6, 7, 3
    };


class Skybox
{
public:
    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    unsigned int cubemapTexture;

    Skybox(Shader &skyboxshader);
    void Draw(Shader &skyboxshader, Camera &camera);
};

#endif