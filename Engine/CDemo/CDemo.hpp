//
// Created by SunCe on 2020/2/2.
//

#ifndef ENGINE_CDEMO_HPP
#define ENGINE_CDEMO_HPP

#include <Engine/CShader/CShader.hpp>

namespace GameClient {
    class CCamera;
    class CDemo {
    public:
        void init();
        void draw();
        void mouse_move(double posx,double posy);
    private:
        unsigned int VAO,EBO;
        unsigned int Texture;
        CShader* shader;
        CCamera* mainCamera = nullptr;
    };
}
#endif //ENGINE_CDEMO_HPP
