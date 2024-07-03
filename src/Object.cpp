#include "Object.h"

Object::Object(std::vector<Vertex> me, Shader  shader, Texture tex, std::string n)
{
    name = n;
    texture = tex;
    Object::mesh = me;
    init(shader);
}

void Object::init(Shader & shader)
{
    VAO.Bind();
    VBO VBO(mesh);
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO.LinkAttrib(VBO, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));

    VAO.Unbind();
	VBO.Unbind();

    glm::mat4 temp = glm::mat4(1.0f);

    shader.activate();
    shader.setMat4("model", temp);
    shader.setMat4("scale", temp);
    shader.setMat4("translation", temp);
    shader.setMat4("spin", temp);

    texture.texUnit(shader, "tex0", 0);
}

void Object::SetParameters
(
    float orbit_radiou, 
    double orbit_ti, 
    float orbit_incl, 
    float angl, 
    double spin_ti, 
    float scal, 
    float thet, 
    float alph, 
    float spi
)
{
    orbit_radious = orbit_radiou;
    double orbit_int = orbit_ti;
    if (orbit_ti != 0.0f)
    {
        orbit_int = (2.0f * 3.141f)/(orbit_ti * 365 * 24 * 60 * 60 * 144);
    }

    orbit_interval = orbit_int;
    default_orbit_interval = orbit_int;

    orbit_inclination = orbit_incl;

    angle = angl;

    double spin_int = spin_ti;
    if (spin_ti != 0.0f)
    {
        spin_int =  (360)/(spin_ti * 24 * 60 * 60 * 144);
    }

    spin_interval = spin_int;
    default_spin_interval = spin_int;

    scale = scal;
    alpha = alph;
    spin = spi;
    theta = thet;
}

void Object::Draw(Shader& shader)
{
    texture.Bind();
    VAO.Bind();

    glDrawArrays(GL_TRIANGLES, 0, mesh.size());

    VAO.Unbind();
    texture.Unbind();
}

void Object::UpdatePositionMatrix(Shader& shader, glm::vec3 middle)
{
    // kalkulacje orbity
    float x = orbit_radious * cos(theta);
    float y = tan(glm::radians(orbit_inclination));
    float z = orbit_radious * sin(theta);
    
    float deltaX = z * cos(alpha) - x * sin(alpha);
    float deltaY = y * cos(alpha);
    float deltaZ = x * cos(alpha) + z * sin(alpha);

    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 rotation = glm::vec3(deltaX, deltaY, deltaZ);
    glm::mat4 trans = glm::translate(model, rotation);

    location = rotation;

    // pochylenie rownika
    glm::mat4 rot = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));

    model = trans * rot;
    alpha += orbit_interval;
    shader.setMat4("model", model);

    // rotacja dzien/noc
    glm::mat4 spinmat = glm::mat4(1.0f);
    spin += spin_interval;
    spinmat = glm::rotate(spinmat, glm::radians(spin), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.setMat4("spin", spinmat); 

    // zmiana skali
    glm::mat4 sc = glm::mat4(1.0f);
    sc = glm::scale(sc, glm::vec3(scale, scale, scale));
    shader.setMat4("scale", sc);

    // potencjalna zmiana srodka orbity
    glm::mat4 translation = glm::mat4(1.0f);
    translation = glm::translate(translation, middle);
    shader.setMat4("translation", translation);
}

glm::vec3 Object::GetLocation()
{
    return glm::vec3(location.x, location.y, location.z);
}

const char* Object::GetName()
{
    return name.c_str();
}

void Object::Delete()
{
    VAO.Delete();
}
