//
// Created by ��� on 2020/4/20.
//

#ifndef __CMESH_HPP__
#define __CMESH_HPP__

#include <glm/glm.hpp>
#include <base/CTexture/CTexture.hpp>
#include <string>
#include <memory>
#include <vector>
#include <base/CShader/CShader.hpp>
#include "../struct.hpp"

namespace GameClient {
	// ����
	class CMesh {
	public:
		// ���캯��
		CMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		// ��������
		~CMesh();
		// ����ģ��
		void Draw(std::shared_ptr<const CShader> shader);
	private:
		// �ϴ�������Ϣ���Կ�
		void SetUpMesh();
	public:
		// ��������
		std::vector<Vertex> vertices;
		// EBO����
		std::vector<unsigned int> indices;
		// ��������
		std::vector<Texture> textures;
	private:
		// �����õĸ�������
		unsigned int VAO, VBO, EBO;
	};
}
#endif // !__CMESH_HPP__
