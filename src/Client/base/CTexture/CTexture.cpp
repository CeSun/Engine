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
    CTexture::CTexture(const std::string& filename) {
        int nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(filename.c_str(),&width, &height, &nrChannels,0);
        // std::cout << nrChannels << std::endl;
        if (data) {
            glGenTextures(1, &this->id);
            glBindTexture(GL_TEXTURE_2D, this->id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            GLenum format;
            switch (nrChannels) {
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
            default:
                format = GL_RGB;
                break;
            }
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cout << "load " <<filename << "faild" <<std::endl;
        }
    }
    CTexture::~CTexture() {

    }
    unsigned int CTexture::get_id() const {
        return this->id;
    }
}