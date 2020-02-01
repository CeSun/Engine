//
// Created by SunCe on 2020/2/1.
//

#include "CEngine.h"

namespace GameClient {
    CEngine::CEngine() {

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
    CEngine::~CEngine() {
        glfwTerminate();
        delete this->engineWindow;
    }

    int CEngine::init() {
        engineWindow = glfwCreateWindow(800, 600, "GameEngine", nullptr, nullptr);
        if (engineWindow == nullptr) {
            return -1;
        }
        glfwMakeContextCurrent(this->engineWindow);
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            return -2;
        }
        return 0;

    }
    void CEngine::run() {
        this->init();
        while(!glfwWindowShouldClose(this->engineWindow)) {
            glClearColor(0.0f,0.0f,0.0f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glfwSwapBuffers(this->engineWindow);
            glfwPollEvents();
        }
    }


}