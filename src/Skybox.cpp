#include "Skybox.h"

void checkGLError(const std::string& function) {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error in " << function << ": " << error << std::endl;
    }
}

Skybox::Skybox(Shader &skyboxShader)
{
    skyboxShader.activate();

	// wczytanie vertexow i kolejnosci
	glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);

	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// 
    std::string Dir = "resources/images/"; 
    std::string facesCubemap[6] =
	{
		Dir + "walls.jpg",
		Dir + "walls.jpg",
		Dir + "updown.jpg",
		Dir + "updown.jpg",
		Dir + "walls.jpg",
		Dir + "walls.jpg"
	}; 

	// bind id textur i ustawienia
	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// 
	//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// wczytanie textur
    for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
            //std::cout << "Loaded texture: " << facesCubemap[i] << " (" << width << "x" << height << ", " << nrChannels << " channels)" << std::endl;
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture: " << facesCubemap[i] << " (" << width << "x" << height << ", " << nrChannels << " channels)\n";
			stbi_image_free(data);
		}
	}
}

void Skybox::Draw(Shader &skyboxShader, Camera &camera)
{
    glDepthFunc(GL_LEQUAL);

	skyboxShader.activate();

	// aktualizacja shadera
	glm::mat4 view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
	glm::mat4 projection = glm::perspective(
		glm::radians(45.0f),
		(float)camera.SCR_WIDTH / camera.SCR_HEIGHT,
		camera.min_view,
		camera.max_view
		);

    skyboxShader.setMat4("view", view);
    skyboxShader.setMat4("projection", projection);

	// rysowanie 
    glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
    glDepthFunc(GL_LESS);
}