#include <chrono>
#include <iostream>
#include <string>
#include <random>

#define TINYOBJLOADER_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "Graphics Engine/Model3D.h"
#include "Graphics Engine/Shader.h"
#include "Graphics Engine/Input.h"

#include "Camera/MyCamera.h"
#include "Camera/OrthoCamera.h"
#include "Camera/PerspectiveCamera.h"

#include "P6/MyVector.h"
#include "P6/PhysicsParticle.h"
#include "P6/PhysicsWorld.h"
#include "P6/RenderParticle.h"
#include "P6/DragForce.h"

#define PI 3.14159
using namespace std::chrono_literals;
constexpr std::chrono::nanoseconds timestep(16ms);

int main(void) {
    std::fstream vertSrc("Shaders/Sample.vert");
    std::stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();
    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    std::fstream fragSrc("Shaders/Sample.frag");
    std::stringstream fragBuff;
    fragBuff << fragSrc.rdbuf();
    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(800, 800, "PC01 Catrina Mikaela G. Ramirez & Gracielle Ann R. Jacinto", NULL, NULL);
    
    if (!window) {
        glfwTerminate();
        return -1;
    }

    float window_width = 800;
    float window_height = 800;

    MyCamera* cameraOrtho = new OrthoCamera(window_height, window_width);
    OrthoCamera* pCameraOrtho = (OrthoCamera*)cameraOrtho;

    MyCamera* cameraPerspective = new PerspectiveCamera(window_height, window_width);
    PerspectiveCamera* pCameraPerspective = (PerspectiveCamera*)cameraPerspective;

    glfwMakeContextCurrent(window);
    gladLoadGL();

    Input input;
    glfwSetWindowUserPointer(window, &input);
    glfwSetKeyCallback(window, Input::Key_Callback);

    Shader shader(v, f);

    Model3D object("3D/white.jpg", "3D/sphere.obj");
    object.setShaders(shader.getShaderProg());
    object.createModel();

    cameraOrtho->createCamera();
    cameraPerspective->createCamera();

    P6::PhysicsWorld pWorld = P6::PhysicsWorld();
    std::list<RenderParticle*> RenderParticles;

    int sparkAmount = 0;
    std::cout << "Enter Spark Amount: ";
    std::cin >> sparkAmount;

    const float spawnInterval = 100.f;
    int maxParticles = sparkAmount;
    int particlesSpawned = 0;

    using clock = std::chrono::steady_clock;
    auto lastSpawnTime = clock::now();
    using clock = std::chrono::high_resolution_clock;
    auto start_time = clock::now();
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);

    std::random_device rd;
    std::uniform_real_distribution<float> dist(1.0f, 10.0f);
    std::uniform_real_distribution<float> distForce(50.f, 100.f);
    std::uniform_real_distribution<float> distAngle(80.f, 110.f);
    std::uniform_real_distribution<float> distAngle_2(0.f, 360.f);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        auto currentTime = clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastSpawnTime);

        curr_time = clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(curr_time - prev_time);
        prev_time = curr_time;
        curr_ns += dur;

        if (curr_ns >= timestep) {
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);
            curr_ns -= curr_ns;

            if (!input.getSpace())
                pWorld.Update((float)ms.count() / 1000);
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LEQUAL);
        glUseProgram(shader.getShaderProg());
        
        if (input.getPerspective()) {
            pCameraPerspective->performCamera(shader.getShaderProg(), window);

        }
        else {

            pCameraOrtho->performCamera(shader.getShaderProg(), window);
        }

        if (particlesSpawned < maxParticles && elapsedTime.count() >= spawnInterval && !input.getSpace()) {
            P6::PhysicsParticle* newParticle = new P6::PhysicsParticle();
            newParticle->Position = P6::MyVector(0, -380, 0);
            newParticle->mass = 0.01f;
            newParticle->lifespan = dist(rd);
            newParticle->lifeRemaining = newParticle->lifespan;

            float angle = distAngle(rd) * (PI / 180.f);
            float angle_2 = distAngle_2(rd) * (PI / 180.f);
            float velocity = distForce(rd);

            P6::MyVector randomForce = P6::MyVector(
                velocity * std::cosf(angle) * std::cosf(angle_2),
                velocity * std::sinf(angle), 
                velocity * std::cosf(angle) * std::sinf(angle_2));
            newParticle->AddForce(randomForce);
            pWorld.AddParticle(newParticle);

            P6::MyVector randomColor = P6::MyVector((float)std::rand() / RAND_MAX,
                (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX);
            int randomRadius = 2 + (std::rand() % 10);
            P6::MyVector randomScale = P6::MyVector(randomRadius, randomRadius, randomRadius);

            RenderParticle* rp = new RenderParticle(newParticle, &object, randomColor, randomScale);

            RenderParticles.push_back(rp);
            particlesSpawned++;
            lastSpawnTime = currentTime;
        }

        for (std::list<RenderParticle*>::iterator i = RenderParticles.begin(); i != RenderParticles.end(); i++) {
            (*i)->Draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
