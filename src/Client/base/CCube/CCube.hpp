//
// Created by 孙策 on 2020/3/1.
//

#ifndef ENGINE_CCUBE_HPP
#define ENGINE_CCUBE_HPP

#include <glm/glm.hpp>
#include <memory>
namespace GameClient {
    class CTexture;
    class CShader;
    class CTexture;
    class CCube {
    public:
        CCube(const CTexture& texture, glm::vec3 postion, glm::vec3 size);
        void draw();
    private:
        float buffer [24][3 + 3 + 2];
        int eboBuffer[6] = { 0,1,2,2,3,0 };
        unsigned int vao[6],vbo[6],ebo[6];
        const CTexture& texture;
        std::shared_ptr<const CShader> shader;
    };
}



#endif //ENGINE_CCUBE_HPP
