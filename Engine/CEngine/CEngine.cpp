//
// Created by SunCe on 2020/2/1.
//

#include "CEngine.h"

namespace GameClient {
    void test();
    unsigned int VAO;
    unsigned int shaderProgram;
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
        test();
        while(!glfwWindowShouldClose(this->engineWindow)) {
            glClearColor(0.0f,0.0f,0.0f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            // 交换缓冲区
            glfwSwapBuffers(this->engineWindow);
            // 监听输入
            glfwPollEvents();
            // 处理输入
            this->processInput();
        }

        glDeleteProgram(shaderProgram);
    }


    float v[] = {
            0.0f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
    };
    const char* vertexShaderSource= "#version 330 core\n"
                              "layout (location = 0) in vec3 aPos;\n"
                              "\n"
                              "void main()\n"
                              "{\n"
                              "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                              "}";
    const char* fragmentShaderSource= "#version 330 core\n"
                             "out vec4 FragColor;\n"
                             "\n"
                             "void main()\n"
                             "{\n"
                             "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                             "} ";
    void test() {
        unsigned int VBO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(v), &v, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    }
}