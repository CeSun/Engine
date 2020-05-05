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
        this->page.Init();

        return 0;

    }
    void CClient::processInput() {
        /*
        if(glfwGetKey(this->engineWindow, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(this->engineWindow, GLFW_TRUE);
        if (glfwGetKey(this->engineWindow, GLFW_KEY_W) == GLFW_PRESS)
            camera->ProcessKeyboard(FORWARD, 0.05);
        if (glfwGetKey(this->engineWindow, GLFW_KEY_S) == GLFW_PRESS)
            camera->ProcessKeyboard(BACKWARD, 0.05);
        if (glfwGetKey(this->engineWindow, GLFW_KEY_A) == GLFW_PRESS)
            camera->ProcessKeyboard(LEFT, 0.05);
        if (glfwGetKey(this->engineWindow, GLFW_KEY_D) == GLFW_PRESS)
            camera->ProcessKeyboard(RIGHT, 0.05);
         */
        //demo.inputKey();
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
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // glm::mat4 view = camera->GetViewMatrix();
            // shadermgr.setMat4("view", view);
            // shadermgr.setVec3("viewPos", camera->Position);
            // lightMgr.update_shader();
            // skybox->draw();
            /*
            for(int i = 0 ; i < MAX_CUBUE ; i ++) {
                if (cube[i] != nullptr)
                    cube[i]->draw();
            }
            for(int i = 0 ; i < MAX_BOX ; i ++) {
                if (box[i] != nullptr)
                    box[i]->draw();
            }*/
            // model2->Draw(shader);
            // world.draw();
            // model->Draw(shader);
            // 交换缓冲区

            if (DrawState & DRAW_PAGE) {
                page.Draw();
            }
            if (DrawState & DRAW_WORLD) {
                world.draw();
            }
            glfwSwapBuffers(this->engineWindow);
            // 监听输入
            glfwPollEvents();
            // 处理输入
            this->processInput();
        }
    }
    void CClient::mouse_move(double xpos, double ypos) {
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
        // camera->ProcessMouseMovement(offsetx, offsety);
    }
    void CClient::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
        CClient::instance().mouse_move(xpos, ypos);
    }
}