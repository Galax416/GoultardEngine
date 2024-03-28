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
#include <common/camera.hpp>

void processInput(GLFWwindow *window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods); // Fix les input trop rapide
void mouse_callback(GLFWwindow* window, double xpos, double ypos); // Souris
double lastX = 400, lastY = 300;
bool firstMouse = true;
bool mouseButtonPressed = false; // Indicateur pour savoir si le bouton de la souris est actuellement enfoncé

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera_libre;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//rotation
float angle = 0.;
float zoom = 1.;

//wire mode 
bool wireMode = false;
/*******************************************************************************/

int main( void )
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "TP1 - GLFW", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPosCallback(window, mouse_callback);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

    // Dark blue background
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    //glEnable(GL_CULL_FACE);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "vertex_shader.glsl", "fragment_shader.glsl" );

    /*****************TODO***********************/
    // Get a handle for our "Model View Projection" matrices uniforms

    /****************************************/
    std::vector<unsigned short> indices; //Triangles concaténés dans une liste
    std::vector<std::vector<unsigned short> > triangles;
    std::vector<glm::vec3> indexed_vertices;

    //Chargement du fichier de maillage
    std::string filename("suzanne.off");
    loadOFF(filename, indexed_vertices, indices, triangles );

    // Load it into a VBO

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

    // Generate a buffer for the indices as well
    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

    // Get a handle for our "LightPosition" uniform
    glUseProgram(programID);
    GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

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

        // input
        // -----
        processInput(window);
        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            if (button == GLFW_MOUSE_BUTTON_LEFT) {
                mouseButtonPressed = (action == GLFW_PRESS);
                if (mouseButtonPressed) {
                    // Mettre à jour la dernière position de la souris uniquement lorsqu'elle est enfoncée
                    glfwGetCursorPos(window, &lastX, &lastY);
                }
            }
        });


        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);


        /*****************TODO***********************/
        // Model matrix : an identity matrix (model will be at the origin) then change
        glm::mat4 modelMatrix = glm::mat4(1.f);

        // View matrix : camera/view transformation lookat() utiliser camera_position camera_target camera_up
        glm::mat4 viewMatrix = glm::lookAt(camera_libre.getPosition(), camera_libre.getPosition() + camera_libre.getTarget(), camera_libre.getUp());
        
        // Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        glm::mat4 projectionMatrix = camera_libre.getProjectionMatrix();

        // Send our transformation to the currently bound shader,
        // in the "Model View Projection" to the shader uniforms
        glUniformMatrix4fv(glGetUniformLocation(programID, "Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(glGetUniformLocation(programID, "View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(programID, "Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        /****************************************/




        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                    0,                  // attribute
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                    );

        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

        // Draw the triangles !
        glDrawElements(
                    GL_TRIANGLES,      // mode
                    indices.size(),    // count
                    GL_UNSIGNED_SHORT,   // type
                    (void*)0           // element array buffer offset
                    );

        glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &elementbuffer);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //Camera zoom in and out
    camera_libre.setCameraSpeed(2.5 * deltaTime);

    // ZQSD
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera_libre.moveFoward();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera_libre.moveBackward();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera_libre.moveLeft();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera_libre.moveRight();

    // Haut/Bas
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera_libre.moveUp();
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera_libre.moveDown();

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        wireMode = !wireMode;
        if(wireMode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse && mouseButtonPressed) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    if (mouseButtonPressed) {
        // Calculer la différence de position de la souris depuis la dernière frame
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // Inverser car l'origine de l'écran est en haut à gauche

        // Mettre à jour la dernière position de la souris
        lastX = xpos;
        lastY = ypos;

        // Ajuster la direction de la caméra en fonction des mouvements de la souris
        xoffset *= 0.1f;
        yoffset *= 0.1f;

        // Rotation autour de l'axe y (gauche/droite)
        glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), -glm::radians(xoffset), camera_libre.getUp());
        camera_libre.setTarget(glm::vec3(rotationY * glm::vec4(camera_libre.getTarget(), 0.0f)));   

        // Rotation autour de l'axe x (haut/bas)
        glm::vec3 right = glm::normalize(glm::cross(camera_libre.getUp(), camera_libre.getTarget()));
        glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), -glm::radians(yoffset), right);
        camera_libre.setTarget(glm::vec3(rotationX * glm::vec4(camera_libre.getTarget(), 0.0f)));
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
