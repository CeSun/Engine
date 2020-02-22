//
// Created by SunCe on 2020/2/1.
//

#ifndef ENGINE_CCLIENT_HPP
#define ENGINE_CCLIENT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GameClient {
    class CCamera;
    class CClient {
    public:
        static CClient& getIntance();
        virtual ~CClient();
        void run ();
    private:        // methods
        CClient();
        int init();
        void processInput();
        void mouse_move(double x,double y);

    private:             // attribute
        GLFWwindow* engineWindow = nullptr;
        const static int major = 3;
        const static int minor = 3;
        const static int width = 1024;
        const static int height = 768;
        friend void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    };

    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
}

#endif //ENGINE_CCLIENT_HPP
