//
// Created by 孙策 on 2020/3/1.
//

#include <iostream>
#include <glad/glad.h>
#include <Client/base/CShader/CShader.hpp>
#include <Client/base/CTexture/CTexture.hpp>
#include <Client/CClient/CClient.hpp>
#include "CCube.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace GameClient {
    CCube::CCube(const CTexture& texture, glm::vec3 postion, glm::vec3 size):texture(texture) {
        shader = CClient::instance().get_shadermgr().add_shader("resource/shader/cube/shader.vs", "resource/shader/cube/shader.fs");
        model = glm::mat4(1.0);
        model = glm::translate(model, postion);

        postion = glm::vec3(0.0);
        this -> buffer[0][0] = postion.x + size.x;
        this -> buffer[0][1] = postion.y - size.y;
        this -> buffer[0][2] = postion.z + size.z;
        this -> buffer[0][6] = 0.0;
        this -> buffer[0][7] = 1.0;

        this -> buffer[1][0] = postion.x + size.x;
        this -> buffer[1][1] = postion.y - size.y;
        this -> buffer[1][2] = postion.z - size.z;
        this -> buffer[1][6] = 0.0;
        this -> buffer[1][7] = 0.0;

        this -> buffer[2][0] = postion.x + size.x;
        this -> buffer[2][1] = postion.y + size.y;
        this -> buffer[2][2] = postion.z - size.z;
        this -> buffer[2][6] = 1.0;
        this -> buffer[2][7] = 0.0;

        this -> buffer[3][0] = postion.x + size.x;
        this -> buffer[3][1] = postion.y + size.y;
        this -> buffer[3][2] = postion.z + size.z;
        this -> buffer[3][6] = 1.0;
        this -> buffer[3][7] = 1.0;

        // 右面
        this -> buffer[4][0] = postion.x + size.x;
        this -> buffer[4][1] = postion.y + size.y;
        this -> buffer[4][2] = postion.z + size.z;
        this -> buffer[4][6] = 0.0;
        this -> buffer[4][7] = 1.0;

        this -> buffer[5][0] = postion.x + size.x;
        this -> buffer[5][1] = postion.y + size.y;
        this -> buffer[5][2] = postion.z - size.z;
        this -> buffer[5][6] = 0.0;
        this -> buffer[5][7] = 0.0;

        this -> buffer[6][0] = postion.x - size.x;
        this -> buffer[6][1] = postion.y + size.y;
        this -> buffer[6][2] = postion.z - size.z;
        this -> buffer[6][6] = 1.0;
        this -> buffer[6][7] = 0.0;

        this -> buffer[7][0] = postion.x - size.x;
        this -> buffer[7][1] = postion.y + size.y;
        this -> buffer[7][2] = postion.z + size.z;
        this -> buffer[7][6] = 1.0;
        this -> buffer[7][7] = 1.0;

        // 后面
        this -> buffer[8][0] = postion.x - size.x;
        this -> buffer[8][1] = postion.y + size.y;
        this -> buffer[8][2] = postion.z + size.z;
        this -> buffer[8][6] = 0.0;
        this -> buffer[8][7] = 1.0;

        this -> buffer[9][0] = postion.x - size.x;
        this -> buffer[9][1] = postion.y + size.y;
        this -> buffer[9][2] = postion.z - size.z;
        this -> buffer[9][6] = 0.0;
        this -> buffer[9][7] = 0.0;

        this -> buffer[10][0] = postion.x - size.x;
        this -> buffer[10][1] = postion.y - size.y;
        this -> buffer[10][2]= postion.z - size.z;
        this -> buffer[10][6] = 1.0;
        this -> buffer[10][7] = 0.0;

        this -> buffer[11][0] = postion.x - size.x;
        this -> buffer[11][1] = postion.y - size.y;
        this -> buffer[11][2] = postion.z + size.z;
        this -> buffer[11][6] = 1.0;
        this -> buffer[11][7] = 1.0;

        // 左面
        this -> buffer[12][0] = postion.x - size.x;
        this -> buffer[12][1] = postion.y - size.y;
        this -> buffer[12][2] = postion.z + size.z;
        this -> buffer[12][6] = 0.0;
        this -> buffer[12][7] = 1.0;

        this -> buffer[13][0] = postion.x - size.x;
        this -> buffer[13][1] = postion.y - size.y;
        this -> buffer[13][2] = postion.z - size.z;
        this -> buffer[13][6] = 0.0;
        this -> buffer[13][7] = 0.0;

        this -> buffer[14][0] = postion.x + size.x;
        this -> buffer[14][1] = postion.y - size.y;
        this -> buffer[14][2] = postion.z - size.z;
        this -> buffer[14][6] = 1.0;
        this -> buffer[14][7] = 0.0;

        this -> buffer[15][0] = postion.x + size.x;
        this -> buffer[15][1] = postion.y - size.y;
        this -> buffer[15][2] = postion.z + size.z;
        this -> buffer[15][6] = 1.0;
        this -> buffer[15][7] = 1.0;

        // 上面
        this -> buffer[16][0] = postion.x - size.x;
        this -> buffer[16][1] = postion.y - size.y;
        this -> buffer[16][2] = postion.z + size.z;
        this -> buffer[16][6] = 0.0;
        this -> buffer[16][7] = 1.0;

        this -> buffer[17][0] = postion.x + size.x;
        this -> buffer[17][1] = postion.y - size.y;
        this -> buffer[17][2] = postion.z + size.z;
        this -> buffer[17][6] = 0.0;
        this -> buffer[17][7] = 0.0;

        this -> buffer[18][0] = postion.x + size.x;
        this -> buffer[18][1] = postion.y + size.y;
        this -> buffer[18][2] = postion.z + size.z;
        this -> buffer[18][6] = 1.0;
        this -> buffer[18][7] = 0.0;

        this -> buffer[19][0] = postion.x - size.x;
        this -> buffer[19][1] = postion.y + size.y;
        this -> buffer[19][2] = postion.z + size.z;
        this -> buffer[19][6] = 1.0;
        this -> buffer[19][7] = 1.0;

        //下面

        this -> buffer[20][0] = postion.x + size.x;
        this -> buffer[20][1] = postion.y - size.y;
        this -> buffer[20][2] = postion.z - size.z;
        this -> buffer[20][6] = 0.0;
        this -> buffer[20][7] = 1.0;

        this -> buffer[21][0] = postion.x - size.x;
        this -> buffer[21][1] = postion.y - size.y;
        this -> buffer[21][2] = postion.z - size.z;
        this -> buffer[21][6] = 0.0;
        this -> buffer[21][7] = 0.0;

        this -> buffer[22][0] = postion.x - size.x;
        this -> buffer[22][1] = postion.y + size.y;
        this -> buffer[22][2] = postion.z - size.z;
        this -> buffer[22][6] = 1.0;
        this -> buffer[22][7] = 0.0;

        this -> buffer[23][0] = postion.x + size.x;
        this -> buffer[23][1] = postion.y + size.y;
        this -> buffer[23][2] = postion.z - size.z;
        this -> buffer[23][6] = 1.0;
        this -> buffer[23][7] = 1.0;

        for (int i = 0; i < 6; i++) {
            int index = i * 4;
            glm::vec3 v1(this->buffer[index + 1][0] - this->buffer[index][0], this->buffer[index + 1][1] - this->buffer[index][1], this->buffer[index + 1][2] - this->buffer[index][2]);
            glm::vec3 v2(this->buffer[index + 3][0] - this->buffer[index][0], this->buffer[index + 3][1] - this->buffer[index][1], this->buffer[index + 3][2] - this->buffer[index][2]);
            
            glm::vec3 normal = glm::cross(v1, v2);
            for (int j = 0; j < 4; j++) {
                this->buffer[index + j][3] = normal.x;
                this->buffer[index + j][4] = normal.y;
                this->buffer[index + j][5] = normal.z;

            }
        }
        // vbo
        glGenBuffers(6, this->vbo);
        glGenBuffers(6, this->ebo);
        glGenVertexArrays(6, this->vao);

        for (int i = 0 ; i < 6 ; i++) {
            glBindBuffer(GL_ARRAY_BUFFER, this->vbo[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(this->buffer[i]) * 4 , this->buffer[i * 4] , GL_STATIC_DRAW);
            glBindVertexArray(this->vao[i]);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo[i]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->eboBuffer), eboBuffer, GL_STATIC_DRAW);
        }


    }
    void CCube::draw() {

        CClient::instance().get_shadermgr().setMat4("model", model);
        for (int i = 0 ; i < 6 ; i++) {
            if (shader != nullptr)
                shader->use();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture.get_id());
            glBindVertexArray(this->vao[i]);
            glBindBuffer(GL_ARRAY_BUFFER, this->vbo[i]);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo[i]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
}