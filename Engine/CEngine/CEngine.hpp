//
// Created by SunCe on 2020/2/1.
//

#ifndef ENGINE_CENGINE_HPP
#define ENGINE_CENGINE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GameClient {
    class CCamera;
    class CEngine {
    public:
        static CEngine& getIntance();
        virtual ~CEngine();
        void run ();
    private:        // methods
        CEngine();
        int init();
        void processInput();
        void mouse_move(double x,double y);

    private:             // attribute
        GLFWwindow* engineWindow = nullptr;
        const static int major = 3;
        const static int minor = 3;
        const static int width = 800;
        const static int height = 600;
        friend void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    };

    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
}

#endif //ENGINE_CENGINE_HPP
