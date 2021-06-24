#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "Camera.h"
#include "Rover.h"
#include "Terrain.h"
#include "StaticObject.h"

#ifdef defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "direct.h"
#endif

#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;

// camera
Camera camera(glm::vec3(0.0f, 10.0f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

glm::vec3 lightPos(1.2f, 2.0f, 2.0f);

Rover* roverPtr;

// What camera we're using right now
bool cameraFlip = false;


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Mars Rover", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader lightingShader("./resources/shaders/lightingShader.vs", "./resources/shaders/lightingShader.fs");

    lightingShader.setVec3("lightPos", lightPos);

    Terrain terrain(glm::vec3(0, 0, 0),
                    glm::vec3(0, 0, 0),
                    glm::vec3(1, 1, 1),
                    glm::vec3(1, 1, 1),
                    glm::vec3(1,1,1),
                    "./resources/plane.obj",
                    0);

    StaticObject rock(glm::vec3(15, 2, 10),
                      glm::vec3(0, 0, 0),
                      glm::vec3(1, 1, 1),
                      glm::vec3(1, 1, 1),
                      glm::vec3(1,1,1),
                      "./resources/rock.obj",
                      7);

    StaticObject monkeyStatue(glm::vec3(-15, 2, 10),
                      glm::vec3(0, 0, 0),
                      glm::vec3(1, 1, 1),
                      glm::vec3(1, 1, 1),
                              glm::vec3(1,1,1),
                      "./resources/monkeyStatue.obj",
                      2);

    Rover rover(glm::vec3(0,0.5,1),
                0,
                glm::vec3(1,1,1),
                glm::vec3(1,1,1),
                glm::vec3(0,0,0),
                "./resources/rover.obj",
                terrain.getHeightMap(),
                2);

    roverPtr = &rover;

    rover.addStaticObject(&rock);
    rover.addStaticObject(&monkeyStatue);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        lightPos = camera.Position + glm::vec3(0, 1.0f, 0);

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader.use();
        lightingShader.setVec3("lightPos", lightPos);
        lightingShader.setVec3("viewPos", camera.Position);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 300.0f);
        glm::mat4 view;
        if (cameraFlip)
            view = camera.GetViewMatrixFromRover(rover.position, rover.front);
        else
            view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        rover.updatePos();
        rover.draw(lightingShader);

        rock.draw(lightingShader);
        monkeyStatue.draw(lightingShader);
        terrain.draw(lightingShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    float speed = 0.03;

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        roverPtr->setLeftVelocity(roverPtr->getLeftVelocity() + speed);
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        roverPtr->setLeftVelocity(roverPtr->getLeftVelocity() - speed);
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    {
        roverPtr->setRightVelocity(roverPtr->getRightVelocity() + speed);
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        roverPtr->setRightVelocity(roverPtr->getRightVelocity() - speed);
    }

    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        cameraFlip = !cameraFlip;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
