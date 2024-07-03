#include "MyGui.h"

#include "OBJloader.h"

#include "Object.h"
#include "Skybox.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

unsigned int SCR_WIDTH = 1000;
unsigned int SCR_HEIGHT = 800;

const int samples = 4;


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 25.0f));

int main(int argc, char** args)
{
    glfwInit();
    // opengl version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // multisampling
    glfwWindowHint(GLFW_SAMPLES, samples);

    // core profile mowi ze urzywamy nowszych funkcji
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // tworzenie okna
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Solar system symulation", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Wczytanie glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // wczytanie modeli
    std::string moddiv = "resources/models/";
    std::vector<Vertex> Sub1Sphere = OBJLoader((moddiv+"Sub1sphere.obj").c_str());
    std::vector<Vertex> QuadedSphere = OBJLoader((moddiv+"Quadshpere.obj").c_str());
    std::vector<Vertex> SatRing = OBJLoader((moddiv+"saturn_ring.obj").c_str());

    // tworzenie shaderow
    std::string shdiv = "resources/shaders/";
    Shader sunshader((shdiv+"sun_shader.vert").c_str(), (shdiv+"sun_shader.frag").c_str());
    Shader ourShader((shdiv+"default.vert").c_str(), (shdiv+"default.frag").c_str());
    Shader skyboxShader((shdiv+"skybox.vert").c_str(), (shdiv+"skybox.frag").c_str());


    // usawienie swiatla
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);

    ourShader.activate();
    ourShader.setVec4("lightColor", lightColor);
    ourShader.setVec3("lightPos", lightPos);

    // skybox
    Skybox skybox(skyboxShader);

    // wczytanie textur i tworzenie obiektow
    std::string imgdiv = "resources/images/";
    Texture planetstex[] 
    {
        Texture ((imgdiv+"mercury.jpg").c_str(), 0, GL_RGB),
        Texture ((imgdiv+"venus.jpg").c_str(), 0, GL_RGB),
        Texture ((imgdiv+"earth2.png").c_str(), 0, GL_RGB),
        Texture ((imgdiv+"mars.jpg").c_str(), 0, GL_RGB),
        Texture ((imgdiv+"jupiter.jpg").c_str(), 0, GL_RGB),
        Texture ((imgdiv+"saturn.jpg").c_str(), 0, GL_RGB),
        Texture ((imgdiv+"uranus.jpg").c_str(), 0, GL_RGB),
        Texture ((imgdiv+"neptune.jpg").c_str(), 0, GL_RGB)//,
        // honorable mention pluto Texture ((imgdiv+"plutomap2k,jpg").c_str(), 0, GL_RGB)        
    };

    Object Planets[]
    {
        Object (Sub1Sphere, ourShader, planetstex[0], "Mercury"),
        Object (Sub1Sphere, ourShader, planetstex[1], "Wenus"),
        Object (Sub1Sphere, ourShader, planetstex[2], "Ziemia"),
        Object (Sub1Sphere, ourShader, planetstex[3], "Mars"),
        Object (Sub1Sphere, ourShader, planetstex[4], "Jowisz"),
        Object (Sub1Sphere, ourShader, planetstex[5], "Saturn"),
        Object (Sub1Sphere, ourShader, planetstex[6], "Uran"),
        Object (Sub1Sphere, ourShader, planetstex[7], "Neptun")//,
        // pluto Object (Sub1Sphere, ourShader, planetstex[8], "Pluto")
    };


    Texture elseTex[]
    {
        Texture ((imgdiv+"sun_diff.png").c_str(), 0, GL_RGB),
        Texture ((imgdiv+"moonmap4k.png").c_str(), 0, GL_RGB),
        Texture ((imgdiv+"saturn_ring.png").c_str(), 0, GL_RGBA)
    };


    Object elseObj[]
    {
        Object (QuadedSphere, sunshader, elseTex[0], "Slonce"),
        Object (Sub1Sphere, ourShader, elseTex[1], "Ksiezyc"),
        Object (SatRing, ourShader, elseTex[2], "Pierscien Saturna")
    };

    // ustawienie parametrow, 
    // wartosci rzeczywiste 
    /*                        o_r     o_ti   o_inc  axis   sp_ti    scale
    Planets[0].SetParameters(35.79f, 0.2408, 3.38f, 0.03f, 58.645f, 0.3825f);
    Planets[1].SetParameters(40.82, 0.6152f, 3.86f, 2.64f, 243.05f, 0.7489f);
    Planets[2].SetParameters(49.959f, 1.0f, 7.25f, 23.44f, 1.0f, 0.8f);
    Planets[3].SetParameters(57.793f, 1.88f, 5.65f, 25.19f, 1.05f, 0.536f);
    Planets[4].SetParameters(112.84f, 11.86f, 6.09f, 3.13f, 0.4f , 11.2f);
    Planets[5].SetParameters(177.6725f, 29.44f, 5.51f, 26.73f, 0.443f, 9.44f);
    Planets[6].SetParameters(287.09f, 84.07f, 6.48f, 82.23f, 0.7183f, 4.0f);
    Planets[7].SetParameters(449.8f, 164.88f, 6.43f, 28.32f, 0.671f, 3.88f);


    elseObj[0].SetParameters(0.0f, 0.0f, 0.0f, 7.25f, 250.38f, 30.0f);
    elseObj[1].SetParameters(3.0f, 0.0748f, 5.145f, 6.68f, 27.322f, 0.1f);
    elseObj[2].SetParameters(0.0f, 0.0f, 5.51f, 26.73f, 0.443f, 9.44f);
*/

    // warotsci dla lepszej wizualizacji
    Planets[0].SetParameters(9.0f, 0.6f, 3.38f, 0.03f, 18.0f, 0.4f, 1.0f);
    Planets[1].SetParameters(14.8f, 0.8f, 3.86f, 2.64f, 24.0f, 0.75f, 2.4f);
    Planets[2].SetParameters(21.0f, 1.3f, 7.25f, 23.44f, 5.0f, 0.8f, 4.1f);
    Planets[3].SetParameters(28.0f, 2.4f, 5.65f, 25.19f, 5.25f, 0.6f, 0.3f);
    Planets[4].SetParameters(42.0f, 3.2f, 6.09f, 3.13f, 4.4f , 3.2f, 5.0f);
    Planets[5].SetParameters(64.0f, 3.9f, 5.51f, 26.73f, 3.0f, 2.4f, 1.6f);
    Planets[6].SetParameters(82.0f, 4.5f, 6.48f, 82.23f, 2.0f, 1.6f, 3.7f);
    Planets[7].SetParameters(90.0f, 5.0f, 6.43f, 28.32f, 1.f, 1.1f, 4.4f);

    elseObj[0].SetParameters(0.0f, 0.0f, 0.0f, 7.25f, 500.0f, 5.0f);
    elseObj[1].SetParameters(3.0f, 0.0748f, 5.145f, 6.68f, 27.322f, 0.3f);
    elseObj[2].SetParameters(0.0f, 0.0f, 5.51f, 26.73f, 0.443f, 3.4f);


    // rysowanie counterclockwise, optymalizacja
    glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

    // multisampling
    glEnable(GL_MULTISAMPLE);

    //Gui
    MyGui Gui;

    // FPS counter
    double prevTime = 0.0;
    double diff;
    int counter = 0;

    while (!glfwWindowShouldClose(window))
    {
        // Fps counter
        diff = glfwGetTime() - prevTime;
        counter++;
        
        if ( diff >= 1.0f/10.0f )
        {
            std::string FPS = std::to_string((1.0/diff)* counter);
            std::string newTitle = "Solar system symulation "+FPS;
            glfwSetWindowTitle(window, newTitle.c_str());
            
            prevTime = glfwGetTime();
            counter = 0;
        }
        
        // View port i wyczyszczenie bufferow
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        // imgui frame info 
        Gui.FrameInfo();

        // input process
        ImGui::GetCurrentContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        // wczytanie myszki jak jest poza oknem menu
        if (!io.WantCaptureMouse)
        {
            camera.ProcessMouseInput(window);
        }
        camera.ProcessKeyboardInpit(window);


        // Rendering skybox
        skybox.Draw(skyboxShader, camera);
 
        // Rendering slonca 
        sunshader.activate();
        camera.UpdataCameraMatrix(sunshader);
        elseObj[0].UpdatePositionMatrix(sunshader);
        elseObj[0].Draw(sunshader);


        // Rendering planet i reszty
        ourShader.activate();
        camera.UpdataCameraMatrix(ourShader);
        for(int i = 0; i < 8; i++)
        {
            Planets[i].UpdatePositionMatrix(ourShader);
            Planets[i].Draw(ourShader);
        }

        elseObj[1].UpdatePositionMatrix(ourShader, Planets[2].GetLocation());
        elseObj[1].Draw(ourShader);

        elseObj[2].UpdatePositionMatrix(ourShader, Planets[5].GetLocation());
        elseObj[2].Draw(ourShader);

        // Gui i update czasu symulacji
        Gui.Render(camera, Planets);
        Gui.UpdateIntervals(Planets, 8);
        Gui.UpdateIntervals(elseObj, 3);

        // zmiana bufferow i koniec inputow
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Czyszczenie
    for(int i=0; i<8; i++)
    {
        Planets[i].Delete();
    }

    for(int i=0; i<3; i++)
    {
        elseObj[i].Delete();
    }
    
    Gui.Delete();

    glfwTerminate();
    return 0;
}

// Zmiana rozmiarow okna
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    if (width == 0 || height == 0) return;

    SCR_HEIGHT = height;
    SCR_WIDTH = width;
    camera.SCR_HEIGHT = height;
    camera.SCR_WIDTH = width;
}

// scroll 
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
