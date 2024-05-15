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

// Collision
bool CollisionRender = false;

bool globalInit();
void windowSetup();

void processInput(GLFWwindow *window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void initMap(Entity *map, Shader *shader);

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
    
    Entity scene(&MainShader);

    Camera FreeCam, FpsCamera;
    FreeCam.setEditionMode(true);
    FreeCam.setPosition(glm::vec3(0.0f, 100.0f, 0.0f));
    FreeCam.setTranslationSpeed(2000.0f);

    FpsCamera.setRotation(glm::vec3(0,180,0)); 

    Player Slayer("../data/model/slayer/slayer.gltf", &MainShader, FpsCamera);
    scene.addChild(Slayer);
    Slayer.transform.setLocalPosition(glm::vec3(0, 400, 0));

    Weapon ar181("../data/model/plasma_rifle/scene.gltf", &MainShader, "../data/model/50bmg/scene.gltf");
    ar181.transform.setLocalScale(glm::vec3(0.5f, 0.5f, 0.5f));
    ar181.transform.setLocalRotation(glm::vec3(-90.0f, 1.0f, 1.0f));
    Slayer.addChild(ar181);
    Slayer.setWeapon(&ar181);


    Entity map(&MainShader); // Test collision
    scene.addChild(map);

    Entity road_1("../data/model/Map/road/scene.gltf", &MainShader);
    map.addChild(road_1);
    road_1.transform.setLocalScale(glm::vec3(0.5f));

    Entity bat_1("../data/model/Map/bat_clinic/scene.gltf", &MainShader);
    map.addChild(bat_1);
    bat_1.transform.setLocalScale(glm::vec3(0.5f));
    bat_1.transform.setLocalPosition(glm::vec3(1753, 0, -4470));

    Model basket("../data/model/Map/basket/scene.gltf");

    Entity basket_1(&basket, &MainShader);
    map.addChild(basket_1);
    basket_1.transform.setLocalScale(glm::vec3(0.5f));
    basket_1.transform.setLocalPosition(glm::vec3(-4451, 0, -4143));
    Entity basket_2(&basket, &MainShader);
    map.addChild(basket_2);
    basket_2.transform.setLocalScale(glm::vec3(0.5f));
    basket_2.transform.setLocalRotation(glm::vec3(0.0f, 180.0f, 0.0f));
    basket_2.transform.setLocalPosition(glm::vec3(-4451, 0, -5726));

    Entity car_1("../data/model/Map/car/scene.gltf", &MainShader);
    map.addChild(car_1);
    car_1.transform.setLocalScale(glm::vec3(60.0f));
    car_1.transform.setLocalRotation(glm::vec3(0.0f, 1140.0f, 0.0f));
    car_1.transform.setLocalPosition(glm::vec3(-2496, 0, -4173));
    
    Entity bat_2("../data/model/Map/bat_car_wash/scene.gltf", &MainShader);
    map.addChild(bat_2);
    bat_2.transform.setLocalScale(glm::vec3(0.5f));
    bat_2.transform.setLocalPosition(glm::vec3(-2776, 10, -4490));

    Model wall("../data/model/Map/wall/scene.gltf");
    Entity wall_1(&wall, &MainShader);
    map.addChild(wall_1);
    wall_1.transform.setLocalScale(glm::vec3(6.5f));
    wall_1.transform.setLocalPosition(glm::vec3(-6336, 300, 467));
    Entity wall_2(&wall, &MainShader);
    map.addChild(wall_2);
    wall_2.transform.setLocalScale(glm::vec3(6.5f));
    wall_2.transform.setLocalPosition(glm::vec3(-6336, 300, -11242));
    Entity wall_3(&wall, &MainShader);
    map.addChild(wall_3);
    wall_3.transform.setLocalScale(glm::vec3(6.5f));
    wall_3.transform.setLocalPosition(glm::vec3(-19303, 300, -6534));
    wall_3.transform.setLocalRotation(glm::vec3(0, 90, 0));
    Entity wall_4(&wall, &MainShader);
    map.addChild(wall_4);
    wall_4.transform.setLocalScale(glm::vec3(6.5f));
    wall_4.transform.setLocalPosition(glm::vec3(6616, 300, -6534));
    wall_4.transform.setLocalRotation(glm::vec3(0, 90, 0));

    Model bat__1("../data/model/Map/bat_1/scene.gltf");
    Entity bat_3(&bat__1, &MainShader);
    map.addChild(bat_3);
    bat_3.transform.setLocalScale(glm::vec3(0.2f, 0.3f, 0.4f));
    bat_3.transform.setLocalPosition(glm::vec3(1055, 0, -2444));
    bat_3.transform.setLocalRotation(glm::vec3(0, -90, 0));
    Entity bat_3_2(&bat__1, &MainShader);
    map.addChild(bat_3_2);
    bat_3_2.transform.setLocalScale(glm::vec3(0.2f, 0.3f, 0.4f));
    bat_3_2.transform.setLocalPosition(glm::vec3(-1582, 0, -8189));
    bat_3_2.transform.setLocalRotation(glm::vec3(0, -90, 0));
    Entity bat_3_3(&bat__1, &MainShader);
    map.addChild(bat_3_3);
    bat_3_3.transform.setLocalScale(glm::vec3(0.2f, 0.3f, 0.4f));
    bat_3_3.transform.setLocalPosition(glm::vec3(-5838, 0, -1035));
    Entity bat_3_4(&bat__1, &MainShader);
    map.addChild(bat_3_4);
    bat_3_4.transform.setLocalScale(glm::vec3(0.2f, 0.3f, 0.4f));
    bat_3_4.transform.setLocalPosition(glm::vec3(-15336, 0, -7350));

    Model bat__2("../data/model/Map/bat_2/scene.gltf");
    Entity bat_4(&bat__2, &MainShader);
    map.addChild(bat_4);
    bat_4.transform.setLocalScale(glm::vec3(0.5f));
    bat_4.transform.setLocalPosition(glm::vec3(-3541, 0, -8112));
    Entity bat_4_2(&bat__2, &MainShader);
    map.addChild(bat_4_2);
    bat_4_2.transform.setLocalScale(glm::vec3(0.5f));
    bat_4_2.transform.setLocalPosition(glm::vec3(-8066, 0, -917));
    bat_4_2.transform.setLocalRotation(glm::vec3(0, 180, 0));
    Entity bat_4_3(&bat__2, &MainShader);
    map.addChild(bat_4_3);
    bat_4_3.transform.setLocalScale(glm::vec3(0.5f));
    bat_4_3.transform.setLocalPosition(glm::vec3(-12516, 0, -5379));
    bat_4_3.transform.setLocalRotation(glm::vec3(0, 90, 0));

    Model bat__3("../data/model/Map/bat_3/scene.gltf");
    Entity bat_5(&bat__3, &MainShader);
    map.addChild(bat_5);
    bat_5.transform.setLocalScale(glm::vec3(0.5f));
    bat_5.transform.setLocalPosition(glm::vec3(-1733, 0, -858));
    bat_5.transform.setLocalRotation(glm::vec3(0, 180, 0));
    Entity bat_5_2(&bat__3, &MainShader);
    map.addChild(bat_5_2);
    bat_5_2.transform.setLocalScale(glm::vec3(0.5f));
    bat_5_2.transform.setLocalPosition(glm::vec3(953, 0, -8989));
    bat_5_2.transform.setLocalRotation(glm::vec3(0, -90, 0));
    Entity bat_5_3(&bat__3, &MainShader);
    map.addChild(bat_5_3);
    bat_5_3.transform.setLocalScale(glm::vec3(0.5f));
    bat_5_3.transform.setLocalPosition(glm::vec3(-6263, 0, -8989));
    bat_5_3.transform.setLocalRotation(glm::vec3(0, 90, 0));
    Entity bat_5_4(&bat__3, &MainShader);
    map.addChild(bat_5_4);
    bat_5_4.transform.setLocalScale(glm::vec3(0.5f));
    bat_5_4.transform.setLocalPosition(glm::vec3(-16576, 0, -2693));
    bat_5_4.transform.setLocalRotation(glm::vec3(0, 180, 0));
    Entity bat_5_5(&bat__3, &MainShader);
    map.addChild(bat_5_5);
    bat_5_5.transform.setLocalScale(glm::vec3(0.5f));
    bat_5_5.transform.setLocalPosition(glm::vec3(-8998, 0, -2693));

    Model bat__4("../data/model/Map/bat_4/scene.gltf");
    Entity bat_6(&bat__4, &MainShader);
    map.addChild(bat_6);
    bat_6.transform.setLocalScale(glm::vec3(0.5f));
    bat_6.transform.setLocalPosition(glm::vec3(940, 0, -6281));
    bat_6.transform.setLocalRotation(glm::vec3(0, -90, 0));
    Entity bat_6_2(&bat__4, &MainShader);
    map.addChild(bat_6_2);
    bat_6_2.transform.setLocalScale(glm::vec3(0.5f));
    bat_6_2.transform.setLocalPosition(glm::vec3(-4447, 0, -6288));
    bat_6_2.transform.setLocalRotation(glm::vec3(0, 180, 0));
    Entity bat_6_3(&bat__4, &MainShader);
    map.addChild(bat_6_3);
    bat_6_3.transform.setLocalScale(glm::vec3(0.5f));
    bat_6_3.transform.setLocalPosition(glm::vec3(-9848, 0, -8070));
    Entity bat_6_4(&bat__4, &MainShader);
    map.addChild(bat_6_4);
    bat_6_4.transform.setLocalScale(glm::vec3(0.5f));
    bat_6_4.transform.setLocalPosition(glm::vec3(-13440, 0, -866));
    bat_6_4.transform.setLocalRotation(glm::vec3(0, 90, 0));

    Model bat__5("../data/model/Map/bat_5/scene.gltf");
    Entity bat_7(&bat__5, &MainShader);
    map.addChild(bat_7);
    bat_7.transform.setLocalScale(glm::vec3(0.5f));
    bat_7.transform.setLocalPosition(glm::vec3(-846, 0, -6735));
    bat_7.transform.setLocalRotation(glm::vec3(0, -90, 0));
    Entity bat_7_2(&bat__5, &MainShader);
    map.addChild(bat_7_2);
    bat_7_2.transform.setLocalScale(glm::vec3(0.5f));
    bat_7_2.transform.setLocalPosition(glm::vec3(-8871, 0, -9874));
    Entity bat_7_3(&bat__5, &MainShader);
    map.addChild(bat_7_3);
    bat_7_3.transform.setLocalScale(glm::vec3(0.5f));
    bat_7_3.transform.setLocalPosition(glm::vec3(-15593, 0, -871));
    bat_7_3.transform.setLocalRotation(glm::vec3(0, 90, 0));

    Model bat__6("../data/model/Map/bat_6/scene.gltf");
    Entity bat_8(&bat__6, &MainShader);
    map.addChild(bat_8);
    bat_8.transform.setLocalScale(glm::vec3(0.5f, 1.6f, 0.5f));
    bat_8.transform.setLocalPosition(glm::vec3(-3984, 0, -9894));
    Entity bat_8_2(&bat__6, &MainShader);
    map.addChild(bat_8_2);
    bat_8_2.transform.setLocalScale(glm::vec3(0.5f, 1.6f, 0.5f));
    bat_8_2.transform.setLocalPosition(glm::vec3(-16995, 0, -7243));
    Entity bat_8_3(&bat__6, &MainShader);
    map.addChild(bat_8_3);
    bat_8_3.transform.setLocalScale(glm::vec3(0.5f, 1.6f, 0.5f));
    bat_8_3.transform.setLocalPosition(glm::vec3(-9816, 0, -5954));
    bat_8_3.transform.setLocalRotation(glm::vec3(0, -90, 0));

    Model bat__7("../data/model/Map/bat_7/scene.gltf");
    Entity bat_9(&bat__7, &MainShader);
    map.addChild(bat_9);
    bat_9.transform.setLocalScale(glm::vec3(0.5f));
    bat_9.transform.setLocalPosition(glm::vec3(-4469, 0, -8028));
    Entity bat_9_2(&bat__7, &MainShader);
    map.addChild(bat_9_2);
    bat_9_2.transform.setLocalScale(glm::vec3(0.5f));
    bat_9_2.transform.setLocalPosition(glm::vec3(-8057, 0, -8002));
    Entity bat_9_3(&bat__7, &MainShader);
    map.addChild(bat_9_3);
    bat_9_3.transform.setLocalScale(glm::vec3(0.5f));
    bat_9_3.transform.setLocalPosition(glm::vec3(-13462, 0, -9822));
    Entity bat_9_4(&bat__7, &MainShader);
    map.addChild(bat_9_4);
    bat_9_4.transform.setLocalScale(glm::vec3(0.5f));
    bat_9_4.transform.setLocalPosition(glm::vec3(-4504, 0, -149));
    bat_9_4.transform.setLocalRotation(glm::vec3(0, 90, 0));
    Entity bat_9_5(&bat__7, &MainShader);
    map.addChild(bat_9_5);
    bat_9_5.transform.setLocalScale(glm::vec3(0.5f));
    bat_9_5.transform.setLocalPosition(glm::vec3(-8984, 0, -925));
    bat_9_5.transform.setLocalRotation(glm::vec3(0, 180, 0));

    Model bat__8("../data/model/Map/bat_8/scene.gltf");
    Entity bat_10(&bat__8, &MainShader);
    map.addChild(bat_10);
    bat_10.transform.setLocalScale(glm::vec3(0.5f));
    bat_10.transform.setLocalPosition(glm::vec3(-11602, 0, -8046));
    Entity bat_10_2(&bat__8, &MainShader);
    map.addChild(bat_10_2);
    bat_10_2.transform.setLocalScale(glm::vec3(0.5f));
    bat_10_2.transform.setLocalPosition(glm::vec3(-2612, 0, -6261));
    bat_10_2.transform.setLocalRotation(glm::vec3(0, 180, 0));
    Entity bat_10_3(&bat__8, &MainShader);
    map.addChild(bat_10_3);
    bat_10_3.transform.setLocalScale(glm::vec3(0.5f));
    bat_10_3.transform.setLocalPosition(glm::vec3(-11688, 0, -908));
    bat_10_3.transform.setLocalRotation(glm::vec3(0, 180, 0));
    Entity bat_10_4(&bat__8, &MainShader);
    map.addChild(bat_10_4);
    bat_10_4.transform.setLocalScale(glm::vec3(0.5f));
    bat_10_4.transform.setLocalPosition(glm::vec3(-8018, 0, -4527));
    bat_10_4.transform.setLocalRotation(glm::vec3(0, 90, 0));


    
    Model chair("../data/model/Map/chair/scene.gltf");
    Entity chair_1(&chair, &MainShader);
    map.addChild(chair_1);
    chair_1.transform.setLocalPosition(glm::vec3(569, 30, -4276));
    chair_1.transform.setLocalRotation(glm::vec3(0, -90, 0));
    Entity chair_2(&chair, &MainShader);
    map.addChild(chair_2);
    chair_2.transform.setLocalPosition(glm::vec3(569, 30, -4639));
    chair_2.transform.setLocalRotation(glm::vec3(0, -90, 0));
    Entity chair_3(&chair, &MainShader);
    map.addChild(chair_3);
    chair_3.transform.setLocalPosition(glm::vec3(-1555, 30, -5714));
    Entity chair_4(&chair, &MainShader);
    map.addChild(chair_4);
    chair_4.transform.setLocalPosition(glm::vec3(-1981, 30, -5714));
    // MORE CHAIR !!!!

    Model Cacodemon("../data/model/cacodemon/scene.gltf");
    Model Cyberdemon("../data/model/cyberdemon/scene.gltf");
    
    Monster Demon(&Cacodemon, &MainShader);
    scene.addChild(Demon);
    Demon.transform.setLocalScale(glm::vec3(0.5f, 0.5f, 0.5f));
    Demon.transform.setLocalPosition(glm::vec3(2500.0f, 200.0f, 100.0f));
    Demon.setSpawnPoint(glm::vec3(2500.0f, 200.0f, 100.0f));
    Demon.transform.setLocalRotation(glm::vec3(0.0f, 97.0f, 0.0f));
    Demon.setRotationOffset(90.0f);

    Monster Knight("../data/model/cyberdemon/scene.gltf", &MainShader);
    scene.addChild(Knight);
    Knight.transform.setLocalScale(glm::vec3(15.0f, 15.0f, 15.0f));
    Knight.transform.setLocalPosition(glm::vec3(2200.0f, 400.0f, -300.0f));
    Knight.setSpawnPoint(glm::vec3(2200.0f, 200.0f, -300.0f));
    Knight.transform.setLocalRotation(glm::vec3(0.0f, -90.0f, 0.0f));
    Knight.setHealth(350); Knight.setDetectionRange(1500.0f); Knight.setDamage(40.0f);
    Knight.setRotationOffset(180.0f);
    Knight.setIsGravtityEntity(true);


    monsters.push_back(&Demon); monsters.push_back(&Knight);

    scene.updateSelfAndChild();

    // Get a handle for our "LightPosition" uniform
    // GLuint LightID = glGetUniformLocation(MainShader.getID(), "LightPosition_worldspace");
    
    // Chargement de la Skybox
    Shader SkyboxShader("../shader/vertexSky.glsl", "../shader/fragmentSky.glsl");
    Skybox skybox(&SkyboxShader);


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

        // if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) bat_10.transform.translate(Camera::projectVectorOnPlan(FreeCam.getFront(), VEC_UP) * 10.0f);
        // if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) bat_10.transform.setRotation(glm::vec3(0, 10, 0));
        // std::cout << bat_10.transform.getLocalPosition().x << " " << bat_10.transform.getLocalPosition().z << std::endl;
        // glm::vec3 p = Knight.transform.getLocalPosition();
        // std::cout << p.x << " " << p.y << " " << p.z << std::endl;


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
            bool isColliding = Slayer.CheckCollisionWithEntity(map);
            Slayer.update(isColliding, deltaTime, window);

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
                monster->update(monster->CheckCollisionWithEntity(map), deltaTime, Slayer.transform.getLocalPosition(), Slayer.getHealth());
            }

            if (Slayer.getHealth() <= 0) {
                Slayer.respawn(glm::vec3(0, 400, 0));
            }
        }

        MainShader.setMat4("View", currentCamera.getViewMatrix());
        MainShader.setMat4("Projection", currentCamera.getProjectionMatrix());
        MainShader.setInt("isEditMode", (int)isEditMode);

        // Scene
        scene.updateSelfAndChild();

        // Render
        skybox.render(currentCamera);
        skybox.shader->setInt("isEditMode", (int)isEditMode);
        if (CollisionRender) scene.renderCollision();
        else scene.render();

        // Camera
        MainShader.setVec3("cameraPos", currentCamera.getPosition());

        // Light 
        MainShader.setVec3("pointLightPos", currentCamera.getPosition());

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
    // glEnable(GL_CULL_FACE);
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

    if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
        CollisionRender = 
            !CollisionRender;
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

