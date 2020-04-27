//
// Created by 孙策 on 2020/4/20.
//

#include "CMesh.hpp"
#include <glad/glad.h>
#include <iostream>

namespace GameClient {
    CMesh::~CMesh() {};
	CMesh::CMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
        this->SetUpMesh();
	}

	void CMesh::SetUpMesh() {
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
        // struct是连续的vector也是连续的，float正好是对齐的，所以这里就很神奇
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // 设置顶点数据的属性
        // 顶点
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // 法向量
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // 纹理UV坐标
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        // 切线
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
        // 双切线
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
        // 取消绑定VAO
        glBindVertexArray(0);
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