//
// Created by dust on 2019/12/16.
//

#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H

#include "shader_s.h"

class Texture {
private:
    Shader* shader;
    unsigned int VBO, VAO, EBO;
    unsigned int texture1,texture2;

public:
    Texture(){};
    void init();
    void draw();
    ~Texture();
};


#endif //ENGINE_TEXTURE_H
