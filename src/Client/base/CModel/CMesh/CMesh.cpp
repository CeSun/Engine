//
// Created by 孙策 on 2020/4/20.
//

#include "CMesh.hpp"
#include <glad/glad.h>
#include <iostream>
#include <Common/CLog/CLog.hpp>
namespace GameClient {
    CMesh::~CMesh() {};
	CMesh::CMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
        this->SetUpMesh();
	}

	void CMesh::SetUpMesh() {

        int index = 0;
        for (auto iter : this->vertices) {
            if (iter.NumBones != 1) {
                //APP_LOG_INFO("id:%d, size: %d", index, iter.NumBones);
            }
            index++;
        }
        // 申请顶点数组对象
        glGenVertexArrays(1, &VAO);
        // 申请顶点缓存对象
        glGenBuffers(1, &VBO);
        // 申请索引缓存对象
        glGenBuffers(1, &EBO);
        // 绑定VAO
        glBindVertexArray(VAO);
        // 绑定VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        // 绑定EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // 设置顶点数据的属性
        // 顶点
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::Position));
        // 法向量
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::Normal));
        // 纹理UV坐标
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::TexCoords));
        /*
        // 切线
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::Tangent));
        // 双切线
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::Bitangent));

        // 骨头数量
        glEnableVertexAttribArray(5);
        glVertexAttribIPointer(5, 1, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::NumBones));

        // 骨头id
        glEnableVertexAttribArray(6);
        glVertexAttribIPointer(6, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::Bone));
        // 骨头权重
        glEnableVertexAttribArray(7);
        glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::Weight));
        */


        // 骨头数量
        glEnableVertexAttribArray(3);
        glVertexAttribIPointer(3, 1, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::NumBones));

        // 骨头id
        glEnableVertexAttribArray(4);
        glVertexAttribIPointer(4, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::Bone));
        // 骨头权重
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::Weight));

        static int Max = 0;
        // 取消绑定VAO
        glBindVertexArray(0);
        for (int i = 0; i < vertices.size(); i++) {
            unsigned char* ptr = (unsigned char*)(&vertices[0]);
            Vertex* ptr2 = (Vertex*)ptr;
            int number = *(int*)(((char*)(&vertices[0])) + offsetof(Vertex, Vertex::Bone));
            if (number > Max)
                Max = number;
        }
        APP_LOG_INFO("Max %d", Max);
	}

    void CMesh::Draw(std::shared_ptr<const CShader> shader) {
        // bind appropriate textures
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);

            std::string number;
            std::string& name = textures[i].Type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++);
            else if (name == "texture_normal")
                number = std::to_string(normalNr++);
            else if (name == "texture_height")
                number = std::to_string(heightNr++);
            shader->setUinform1i((name + number).c_str(), static_cast<GLint> (i));

            glBindTexture(GL_TEXTURE_2D, textures[i].poTexture->get_id());
           
        }
        shader->use();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        glActiveTexture(GL_TEXTURE0);
    }
}