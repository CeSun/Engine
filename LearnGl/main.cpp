#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Texture.h"
using namespace std;
const unsigned short width = 800;
const unsigned short height = 600;
const char* title = "LearnOpenGL";


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width,height,title, nullptr,nullptr);
    if(window == nullptr) {
        cout << "窗口创建失败" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "gl库加载失败" << endl;
        return -1;
    }


    Texture *texture = new Texture();
    texture->init();
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        texture->draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete texture;
    glfwTerminate();

    return 0;
}
