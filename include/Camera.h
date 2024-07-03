
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.h"


// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  0.1f;
const float SENSITIVITY =  50.0f;
const float ZOOM        =  45.0f;



class Camera
{
public:
    // Atributy
    glm::vec3 Position;
    glm::vec3 Orientation;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Perspactive matrix
    glm::mat4 projView;

    // katy
    float Yaw;
    float Pitch;

    // Opcje
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    float min_view;
    float max_view;

    bool firstClick = true;
    bool Above_view = false;

    int SCR_WIDTH;
    int SCR_HEIGHT; 
       

    // constructor 
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float min = 0.1f, float max = 400.0f, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
        float yaw = YAW, float pitch = PITCH, int SCR_H = 800,  int SCR_W = 1000) : 

    Orientation(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        min_view = min;
        max_view = max;
        SCR_HEIGHT = SCR_H;
        SCR_WIDTH = SCR_W;
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        UpdateCameraVectors();
    }

    // aktualizacja widoku
    void UpdataCameraMatrix(Shader & shader)
    {
        // camera/view transformation
        glm::mat4 projection = glm::perspective(glm::radians(Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, min_view, max_view);
        glm::mat4 view = glm::lookAt(Position, Position + Orientation, Up);

        projView = projection * view;
        shader.setMat4("projView", projView);
    }

    // klawiatura
    void ProcessKeyboardInpit(GLFWwindow* window)
    {   
        // sprawdza czy nie jestesmy w trybie widoku z gory
        if (!Above_view)
        {
            float velocity = MovementSpeed;
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                Position += Orientation * velocity;
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                Position -= Orientation * velocity;
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
               Position -= glm::normalize(glm::cross(Orientation, Up)) * velocity;
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                Position += glm::normalize(glm::cross(Orientation, Up)) * velocity;
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
                Position += Up * velocity;
            if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
                Position -= Up *velocity;

            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                MovementSpeed  = 0.5f;
            else if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
                MovementSpeed = 0.1f;
        }
    }

    // myszka
    void ProcessMouseInput(GLFWwindow* window)
    {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT == GLFW_PRESS))
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            if (firstClick)
            {
                glfwSetCursorPos(window, (SCR_WIDTH / 2), (SCR_HEIGHT / 2));
                firstClick = false;
            }

            double mouseX;
		    double mouseY;

		    glfwGetCursorPos(window, &mouseX, &mouseY);


		    float rotX = MouseSensitivity * (float)(mouseY - (SCR_HEIGHT / 2)) / SCR_HEIGHT;
		    float rotY = MouseSensitivity * (float)(mouseX - (SCR_WIDTH / 2)) / SCR_WIDTH;

            // barrel roll prevention
		    glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));
		    if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(89.0f))
		    {
		    	Orientation = newOrientation;
		    }

		    Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		    glfwSetCursorPos(window, (SCR_WIDTH / 2), (SCR_HEIGHT / 2));
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            firstClick = true;
        }
    }

    // zimana zooma
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 89.0f)
            Zoom = 89.0f;
    }

    // aktualizacja vectorow
    void UpdateCameraVectors()
    {
        Orientation.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Orientation.y = sin(glm::radians(Pitch));
        Orientation.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

        Orientation = glm::normalize(Orientation);
        Right = glm::normalize(glm::cross(Orientation, WorldUp));
        Up    = glm::normalize(glm::cross(Right, Orientation));
    }
};
#endif

