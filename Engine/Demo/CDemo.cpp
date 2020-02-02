//
// Created by SunCe on 2020/2/2.
//

#include <glad/glad.h>
#include "CDemo.h"


namespace GameClient {

    float ver[] = {
            -0.5f, 0.5f,0.0f,
            -0.5f,-0.5f,0.0f,
            0.5f,-0.5f,0.0f,
            0.5f,0.5f,0.0f
    };

    unsigned  int indices[] = {
            0,1,2,
            2,3,0
    };
    const char* vertexShader = "#version 330 core\n"
                               "layout (location = 0) in vec3 aPos;\n"
                               "\n"
                               "void main()\n"
                               "{\n"
                               "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                               "}";
    const char* fragmentShader="#version 330 core\n"
                               "out vec4 FragColor;\n"
                               "\n"
                               "void main()\n"
                               "{\n"
                               "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                               "}";


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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


        // 着色器

        // 顶点着色器
        unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(VertexShader, 1, &vertexShader, nullptr);
        glCompileShader(VertexShader);

        // 片元着色器
        unsigned  int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(FragmentShader, 1, &fragmentShader,nullptr);
        glCompileShader(FragmentShader);

        // 着色器小程序
        this->ShaderProgram = glCreateProgram();
        glAttachShader(this->ShaderProgram, VertexShader);
        glAttachShader(this->ShaderProgram, FragmentShader);
        glLinkProgram(this->ShaderProgram);

    }

    void CDemo::draw() {
        // 使用着色器
        glUseProgram(this->ShaderProgram);
        // 绑定VAO
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        // 绘制顶点
        //glDrawArrays(GL_TRIANGLES, 0, 3);
    }

}