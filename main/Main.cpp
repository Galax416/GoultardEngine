#pragma once

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

#include <common/shader.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/Model.hpp>
#include <common/Camera.hpp>
#include <common/Entity.hpp>
#include <common/Skybox.hpp>
#include <common/Input.hpp>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//rotation
float angle = 0.;
float zoom = 1.;

//wire mode 
bool wireMode = false;

bool globalInit();
void windowSetup();

/*******************************************************************************/

int main( void )
{
    
    if (!globalInit())
    {
        return -1;
    }

    // Create and compile our GLSL program from the shaders
    Shader MainShader( "vertex_shader.glsl", "fragment_shader.glsl" );
    MainShader.Use();

    Entity scene;

    Entity Slayer("../data/model/slayer/slayer.gltf", MainShader);
    Slayer.transform.setLocalScale(glm::vec3(0.1f, 0.1f, 0.1f));

    Entity kiki("../data/model/kiki/scene.gltf", MainShader);
    kiki.transform.setLocalScale(glm::vec3(0.1f, 0.1f, 0.1f));

    scene.addChild(Slayer);
    scene.addChild(kiki);
    
    scene.updateSelfAndChild();

    Slayer.bindVBO(MainShader.ID);
    kiki.bindVBO(MainShader.ID);

    // Get a handle for our "LightPosition" uniform
    GLuint LightID = glGetUniformLocation(MainShader.ID, "LightPosition_worldspace");
    // Chargement de la Skybox
    Skybox skybox;
    skybox.init();

    scene.bindVBO(MainShader.ID);
   
    // Init Camera
    Camera camera_libre;
    camera_libre.init();

    // Pressing only one time
    glfwSetKeyCallback(window, key_callback);

    // For speed computation
    double lastTime = glfwGetTime();
    int nbFrames = 0;

    do{

        // Measure speed
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Show FPS in consol
        // std::cout << round(1.0 / deltaTime) << std::endl; 

        // input
        // -----
        processInput(window);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        MainShader.Use();

        Slayer.Draw();
        kiki.Draw();
        // Update
        camera_libre.update(deltaTime, window);
        scene.updateSelfAndChild();

        // Render
        skybox.render(camera_libre);
        scene.render(camera_libre);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    glDeleteProgram(MainShader.ID);
    // Cleanup VBO and shader
    scene.unbindVBO();
    skybox.clear();

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}


bool globalInit()
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "GoultardEngine", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return false;
    }

    windowSetup();
    return true;
}

void windowSetup()
{
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    //glfwSetCursorPos(window, 1024 / 2, 768 / 2);

    // Dark blue background
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        wireMode = !wireMode;
        if(wireMode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
