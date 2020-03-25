//
// Created by SunCe on 2020/3/14.
//

#ifndef ENGINE_CSKEYBOX_HPP
#define ENGINE_CSKEYBOX_HPP

#include <string>
#include <vector>
#include <memory>
namespace GameClient {
    class CShader;
    class CTexture;
    class CSkyBox {
    public:
        CSkyBox(const std::string& skyboxname,const CShader& shader);
        void draw();
    private:
        const CShader& shader;
        std::vector<const CTexture*> textureList;
        unsigned int vao[6],vbo[6],ebo[6];
        float buffer [24][3 + 2];
        int eboBuffer[6] = { 0,3,2,2,1,0 };
    };
}



#endif //ENGINE_CSKEYBOX_HPP
