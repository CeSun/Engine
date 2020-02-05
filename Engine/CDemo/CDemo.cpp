//
// Created by SunCe on 2020/2/2.
//

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "CDemo.h"


namespace GameClient {

    float ver[] = {
            -0.5f, 0.5f,0.0f, 0.0f, 1.0f,
            -0.5f,-0.5f,0.0f, 0.0f, 0.0f,
            0.5f,-0.5f,0.0f, 1.0f, 0.0f,
            0.5f,0.5f,0.0f, 1.0f, 1.0f
    };

    unsigned  int indices[] = {
            0,1,2,
            2,3,0
    };

    void CDemo::init() {

        // 申请VAO对象
        glGenVertexArrays(1, &this->VAO);
        // 绑定VAO
        glBindVertexArray(this->VAO);

        unsigned int VBO;
        // 申请VBO对象
        glGenBuffers(1, &VBO);
        // 绑定VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // 上传顶点数据至显存BUFFER
        glBufferData(GL_ARRAY_BUFFER, sizeof(ver), ver, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5* sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5* sizeof(float), (void *) (3* sizeof(float)));
        glEnableVertexAttribArray(1);



        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        this->shader = new CShader("./shader/shader.vs","./shader/shader.fs");

        // 矩阵
        glm::mat4 trans(1.0f);
        glm::mat4 modelMat(1.0f);
        modelMat = glm::rotate(modelMat, glm::radians(-70.0f), glm::vec3(1.0f,0.0f,0.0f));
        glm::mat4 viewMat(1.0f);
        viewMat = glm::translate(viewMat, glm::vec3(0,0,-3.0f));
        glm::mat4 projMat(1.0f);
        projMat = glm::perspective(glm::radians(45.0f),800.0f/600.0f,0.1f,100.0f);


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

        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void CDemo::draw() {

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->Texture);
        // 使用着色器
        this->shader->use();
        // 绑定VAO
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        // 绘制顶点
        //glDrawArrays(GL_TRIANGLES, 0, 3);
    }

}