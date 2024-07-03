#include "Mygui.h"


MyGui::MyGui()
{
    Setup();
}

// setup
void MyGui::Setup()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

// wczytanie informacji o nowej klatce
void MyGui::FrameInfo()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}


// wyswietlenie gui
void MyGui::Render(Camera& camera, Object planets[])
{
    float buttonWidth = 100.0f;
    ImGui::GetCurrentContext();
    ImGui::Begin("Opcje");
    ImGui::Text("Wybierz rodzaj kamery");

    // widok z gory
    if (ImGui::Button("Widok z gory", ImVec2(buttonWidth, 0)))
    {
        camera.Position = glm::vec3(0, 200.0f, 0);
        camera.Pitch = -89.0f;
        camera.Yaw = -90.0f; 
        camera.Above_view = true;
        camera.UpdateCameraVectors();
    }
    ImGui::SameLine();

    // resetuje kamere
    if (ImGui::Button("Reset kamery", ImVec2(buttonWidth, 0)))
    {
        camera.Position = glm::vec3(0.0f, 0.0f, 25.0f);
        camera.Pitch = 0.0f;
        camera.Yaw = -90.0f;
        camera.Above_view = false;
        camera.UpdateCameraVectors();
    }

    const float timeRates[] = {0, 1.0f, 100.0f, 1000.0f, 10000.0f, 100000.0f, 1000000.0f, 10000000.0f};
    const int timeRateCount = sizeof(timeRates) / sizeof(float);

    // znalezienie najblizszej wartosci
    int currentTimeRateIndex = 0;
    float minDistance = FLT_MAX;
    for (int i = 0; i < timeRateCount; i++)
    {
        float distance = fabsf(timeRate - timeRates[i]);
        if (distance < minDistance)
        {
            minDistance = distance;
            currentTimeRateIndex = i;
        }
    }

    char label[35];
    // zapisanie wiadomosci do 1 miejsca po przecinku
    snprintf(label, sizeof(label), "Predkosc symulacji: x%.1f", timeRates[currentTimeRateIndex]);
    ImGui::Text(label);
    
    // slider
    ImGui::SetNextItemWidth(150.0f);
    if (ImGui::SliderInt(" ", &currentTimeRateIndex, 0, timeRateCount - 1))
    {
        timeRate = timeRates[currentTimeRateIndex];
    }

    ImGui::Text("Wybierz widok na planete:");
    // guziki na przesuniecie kamery na planete
    for (int i = 0; i < 8; i++)
    {
        if (ImGui::Button(planets[i].GetName(), ImVec2(buttonWidth, 0)))
        {
            // reset kamery
            camera.Position = glm::vec3(0.0f, 0.0f, 5.0f);
            camera.Pitch = 0.0f;
            camera.Yaw = -90.0f;
            camera.Zoom = 45.0f;
            camera.Above_view = false;
            camera.UpdateCameraVectors();

            // dystans od planety
            float distance = planets[i].scale * 3.5f;

            // obliczenie gdzie sie powinna znajdowac kamera wzgledem planety
            glm::vec3 planetLocation = planets[i].GetLocation();
            glm::vec3 offset = glm::normalize(camera.Position - planetLocation) * distance;
            camera.Position = planetLocation + offset;

            // obliczenie gdzie sie patrzy kamera wzgledem planety
            glm::vec3 direction = glm::normalize(planetLocation - camera.Position);
            camera.Yaw = glm::degrees(atan2(direction.z, direction.x));

            camera.UpdateCameraVectors();
        }
    }
    
    ImGui::End();

    // wyswietlenie gui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// usuniecie gui
void MyGui::Delete()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

// aktualizacja czasu symulacji
void MyGui::UpdateIntervals(Object objects[], int size)
{
    for(int i = 0; i < size; i++)
    {
        objects[i].orbit_interval = objects[i].default_orbit_interval * timeRate;
        objects[i].spin_interval = objects[i].default_spin_interval * timeRate;
    }
}
