//
// Created by SunCe on 2020/2/1.
//

#include "CEngine.h"
#include "../Demo/CDemo.h"
namespace GameClient {
    CDemo demo;
    CEngine::CEngine() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
    CEngine::~CEngine() {
        glfwTerminate();
        delete this->engineWindow;
    }

    int CEngine::init() {
        engineWindow = glfwCreateWindow(CEngine::width, CEngine::height, "GameEngine", nullptr, nullptr);
        if (engineWindow == nullptr) {
            return -1;
        }
        glfwMakeContextCurrent(this->engineWindow);
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            return -2;
        }
        glViewport(0 ,0, CEngine::width, CEngine::height);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        demo.init();
        return 0;

    }
    void CEngine::processInput() {
        if(glfwGetKey(this->engineWindow, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(this->engineWindow, GLFW_TRUE);
        }
    }
    void CEngine::run() {
        // 初始化
        this->init();
        while(!glfwWindowShouldClose(this->engineWindow)) {
            glClearColor(0.0f,0.0f,0.0f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            demo.draw();
            // 交换缓冲区
            glfwSwapBuffers(this->engineWindow);
            // 监听输入
            glfwPollEvents();
            // 处理输入
            this->processInput();
        }
    }
}