//
// Created by 孙策 on 2020/4/20.
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
	// 网格
	class CMesh {
	public:
		// 构造函数
		CMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		// 析构函数
		~CMesh();
		// 绘制模型
		void Draw(std::shared_ptr<const CShader> shader);
	private:
		// 上传顶点信息到显卡
		void SetUpMesh();
	public:
		// 顶点数据
		std::vector<Vertex> vertices;
		// EBO数据
		std::vector<unsigned int> indices;
		// 纹理数据
		std::vector<Texture> textures;
	private:
		// 绘制用的各个对象
		unsigned int VAO, VBO, EBO;
	};
}
#endif // !__CMESH_HPP__
