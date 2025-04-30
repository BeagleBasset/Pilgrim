#include "Renderer.hpp"
#include "ShaderLoader.hpp"
#include <glm/gtc/type_ptr.hpp> 



bool Renderer::Init(int width, int height, const std::string& title)
{
	m_width = width;
	m_height = height;

    if (!glfwInit()) {
        std::cerr << "GLFW init failed!\n";
        return false;
    }

    GLFWwindow* rawWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!rawWindow) {
        std::cerr << "Window creation failed!\n";
        glfwTerminate();
        return false;
    }
    m_window = std::shared_ptr<GLFWwindow>(rawWindow, [](GLFWwindow* ptr) { glfwDestroyWindow(ptr); });

    glfwMakeContextCurrent(m_window.get());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to init GLAD!\n";
        return false;
    }

	// Shader program
    terrainShaderProgram = LoadShaders("Shaders/Terrain.vs", "Shaders/Terrain.fs");
    if (terrainShaderProgram == 0) {
        std::cerr << "Shader load failed!" << std::endl;
    }


    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);              // mélységi teszt
    glEnable(GL_LIGHTING);                // világítás engedélyezése
    glEnable(GL_LIGHT0);                  // az elsõ fényforrás engedélyezése
    glEnable(GL_COLOR_MATERIAL);          // hogy glColor is hasson

    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightPosition[] = { 0.0f, 10.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glfwSetInputMode(m_window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(m_window.get(), this);
    glfwSetCursorPosCallback(m_window.get(), MouseCallback);


    return true;
}

void Renderer::BeginFrame()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Renderer::EndFrame()
{
	glfwSwapBuffers(m_window.get());
	glfwPollEvents();
}

bool Renderer::WindowShouldClose()
{
	return glfwWindowShouldClose(m_window.get());
}

std::shared_ptr<GLFWwindow> Renderer::GetWindow() const
{
	return m_window;
}

std::pair<int, int> Renderer::GetWindowSize() const
{
	return { m_width, m_height };
}

void Renderer::Setup2D()
{
    glm::mat4 ortho = glm::ortho(
        0.0f,            // left
        (float)m_width,  // right
        (float)m_height, // bottom
        0.0f,            // top
        -1.0f,           // near
        1.0f            // far
    );
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(ortho));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Renderer::Setup3D()
{
    
    float fov = 45.0f;
    float aspect = static_cast<float>(m_width) / m_height;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    glClearColor(0.53f, 0.81f, 0.98f, 1.0f);  // Sky color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 proj = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
    glm::mat4 view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);

    glm::mat4 pv = proj * view;

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(proj));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view));
}

void Renderer::ProcessMouseMovement(double xpos, double ypos)
{
    if (m_firstMouse)
    {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
    }

    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos; 
    m_lastX = xpos;
    m_lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (m_pitch > 89.0f) m_pitch = 89.0f;
    if (m_pitch < -89.0f) m_pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_cameraFront = glm::normalize(front);
}

void Renderer::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
    if (renderer) {
        renderer->ProcessMouseMovement(xpos, ypos);
    }
}

glm::mat4 Renderer::GetProjectionMatrix() const {
    float fov = 45.0f;
    float aspect = static_cast<float>(m_width) / m_height;
    return glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
}

glm::mat4 Renderer::GetViewMatrix() const {
    return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}

void Renderer::DrawMesh(const TerrainMesh& mesh, const glm::mat4& model)
{
    UploadMeshData(mesh); 

    glUseProgram(terrainShaderProgram);

    glUniform1f(glGetUniformLocation(terrainShaderProgram, "waterLevel"), 00.0f);
    glUniform1f(glGetUniformLocation(terrainShaderProgram, "sandLevel"), 2.0f);
    glUniform1f(glGetUniformLocation(terrainShaderProgram, "grassLevel"), 10.0f);
    glUniform1f(glGetUniformLocation(terrainShaderProgram, "rockLevel"), 40.0f);
    glUniform1f(glGetUniformLocation(terrainShaderProgram, "snowLevel"), 60.0f);

    float time = static_cast<float>(glfwGetTime());
    int loc = glGetUniformLocation(terrainShaderProgram, "u_Time");
    glUniform1f(loc, time);

	auto cameraPos = GetCameraPos();
    
    glUniform3fv(glGetUniformLocation(terrainShaderProgram, "u_CameraPos"), 1, glm::value_ptr(cameraPos));

    glUniformMatrix4fv(glGetUniformLocation(terrainShaderProgram, "u_Model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(terrainShaderProgram, "u_View"), 1, GL_FALSE, glm::value_ptr(GetViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(terrainShaderProgram, "u_Projection"), 1, GL_FALSE, glm::value_ptr(GetProjectionMatrix()));
    glBindVertexArray(terrainVAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0); 
    glBindVertexArray(0);
    glUseProgram(0);
}

void Renderer::UploadMeshData(const TerrainMesh& mesh)
{
    if (terrainVAO == 0) {
        glGenVertexArrays(1, &terrainVAO);
        glGenBuffers(1, &terrainVBO);
        glGenBuffers(1, &terrainEBO);
    }

    glBindVertexArray(terrainVAO);

    glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(glm::vec3), mesh.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    indexCount = static_cast<GLsizei>(mesh.indices.size());
}

void Renderer::InitCloud()
{
    float quadVertices[] = {
        //    X      Y     Z      U   V
        -1.0f, 0.0f, -0.5f,   0.0f, 1.0f,  
         1.0f, 0.0f, -0.5f,   1.0f, 1.0f,  
         1.0f, 0.0f,  0.5f,   1.0f, 0.0f,  

        -1.0f, 0.0f, -0.5f,   0.0f, 1.0f,  
         1.0f, 0.0f,  0.5f,   1.0f, 0.0f,  
        -1.0f, 0.0f,  0.5f,   0.0f, 0.0f   
    };

    glGenVertexArrays(1, &cloudVAO);
    glGenBuffers(1, &cloudVBO);

    glBindVertexArray(cloudVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cloudVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1); // texcoord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindVertexArray(0);
    glUseProgram(0);

    // Felhõ shader betöltése
    cloudShaderProgram = LoadShaders("Shaders/Cloud.vs", "Shaders/Cloud.fs");
    if (cloudShaderProgram == 0) {
        std::cerr << "Shader load failed!" << std::endl;
    }
}

void Renderer::DrawClouds(const std::vector<Cloud>& clouds)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    glUseProgram(cloudShaderProgram);

    GLuint mU = glGetUniformLocation(cloudShaderProgram, "u_Model");
    GLuint vU = glGetUniformLocation(cloudShaderProgram, "u_View");
    GLuint pU = glGetUniformLocation(cloudShaderProgram, "u_Projection");
    glm::mat4 view = GetViewMatrix();
    glm::mat4 proj = GetProjectionMatrix();

    glBindVertexArray(cloudVAO);
    for (const Cloud& cloud : clouds) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), cloud.pos);
        model = glm::scale(model, glm::vec3(cloud.scale));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        glUniformMatrix4fv(mU, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(vU, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(pU, 1, GL_FALSE, glm::value_ptr(proj));

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    glBindVertexArray(0);

    glUseProgram(0);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer()
{
    
	std::cout << "Renderer destructor called" << std::endl;
	
    if (cloudShaderProgram != 0) 
		glDeleteProgram(cloudShaderProgram);

	if (cloudVAO != 0) 
		glDeleteVertexArrays(1, &cloudVAO);

	if (cloudVBO != 0) 
		glDeleteBuffers(1, &cloudVBO);

    if (terrainShaderProgram != 0) 
        glDeleteProgram(terrainShaderProgram);
    

    if (terrainVAO != 0) 
        glDeleteVertexArrays(1, &terrainVAO);
    

    if (terrainVBO != 0) 
        glDeleteBuffers(1, &terrainVBO);
    

    if (terrainEBO != 0) 
        glDeleteBuffers(1, &terrainEBO);


    glfwTerminate();
}