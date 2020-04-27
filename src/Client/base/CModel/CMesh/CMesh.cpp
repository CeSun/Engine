//
// Created by ��� on 2020/4/20.
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
        // ���붥���������
        glGenVertexArrays(1, &VAO);
        // ���붥�㻺�����
        glGenBuffers(1, &VBO);
        // ���������������
        glGenBuffers(1, &EBO);
        // ��VAO
        glBindVertexArray(VAO);
        // ��VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // struct��������vectorҲ�������ģ�float�����Ƕ���ģ���������ͺ�����
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // ���ö������ݵ�����
        // ����
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // ������
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // ����UV����
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        // ����
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
        // ˫����
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
        // ȡ����VAO
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