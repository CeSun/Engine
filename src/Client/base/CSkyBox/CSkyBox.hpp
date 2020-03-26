//
// Created by SunCe on 2020/3/14.
//

#ifndef ENGINE_CSKEYBOX_HPP
#define ENGINE_CSKEYBOX_HPP

#include <string>
#include <vector>
#include <memory>
#include <Client/base/CShader/CShader.hpp>
#include <Client/base/CTexture/CTexture.hpp>

namespace GameClient {
    class CSkyBox {
    public:
        CSkyBox(const std::string& skyboxname);
        void draw();
    private:
        std::shared_ptr<const CShader> shader;
        std::vector<std::shared_ptr<const CTexture>> textureList;
        unsigned int vao[6],vbo[6],ebo[6];
        float buffer [24][3 + 2];
        int eboBuffer[6] = { 0,3,2,2,1,0 };
    };
}



#endif //ENGINE_CSKEYBOX_HPP
