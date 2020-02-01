//
// Created by SunCe on 2020/2/1.
//

#ifndef ENGINE_CENGINE_H
#define ENGINE_CENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GameClient {
    class CEngine {
    public:
        CEngine ();
        virtual ~CEngine();
        void run ();
    private:
        int init();
        GLFWwindow* engineWindow = nullptr;
    };
}

#endif //ENGINE_CENGINE_H
