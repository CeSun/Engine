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
        /// methods
        int init();
        void processInput();
        // attribute
        GLFWwindow* engineWindow = nullptr;

        const static int major = 3;
        const static int minor = 3;
        const static int width = 800;
        const static int height = 600;
    };
}

#endif //ENGINE_CENGINE_H
