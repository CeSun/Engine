//
// Created by SunCe on 2020/2/2.
//

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <src/Client/CCamera/CCamera.hpp>
#include "CDemo.hpp"
#include <memory>
namespace GameClient {

    float ver[] = {
            -1.0f, 1.0f,0.0f, 0.0f, 1.0f,
            -1.0f,-1.0f,0.0f, 0.0f, 0.0f,
            1.0f,-1.0f,0.0f, 1.0f, 0.0f,
            1.0f,1.0f,0.0f, 1.0f, 1.0f
    };

    unsigned  int indices[] = {
            0,1,2,
            2,3,0
    };

    void CDemo::mouse_move(double xpos,double ypos) {
        static double lastX, lastY;
        float deltaX = xpos - lastX;
        float deltaY = ypos - lastY;
        lastX = xpos;
        lastY = ypos;

        this->mainCamera->setPitch(float(this->mainCamera->getPitch() - deltaY *0.01));
        this->mainCamera->setYaw(float(this->mainCamera->getYaw() - deltaX * 0.01));
        this->mainCamera->upDateCameraMatrix();
        std::cout << this->mainCamera->getPitch() <<  "" << this->mainCamera->getYaw()<<std::endl;
    }


    float skybox [] = {
            200,-200,200.0f, 0.0f,1.0f,
            200,-200,-200,1.0f,1.0f,
            -200,-200,-200,1.0f,0.0f,
            -200,-200,200,0.0f,0.0f
    };
    unsigned int skyboxvbo[6],texture[6],skyboxvao[6];
    std::shared_ptr<CShader> skyboxShader[6] ;
    void CDemo::init() {
        for(int i = 0 ; i < 6 ; i ++) {
            skyboxShader[i] = std::make_shared<CShader>(*(new CShader("./shader/shader.vs","./shader/shader.fs")));
        }


        // 申请VAO对象
        glGenVertexArrays(2, skyboxvao);


        // 申请VBO对象
        glGenBuffers(1, &VBO);
        // 绑定VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // 上传顶点数据至显存BUFFER
        glBufferData(GL_ARRAY_BUFFER, sizeof(ver), ver, GL_STATIC_DRAW);


        glGenBuffers(1, &skyboxvbo[0]);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxvbo[0]);
        // 上传顶点数据至显存BUFFER
        glBufferData(GL_ARRAY_BUFFER, sizeof(skybox), skybox, GL_STATIC_DRAW);

        // 绑定VAO
        glBindVertexArray(skyboxvao[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5* sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5* sizeof(float), (void *) (3* sizeof(float)));
        glEnableVertexAttribArray(1);





        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        this->shader = new CShader("./shader/shader.vs","./shader/shader.fs");

        mainCamera = new CCamera(glm::vec3(0,0,0.0f),0.0,0.0,glm::vec3(0,1.0f,0));
        // 矩阵
        glm::mat4 trans(1.0f);
        glm::mat4 modelMat(1.0f);
        glm::mat4 viewMat(1.0f);
        viewMat = mainCamera->getViewMatrix();
        glm::mat4 projMat(1.0f);
        projMat = glm::perspective(glm::radians(55.0f),800.0f/600.0f,0.001f,400.0f);
        this->shader->use();
        this->shader->setMat4("modelMat",modelMat);
        this->shader->setMat4("viewMat",viewMat);
        this->shader->setMat4("projMat",projMat);

        glGenTextures(1, &this->Texture);
        glBindTexture(GL_TEXTURE_2D, this->Texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        int width, height, nrChannels;
        unsigned char* data = stbi_load("resource/container.jpg",&width, &height, &nrChannels,0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            data = new unsigned char[14];
            // 红
            data[0] = 0;
            data[1] = 0;
            data[2] = 0;
            // 白
            data[3] = 255;
            data[4] = 0;
            data[5] = 255;
            data[6] = 0;
            data[7] = 0;
            data[8] = 255;
            data[9] =  0;
            data[10] = 255;
            data[11] = 0;
            data[12] = 0;
            data[13] = 0;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            delete[] data;
        }


        stbi_set_flip_vertically_on_load(true);
        glGenTextures(1, &texture[0]);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        skyboxShader[0]->use();
        data = stbi_load("resource/skybox/pm_dn.jpg",&width, &height, &nrChannels,0);
        if (data) {
            std::cout<< "load ok" << std::endl;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }else {

            std::cout<< "load error" << std::endl;
        }
        glGenerateMipmap(GL_TEXTURE_2D);

        glGenTextures(1, &texture[1]);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        skyboxShader[0]->use();
        data = stbi_load("resource/skybox/pm_ft.jpg",&width, &height, &nrChannels,0);
        if (data) {
            std::cout<< "load ok" << std::endl;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }else {

            std::cout<< "load error" << std::endl;
        }
        glGenerateMipmap(GL_TEXTURE_2D);

        glGenTextures(1, &texture[2]);
        glBindTexture(GL_TEXTURE_2D, texture[2]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        skyboxShader[0]->use();
        data = stbi_load("resource/skybox/pm_bk.jpg",&width, &height, &nrChannels,0);
        if (data) {
            std::cout<< "load ok" << std::endl;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }else {

            std::cout<< "load error" << std::endl;
        }
        glGenerateMipmap(GL_TEXTURE_2D);

        glGenTextures(1, &texture[3]);
        glBindTexture(GL_TEXTURE_2D, texture[3]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        skyboxShader[0]->use();
        data = stbi_load("resource/skybox/pm_lf.jpg",&width, &height, &nrChannels,0);
        if (data) {
            std::cout<< "load ok" << std::endl;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }else {

            std::cout<< "load error" << std::endl;
        }
        glGenerateMipmap(GL_TEXTURE_2D);

        glGenTextures(1, &texture[4]);
        glBindTexture(GL_TEXTURE_2D, texture[4]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        skyboxShader[0]->use();
        data = stbi_load("resource/skybox/pm_rt.jpg",&width, &height, &nrChannels,0);
        if (data) {
            std::cout<< "load ok" << std::endl;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }else {

            std::cout<< "load error" << std::endl;
        }
        glGenerateMipmap(GL_TEXTURE_2D);

        glGenTextures(1, &texture[5]);
        glBindTexture(GL_TEXTURE_2D, texture[5]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        skyboxShader[0]->use();
        data = stbi_load("resource/skybox/pm_up.jpg",&width, &height, &nrChannels,0);
        if (data) {
            std::cout<< "load ok" << std::endl;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }else {

            std::cout<< "load error" << std::endl;
        }
        glGenerateMipmap(GL_TEXTURE_2D);

    }

    void CDemo::draw() {


        glm::mat4 modelMat(1.0f);
        glm::mat4 viewMat(1.0f);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        // 使用着色器
        this->shader->use();
        viewMat = mainCamera->getViewMatrix();
        this->shader->setMat4("viewMat",viewMat);
        this->shader->setMat4("modelMat",modelMat);

        glBindVertexArray(skyboxvao[0]);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxvbo[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
         glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);


        modelMat = glm::rotate(modelMat,glm::radians(90.0f),glm::vec3(0.0f,1.0,0.0));
        modelMat = glm::rotate(modelMat,glm::radians(90.0f),glm::vec3(0.0f,0.0,1.0));

        this->shader->setMat4("modelMat",modelMat);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glBindVertexArray(skyboxvao[0]);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxvbo[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        modelMat = glm::rotate(modelMat,glm::radians(90.0f),glm::vec3(1.0f,0.0,0.0));
        this->shader->setMat4("modelMat",modelMat);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[3]);
        glBindVertexArray(skyboxvao[0]);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxvbo[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        modelMat = glm::rotate(modelMat,glm::radians(90.0f),glm::vec3(1.0f,0.0,0.0));
        this->shader->setMat4("modelMat",modelMat);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[2]);
        glBindVertexArray(skyboxvao[0]);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxvbo[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        modelMat = glm::rotate(modelMat,glm::radians(90.0f),glm::vec3(1.0f,0.0,0.0));
        this->shader->setMat4("modelMat",modelMat);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[4]);
        glBindVertexArray(skyboxvao[0]);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxvbo[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);


        modelMat = glm::rotate(modelMat,glm::radians(90.0f),glm::vec3(0.0f,0.0,1.0));
        this->shader->setMat4("modelMat",modelMat);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[5]);
        glBindVertexArray(skyboxvao[0]);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxvbo[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

    }

}