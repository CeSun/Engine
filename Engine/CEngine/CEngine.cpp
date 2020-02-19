//
// Created by SunCe on 2020/2/1.
//
#include <iostream>
#include "CEngine.hpp"
#include <Engine/CDemo/CDemo.hpp>
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
    }

    CEngine& CEngine::getIntance() {
        static CEngine Engine;
        return Engine;
    }
    int CEngine::init() {
        engineWindow = glfwCreateWindow(CEngine::width, CEngine::height, "GameEngine", nullptr, nullptr);
        if (engineWindow == nullptr) {
            return -1;
        }
        glfwMakeContextCurrent(this->engineWindow);
        glfwSetInputMode(this->engineWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(this->engineWindow, mouse_callback);

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
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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

    void CEngine::mouse_move(double xpos,double ypos) {
        demo.mouse_move(xpos,ypos);
    }
    void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
        CEngine::getIntance().mouse_move(xpos,ypos);
    }
}