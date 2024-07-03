#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include <algorithm>

#include "VAO.h"
#include "VBO.h"
#include "Camera.h"
#include "Texture.h"


class Object
{
public:
    std::vector<Vertex> mesh;

    VAO VAO;

    std::string name;
    
    float theta;
    float alpha;
    float spin;

    float angle;

    float scale;

    float orbit_inclination;
    float orbit_radious;

    double orbit_interval;
    double default_orbit_interval;

    double spin_interval;
    double default_spin_interval;

    glm::vec3 location;

    Texture texture;

    Object(std::vector<Vertex> me, Shader shader, Texture tex, std::string n);

    void init(Shader & shader);

    void UpdatePositionMatrix(Shader& shader, glm::vec3 middle = glm::vec3(0.0f, 0.0f, 0.0f));

    void SetParameters
    (
        float orbit_radiou, 
        double orbit_ti, 
        float orbit_incl, 
        float angl, 
        double spin_ti, 
        float scal = 1.0f, 
        float thet = 5.0f, 
        float alph = 0.0f, 
        float spi = 0.0f
    );

    void Draw(Shader& shader);

    glm::vec3 GetLocation();

    void Delete();

    const char* GetName();
};

#endif