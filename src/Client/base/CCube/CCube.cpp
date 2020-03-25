//
// Created by 孙策 on 2020/3/1.
//

#include <Client/base/CTexture/CTexture.hpp>
#include <glad/glad.h>
#include "CCube.hpp"
#include <Client/base/CShader/CShader.hpp>
#include <iostream>
namespace GameClient {
    CCube::CCube(const CTexture& texture, glm::vec3 postion, glm::vec3 size,const CShader& shader):
        shader(shader), texture(texture){
        this -> buffer[0][0] = postion.x + size.x;
        this -> buffer[0][1] = postion.y - size.y;
        this -> buffer[0][2] = postion.z + size.z;
        this -> buffer[0][3] = 0.0;
        this -> buffer[0][4] = 1.0;

        this -> buffer[1][0] = postion.x + size.x;
        this -> buffer[1][1] = postion.y - size.y;
        this -> buffer[1][2] = postion.z - size.z;
        this -> buffer[1][3] = 0.0;
        this -> buffer[1][4] = 0.0;

        this -> buffer[2][0] = postion.x + size.x;
        this -> buffer[2][1] = postion.y + size.y;
        this -> buffer[2][2] = postion.z - size.z;
        this -> buffer[2][3] = 1.0;
        this -> buffer[2][4] = 0.0;

        this -> buffer[3][0] = postion.x + size.x;
        this -> buffer[3][1] = postion.y + size.y;
        this -> buffer[3][2] = postion.z + size.z;
        this -> buffer[3][3] = 1.0;
        this -> buffer[3][4] = 1.0;

        // 右面
        this -> buffer[4][0] = postion.x + size.x;
        this -> buffer[4][1] = postion.y + size.y;
        this -> buffer[4][2] = postion.z + size.z;
        this -> buffer[4][3] = 0.0;
        this -> buffer[4][4] = 1.0;

        this -> buffer[5][0] = postion.x + size.x;
        this -> buffer[5][1] = postion.y + size.y;
        this -> buffer[5][2] = postion.z - size.z;
        this -> buffer[5][3] = 0.0;
        this -> buffer[5][4] = 0.0;

        this -> buffer[6][0] = postion.x - size.x;
        this -> buffer[6][1] = postion.y + size.y;
        this -> buffer[6][2] = postion.z - size.z;
        this -> buffer[6][3] = 1.0;
        this -> buffer[6][4] = 0.0;

        this -> buffer[7][0] = postion.x - size.x;
        this -> buffer[7][1] = postion.y + size.y;
        this -> buffer[7][2] = postion.z + size.z;
        this -> buffer[7][3] = 1.0;
        this -> buffer[7][4] = 1.0;

        // 后面
        this -> buffer[8][0] = postion.x - size.x;
        this -> buffer[8][1] = postion.y + size.y;
        this -> buffer[8][2] = postion.z + size.z;
        this -> buffer[8][3] = 0.0;
        this -> buffer[8][4] = 1.0;

        this -> buffer[9][0] = postion.x - size.x;
        this -> buffer[9][1] = postion.y + size.y;
        this -> buffer[9][2] = postion.z - size.z;
        this -> buffer[9][3] = 0.0;
        this -> buffer[9][4] = 0.0;

        this -> buffer[10][0] = postion.x - size.x;
        this -> buffer[10][1] = postion.y - size.y;
        this -> buffer[10][2]= postion.z - size.z;
        this -> buffer[10][3] = 1.0;
        this -> buffer[10][4] = 0.0;

        this -> buffer[11][0] = postion.x - size.x;
        this -> buffer[11][1] = postion.y - size.y;
        this -> buffer[11][2] = postion.z + size.z;
        this -> buffer[11][3] = 1.0;
        this -> buffer[11][4] = 1.0;

        // 左面
        this -> buffer[12][0] = postion.x - size.x;
        this -> buffer[12][1] = postion.y - size.y;
        this -> buffer[12][2] = postion.z + size.z;
        this -> buffer[12][3] = 0.0;
        this -> buffer[12][4] = 1.0;

        this -> buffer[13][0] = postion.x - size.x;
        this -> buffer[13][1] = postion.y - size.y;
        this -> buffer[13][2] = postion.z - size.z;
        this -> buffer[13][3] = 0.0;
        this -> buffer[13][4] = 0.0;

        this -> buffer[14][0] = postion.x + size.x;
        this -> buffer[14][1] = postion.y - size.y;
        this -> buffer[14][2] = postion.z - size.z;
        this -> buffer[14][3] = 1.0;
        this -> buffer[14][4] = 0.0;

        this -> buffer[15][0] = postion.x + size.x;
        this -> buffer[15][1] = postion.y - size.y;
        this -> buffer[15][2] = postion.z + size.z;
        this -> buffer[15][3] = 1.0;
        this -> buffer[15][4] = 1.0;

        // 上面
        this -> buffer[16][0] = postion.x - size.x;
        this -> buffer[16][1] = postion.y - size.y;
        this -> buffer[16][2] = postion.z + size.z;
        this -> buffer[16][3] = 0.0;
        this -> buffer[16][4] = 1.0;

        this -> buffer[17][0] = postion.x + size.x;
        this -> buffer[17][1] = postion.y - size.y;
        this -> buffer[17][2] = postion.z + size.z;
        this -> buffer[17][3] = 0.0;
        this -> buffer[17][4] = 0.0;

        this -> buffer[18][0] = postion.x + size.x;
        this -> buffer[18][1] = postion.y + size.y;
        this -> buffer[18][2] = postion.z + size.z;
        this -> buffer[18][3] = 1.0;
        this -> buffer[18][4] = 0.0;

        this -> buffer[19][0] = postion.x - size.x;
        this -> buffer[19][1] = postion.y + size.y;
        this -> buffer[19][2] = postion.z + size.z;
        this -> buffer[19][3] = 1.0;
        this -> buffer[19][4] = 1.0;

        //下面

        this -> buffer[20][0] = postion.x + size.x;
        this -> buffer[20][1] = postion.y - size.y;
        this -> buffer[20][2] = postion.z - size.z;
        this -> buffer[20][3] = 0.0;
        this -> buffer[20][4] = 1.0;

        this -> buffer[21][0] = postion.x - size.x;
        this -> buffer[21][1] = postion.y - size.y;
        this -> buffer[21][2] = postion.z - size.z;
        this -> buffer[21][3] = 0.0;
        this -> buffer[21][4] = 0.0;

        this -> buffer[22][0] = postion.x - size.x;
        this -> buffer[22][1] = postion.y + size.y;
        this -> buffer[22][2] = postion.z - size.z;
        this -> buffer[22][3] = 1.0;
        this -> buffer[22][4] = 0.0;

        this -> buffer[23][0] = postion.x + size.x;
        this -> buffer[23][1] = postion.y + size.y;
        this -> buffer[23][2] = postion.z - size.z;
        this -> buffer[23][3] = 1.0;
        this -> buffer[23][4] = 1.0;
        // vbo
        glGenBuffers(6, this->vbo);
        glGenBuffers(6, this->ebo);
        glGenVertexArrays(6, this->vao);

        for (int i = 0 ; i < 6 ; i++) {
            glBindBuffer(GL_ARRAY_BUFFER, this->vbo[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(this->buffer[i]) * 4 , this->buffer[i * 4] , GL_STATIC_DRAW);
            glBindVertexArray(this->vao[i]);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo[i]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->eboBuffer), eboBuffer, GL_STATIC_DRAW);
        }


    }
    void CCube::draw() {
        for (int i = 0 ; i < 6 ; i++) {
            shader.use();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture.get_id());
            glBindVertexArray(this->vao[i]);
            glBindBuffer(GL_ARRAY_BUFFER, this->vbo[i]);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo[i]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
}