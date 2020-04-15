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
// imgui



#define MAX_CUBUE 101
#define MAX_BOX 5
namespace GameClient {
    std::shared_ptr<CCube> cube[MAX_CUBUE];
    std::shared_ptr<CCube> box[MAX_BOX];
    std::shared_ptr<CCamera> camera;
    std::shared_ptr<CSkyBox> skybox;
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

    CClient& CClient::intance() {
        static CClient Engine;
        return Engine;
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
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glEnable(GL_DEPTH_TEST);

        std::shared_ptr<const CTexture> roTexture1 = texturemgr.add_texture("resource/texture/TDtps0247.jpg");
        std::shared_ptr<const CTexture> roTexture2 = texturemgr.add_texture("resource/texture/container.jpg");

        skybox = std::make_shared<CSkyBox>("pm");

        for (int i = 0 ; i < MAX_CUBUE - 2 ; i ++ ) {
            cube[i] = std::make_shared<CCube>(*roTexture1,glm::vec3(0.0 + (i % 10) * 20 ,0.0,0.0 + (i / 10) * 20),glm::vec3(10,1,10));
        }
        box[0] = std::make_shared<CCube>(*roTexture2, glm::vec3(82.0,6.0,77.0),glm::vec3(5,5,5));
        box[1] = std::make_shared<CCube>(*roTexture2, glm::vec3(87.0,16.0,77.0),glm::vec3(5,5,5));
        box[2] = std::make_shared<CCube>(*roTexture2, glm::vec3(92.0,6.0,77.0),glm::vec3(5,5,5));
        camera = std::make_shared<CCamera>(glm::vec3(100.0,100.0,40.0));
        cube[MAX_CUBUE - 1] = std::make_shared<CCube>(*roTexture1, glm::vec3(100, 130, 200), glm::vec3(1, 1, 1));
        cube[MAX_CUBUE - 2] = std::make_shared<CCube>(*roTexture1, glm::vec3(40, 100, 50), glm::vec3(1, 1, 1));


        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)width / (float)height, 0.1f,  15000.0f);
        glm::mat4 view = camera->GetViewMatrix();
        glm::mat4 worldarea(1.0);
        worldarea = glm::scale(worldarea, glm::vec3(1.0, 1.0, 0.5));
        worldarea = glm::translate(worldarea, glm::vec3(0.0f, 0.0f, -0.25f));
        std::shared_ptr<CLight> light = std::make_shared<CLight>(CLight::LIGHTTYPE_POINT,glm::vec3(0.4, 0.0, 0.0), glm::vec3(100, 130, 200));
        std::shared_ptr<CLight> light2 = std::make_shared<CLight>(glm::vec3(1.0, 1.0, 1.0), glm::vec3(40, 20, 40), glm::vec3(0.6,-1.0,0.0), glm::cos(glm::radians(40.0f)), glm::cos(glm::radians(17.5f)));
        std::shared_ptr<CLight> light3 = std::make_shared<CLight>(glm::vec3(0.4, 0.4, 0.4), glm::vec3(-1.0, -2.0, 0.0));
        std::shared_ptr<CLight> light4 = std::make_shared<CLight>(CLight::LIGHTTYPE_POINT, glm::vec3(0.0, 0.0, 0.4), glm::vec3(50, 24, 200));
        lightMgr.add_light("light", light);
        lightMgr.add_light("light2", light2);
        lightMgr.add_light("light3", light3);
        lightMgr.add_light("light4", light4);
        shadermgr.setMat4("model",glm::mat4(1.0));
        shadermgr.setMat4("projection", projection);
        shadermgr.setMat4("view", view);
        shadermgr.setMat4("worldarea", worldarea);
        shadermgr.setInt("texture1", 0);
        return 0;

    }
    void CClient::processInput() {
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
        //demo.inputKey();
    }

    void CClient::run() {
        // 初始化
        if(this->init())
            return;
        while(!glfwWindowShouldClose(this->engineWindow)) {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glm::mat4 view = camera->GetViewMatrix();
            shadermgr.setMat4("view", view);
            shadermgr.setVec3("viewPos", camera->Position);
            lightMgr.update_shader();
            skybox->draw();
            for(int i = 0 ; i < MAX_CUBUE ; i ++) {
                if(cube[i] != nullptr)
                    cube[i]->draw();
            }
            for(int i = 0 ; i < MAX_BOX ; i ++) {
                if(box[i] != nullptr)
                    box[i]->draw();
            }
            world.draw();
            // 交换缓冲区
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
        camera->ProcessMouseMovement(offsetx, offsety);
    }
    void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
        CClient::intance().mouse_move(xpos, ypos);
    }
}