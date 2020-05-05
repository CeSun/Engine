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
        // 构造函数
        CSkyBox(const std::string& skyboxname);
        // 绘制函数
        void draw();
    private:
        // 着色器指针
        std::shared_ptr<const CShader> shader;
        // 纹理数组
        std::vector<std::shared_ptr<const CTexture>> textureList;
        // 绘制对象
        unsigned int vao[6],vbo[6],ebo[6];
        // buffer
        float buffer [24][3 + 2];
        // ebo的buffer
        int eboBuffer[6] = { 0,3,2,2,1,0 };
    };
}



#endif //ENGINE_CSKEYBOX_HPP
