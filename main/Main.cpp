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

#include <common/Shader.hpp>
#include <common/vboindexer.hpp>
#include <common/Model.hpp>
#include <common/Camera.hpp>
#include <common/Entity.hpp>
#include <common/Skybox.hpp>
#include <common/Input.hpp>
#include <common/Player.hpp>

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

bool inFreeCam = false;

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

    Camera FreeCam;
    FreeCam.init();
    FreeCam.setEditionMode(true);

    Camera FpsCamera;

    Entity scene(MainShader);

    Player Slayer("../data/model/slayer/slayer.gltf", MainShader, FpsCamera);

    Entity ar181("../data/model/plasma_rifle/scene.gltf", MainShader);
    ar181.transform.setLocalScale(glm::vec3(0.5f, 0.5f, 0.5f));
    ar181.transform.setLocalRotation(glm::vec3(-90.0f, 1.0f, 1.0f));
    ar181.transform.setLocalPosition(glm::vec3(-20.0f, 70.0f, 60.0f));

    Entity map("../data/model/map/scene.gltf", MainShader);
    map.transform.setLocalRotation(glm::vec3(-90.0f, 0.0f, 0.0f));
    map.transform.setLocalPosition(glm::vec3(800.0f, 0.0f, 0.0f));

    scene.addChild(Slayer);
    //scene.addChild(map);
    Slayer.addChild(ar181);

    scene.updateSelfAndChild();

    // Get a handle for our "LightPosition" uniform
    GLuint LightID = glGetUniformLocation(MainShader.ID, "LightPosition_worldspace");
    // Chargement de la Skybox
    Skybox skybox;
    skybox.init(Shader("../main/vertexSky.glsl", "../main/fragmentSky.glsl"));

    scene.bindVBO(MainShader.ID);
   
    // Init Camera
    //Camera camera_libre;
    //camera_libre.init();

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
        //Slayer.transform.setLocalPosition(Slayer.camera.getPosition());
        //Slayer.camera.setPosition(Slayer.transform.getLocalPosition());

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader

        // Update
        MainShader.Use();
        Slayer.camera.update(deltaTime, window);
        Slayer.updateInput(deltaTime, window);
        scene.updateSelfAndChild();
        FreeCam.update(deltaTime, window);

        //if (Slayer.camera.getEditionMode()) {
            glUniformMatrix4fv(glGetUniformLocation(MainShader.ID, "View"), 1, GL_FALSE, &Slayer.camera.getViewMatrix()[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(MainShader.ID, "Projection"), 1, GL_FALSE, &Slayer.camera.getProjectionMatrix()[0][0]);
        //}
		
        // Render
        skybox.render(Slayer.camera);
        scene.render();

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
