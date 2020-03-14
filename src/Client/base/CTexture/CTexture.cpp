//
// Created by 孙策 on 2020/2/23.
//

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "CTexture.hpp"
#include <iostream>
#include <string>
namespace GameClient {
    CTexture::CTexture(std::string filename) {
        int nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(filename.c_str(),&width, &height, &nrChannels,0);
        if (data) {
            glGenTextures(1, &this->id);
            glBindTexture(GL_TEXTURE_2D, this->id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cout << "load " <<filename << "faild" <<std::endl;
        }
    }
    CTexture::~CTexture() {

    }
    unsigned int CTexture::getTextureId() const {
        return this->id;
    }
}