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

// Audio
#include <irrKlang.h>

using namespace glm;

#include <common/Shader.hpp>
#include <common/vboindexer.hpp>
#include <common/Model.hpp>
#include <common/Camera.hpp>
#include <common/Entity.hpp>
#include <common/Skybox.hpp>
#include <common/Input.hpp>
#include <common/Player.hpp>
#include <common/Weapon.hpp>
#include <common/Monster.hpp>
#include <common/GLutils.hpp>
#include <common/Hud.hpp>

// settings
const unsigned int SCR_WIDTH = 1080;
const unsigned int SCR_HEIGHT = 720;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// Entity pointers
std::vector<Monster*> monsters;

//rotation
float angle = 0.;
float zoom = 1.;

//wire mode 
bool wireMode = false;

// edit mode
bool isEditMode = false;

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
    Shader MainShader( "../shader/vertex_shader.glsl", "../shader/fragment_shader.glsl" );
    MainShader.use();
    
    Camera FreeCam, FpsCamera;
    FreeCam.setEditionMode(true);
    FreeCam.setTranslationSpeed(2000.0f);

    Entity scene(&MainShader);  
    
    Player Slayer("../data/model/slayer/slayer.gltf", &MainShader, FpsCamera);
    Slayer.transform.setLocalPosition(glm::vec3(0, 400, 0));

    Weapon ar181("../data/model/plasma_rifle/scene.gltf", &MainShader, "../data/model/50bmg/scene.gltf");
    ar181.transform.setLocalScale(glm::vec3(0.5f, 0.5f, 0.5f));
    ar181.transform.setLocalRotation(glm::vec3(-90.0f, 1.0f, 1.0f));

    Entity map(&MainShader); // Test collision
    Entity map2("../data/model/cube/Cube.gltf", &MainShader);
    Entity map3("../data/model/cube/Cube.gltf", &MainShader);
    Entity map4("../data/model/cube/Cube.gltf", &MainShader);
    Entity map5("../data/model/cube/Cube.gltf", &MainShader);

    map2.transform.setLocalScale(glm::vec3(200, 200, 10));
    map2.transform.setLocalPosition(glm::vec3(0, 0, -200));
    map3.transform.setLocalScale(glm::vec3(200, 200, 10));
    map3.transform.setLocalPosition(glm::vec3(0, 0, 200));
    map4.transform.setLocalScale(glm::vec3(200, 10, 200));
    map4.transform.setLocalPosition(glm::vec3(0, -100, 0));
    map5.transform.setLocalScale(glm::vec3(200, 10, 200));
    map5.transform.setLocalPosition(glm::vec3(200, -50, 0));

    map.addChild(map2);
    map.addChild(map5);
    map.addChild(map4);
    map.addChild(map3);

    Entity stoneGround("../data/model/stone_ground/scene.gltf", &MainShader);
    stoneGround.transform.setLocalScale(glm::vec3(2000.0f));

    Entity grassGround("../data/model/grass_ground/scene.gltf", &MainShader);
    grassGround.transform.setLocalScale(glm::vec3(2000.0f));
    grassGround.transform.setLocalPosition(glm::vec3(2000.0f, 0.0f, 0.0f));

    map.addChild(stoneGround);
    map.addChild(grassGround);

    Monster Demon("../data/model/cacodemon/scene.gltf", &MainShader);
    Demon.transform.setLocalScale(glm::vec3(0.5f, 0.5f, 0.5f));
    Demon.transform.setLocalPosition(glm::vec3(2500.0f, 200.0f, 100.0f));
    Demon.setSpawnPoint(glm::vec3(2500.0f, 200.0f, 100.0f));
    Demon.transform.setLocalRotation(glm::vec3(0.0f, 97.0f, 0.0f));
    Demon.setRotationOffset(90.0f);

    Monster Knight("../data/model/cyberdemon/scene.gltf", &MainShader);
    Knight.transform.setLocalScale(glm::vec3(15.0f, 15.0f, 15.0f));
    Knight.transform.setLocalPosition(glm::vec3(2200.0f, 200.0f, -300.0f));
    Knight.setSpawnPoint(glm::vec3(2200.0f, 200.0f, -300.0f));
    Knight.transform.setLocalRotation(glm::vec3(0.0f, -90.0f, 0.0f));
    Knight.setIsGravtityEntity(true);
    Knight.setHealth(350); Knight.setDetectionRange(1500.0f); Knight.setDamage(40.0f);
    Knight.setRotationOffset(180.0f);

    // Monster bigBrain("../data/model/naked/scene.gltf", &MainShader);
    // bigBrain.transform.setLocalScale(glm::vec3(0.5f, 0.5f, 0.5f));
    // bigBrain.transform.setLocalPosition(glm::vec3(2400.0f, 200.0f, 400.0f));
    // bigBrain.setSpawnPoint(glm::vec3(2400.0f, 200.0f, 400.0f));
    // bigBrain.transform.setLocalRotation(glm::vec3(0.0f, 50.0f, 0.0f));
    // bigBrain.setHealth(200); bigBrain.setDetectionRange(1800.0f); bigBrain.setDamage(50.0f);


    monsters.push_back(&Demon); monsters.push_back(&Knight);

    // map 
    scene.addChild(map);
    // Player
    scene.addChild(Slayer);
    // Weapon
    Slayer.addChild(ar181);
    Slayer.setWeapon(&ar181);
    // Monster
    scene.addChild(Demon); scene.addChild(Knight);
    // Misc

    scene.updateSelfAndChild();

    // Get a handle for our "LightPosition" uniform
    // GLuint LightID = glGetUniformLocation(MainShader.getID(), "LightPosition_worldspace");
    
    // Chargement de la Skybox
    Skybox skybox;
    skybox.init(Shader("../shader/vertexSky.glsl", "../shader/fragmentSky.glsl"));

    // Hud
    Shader HUDShader("../shader/vertexHUD.glsl", "../shader/fragmentHUD.glsl");
    Shader TextShader("../shader/vertexText.glsl", "../shader/fragmentText.glsl");
    Hud hud(&HUDShader, &TextShader, SCR_WIDTH, SCR_HEIGHT);

    // Pressing only one time
    glfwSetKeyCallback(window, key_callback);

    // For speed computation
    double lastTime = glfwGetTime();
    int nbFrames = 0;

    irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
    engine->setSoundVolume(0.20f);
    Slayer.setSoundEngine(engine);
    ar181.setSoundEngine(engine);

    // Intro
    float IntroDuration = 9.0f + glfwGetTime(); // 10 seconds
    float IntroTimer = glfwGetTime();
    bool played = false;

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

        // Debug
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(MessageCallback, 0);

        // Use our shader

        // -- Update --
        MainShader.use();
        
        Camera currentCamera;
        if (IntroTimer < IntroDuration) {
            hud.renderText("Welcome to hell", SCR_WIDTH/3 - 45.0f, SCR_WIDTH/3, 2.0f, glm::vec3(0.529, 0.122, 0.051));
            hud.renderText("Made with GoultardEngine", SCR_WIDTH/3, 25.0f, 1.0f, glm::vec3(0.141, 0.075, 0.075));
            if(!played) {
                engine->play2D("../data/sound/dssgcock.wav", false);
                engine->play2D("../data/sound/AtDoomsGate.wav", false);
                played = true;
            }
            IntroTimer = glfwGetTime();
        }        


        if (isEditMode) {
            FreeCam.update(deltaTime, window);
            currentCamera = FreeCam;
        } else {
            // Player
            Slayer.camera.update(deltaTime, window);

            bool isColliding = Slayer.CheckCollisionWithEntity(map);
            Slayer.updateInput(isColliding, deltaTime, window);

            currentCamera = Slayer.camera;
            
            // HUD
            hud.render(Slayer.getHealth(), Slayer.getMaxHealth(), Slayer.weapon->getAmmo());
            MainShader.use();

            // Weapon
            Slayer.weapon->updateBullets(deltaTime);

            // Collision with monster
            for (auto&& bullet : Slayer.weapon->getBullets()) {
                for (auto&& monster : monsters) {
                    if (monster->CheckCollisionWithEntity(*bullet)) {
                        bullet->setAlive(false);
                        monster->setHealth(monster->getHealth() - bullet->getDamage());
                        monster->setisChasing(true);
                        // respawn
                        if (monster->getHealth() <= 0) {
                            monster->respawn(monster->getSpawnPoint());
                        }
                    }
                }
            }

            // Monster
            for (auto&& monster : monsters) {
                monster->detectPlayer(Slayer.transform.getLocalPosition(), deltaTime, Slayer.getHealth());
            }

            if (Slayer.getHealth() <= 0) {
                Slayer.respawn(glm::vec3(0, 400, 0));
            }
        }

        // Scene
        scene.updateSelfAndChild();

        MainShader.setMat4("View", currentCamera.getViewMatrix());
        MainShader.setMat4("Projection", currentCamera.getProjectionMatrix());

        // Render
        skybox.render(currentCamera);
        scene.render();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    glDeleteProgram(MainShader.getID());
    
    // Cleanup VBO and shader
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
    window = glfwCreateWindow( SCR_WIDTH, SCR_HEIGHT, "GoultardEngine", NULL, NULL);
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

    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        isEditMode = !isEditMode;
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