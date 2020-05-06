//
// Created by SunCe on 2020/2/1.
//
#include <iostream>
#include "CClient.hpp"
#include "Client/base/CShader/CShader.hpp"
#include "Client/base/CTexture/CTexture.hpp"
#include "Client/base/CCube/CCube.hpp"
#include <Client/base/CCamera/CCamera.hpp>
#include <Client/base/CSkyBox/CSkyBox.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <base/CModel/CModel.hpp>
// imgui


extern std::shared_ptr<GameClient::CCamera> globalCamera;

#define MAX_CUBUE 101
#define MAX_BOX 5
namespace GameClient {
    CClient::CClient() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // MacOS 预处理
        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
    }
    CClient::~CClient() {
        glfwTerminate();
    }

    int CClient::init() {
        engineWindow = glfwCreateWindow(CClient::width, CClient::height, "GameEngine", nullptr, nullptr);
        if (engineWindow == nullptr) {
            return -1;
        }
        glfwMakeContextCurrent(this->engineWindow);
        glfwSetInputMode(this->engineWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(this->engineWindow, mouse_callback);

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            return -2;
        }
        glViewport(0 , 0, CClient::width, CClient::height);
        glEnable(GL_DEPTH_TEST);

        // 初始化页面
        this->page.Init(engineWindow);
        // 初始化世界
        this->world.init(engineWindow);

        show_page();
        show_world();
        return 0;

    }
    void CClient::processInput() {
        if (glfwGetKey(this->engineWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            show_page();
        world.process_input();
    }

    void CClient::close_client() {
        glfwSetWindowShouldClose(this->engineWindow, GLFW_TRUE);
    }

    void CClient::run() {
        // 初始化
        if(this->init())
            return;
        while(!glfwWindowShouldClose(this->engineWindow)) {
            now = glfwGetTime();
            glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (is_show_mouse == false) {
                glfwSetInputMode(this->engineWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
            else {
                glfwSetInputMode(this->engineWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }

            lightMgr.update_shader();

            if (DrawState & DRAW_WORLD) {
                world.draw();
            }


            if (DrawState & DRAW_PAGE) {
                page.Draw();
                is_show_mouse = true;
            }
            else {
                is_show_mouse = false;
            }
            glfwSwapBuffers(this->engineWindow);
            // 监听输入
            glfwPollEvents();
            // 处理输入
            this->processInput();
        }
    }
    void CClient::mouse_move(double xpos, double ypos) {
        if (DrawState & DRAW_PAGE) {
            return;
        }
        static double lastx = 0, lasty = 0;
        static float offsetx = 0 , offsety =0;
        if (lastx == 0 || lasty == 0) {
            lastx = xpos;
            lasty = ypos;
        } else {
            offsetx = xpos - lastx;
            offsety = lasty - ypos;
            lastx = xpos;
            lasty = ypos;
        }
        globalCamera->ProcessMouseMovement(offsetx, offsety);
        world.mouse_move(xpos, ypos);
    }
    void CClient::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
       
        CClient::instance().mouse_move(xpos, ypos);
    }
}