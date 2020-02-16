//
// Created by SunCe on 2020/2/2.
//

#ifndef ENGINE_CDEMO_HPP
#define ENGINE_CDEMO_HPP

#include "../CShader/CShader.hpp"

namespace GameClient {
    class CDemo {
    public:
        void init();
        void draw();
    private:
        unsigned int VAO,EBO;
        unsigned int Texture;
        CShader* shader;
    };
}
#endif //ENGINE_CDEMO_HPP
