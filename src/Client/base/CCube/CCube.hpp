//
// Created by 孙策 on 2020/3/1.
//

#ifndef ENGINE_CCUBE_HPP
#define ENGINE_CCUBE_HPP

#include <Client/base/CTexture/CTexture.hpp>
#include <glm/glm.hpp>

namespace GameClient {
    class CCube {
    public:
        CCube(const CTexture& texture, glm::vec3 postion, glm::vec3 size);
        void draw();
    private:
        float buffer [8 * (3 + 2)];
        unsigned int Texture;
    };
}



#endif //ENGINE_CCUBE_HPP
