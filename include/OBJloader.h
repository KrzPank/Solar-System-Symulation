#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VAO.h"
#include "VBO.h"
#include "Camera.h"
#include "Texture.h"


std::vector<Vertex> OBJLoader(const char * OBJFile)
{
    std::vector<Vertex> vertices;


    std::vector<glm::vec3> vertexPositoins;
    std::vector<glm::vec2> TexturePositions;
    std::vector<glm::vec3> vertexNormals;


    std::vector<GLuint> verticeID;
    std::vector<GLuint> TextureID;
    std::vector<GLuint> NormalID;
    

    std::stringstream ss;
    std::ifstream in_file(OBJFile);
    std::string line = "";
    std::string prefix;

    glm::vec3 temp_vec3;
    glm::vec2 temp_vec2;
    GLuint temp_GLuint;

    if (!in_file.is_open())
    {
        std::cout << OBJFile << "  "<< errno  << "  Zly file path\n";
        throw"ERROR FILE DID'T LOAD";
    }

    while(std::getline(in_file, line))
    {   
        ss.clear();
        ss.str(line);
        ss >> prefix;

        // wczytanie pozycji do vectorow
        if ( prefix == "v" )
        {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            vertexPositoins.push_back(temp_vec3);
        } 
        else if ( prefix == "vt" )
        {
            ss >> temp_vec2.x >> temp_vec2.y;
            TexturePositions.push_back(temp_vec2);
        } 
        else if ( prefix == "vn")
        {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            vertexNormals.push_back(temp_vec3);
        }
        else if ( prefix == "f")
        {
            int counter = 0;
            //zapisanie kolejnosci vertexow, textur i norlanych
            while (ss >> temp_GLuint)
            {
                if (counter == 0) verticeID.push_back(temp_GLuint);
                else if (counter == 1) TextureID.push_back(temp_GLuint);
                else if (counter == 2) NormalID.push_back(temp_GLuint);

                if (ss.peek() == '/')
                {
                    counter++;
                    ss.ignore(1, '/');
                }
                else if (ss.peek() == ' ')
                {
                    counter++;
                    ss.ignore(1, ' ');
                }
                if (counter > 2) counter=0;
            }
        }
    }
    // resize
    vertices.resize(verticeID.size(), Vertex());

    // zapisanie danych w dobraj kolejnosci
    for (int i=0; i<verticeID.size(); i++)
    {
        vertices[i].Position = vertexPositoins[verticeID[i]-1];
        vertices[i].TexUV = TexturePositions[TextureID[i]-1];
        vertices[i].Normal = vertexNormals[NormalID[i]-1];
    }

    return vertices;
}
