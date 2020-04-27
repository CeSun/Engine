#ifndef __CMODEL_STRUCT_HPP__
#define __CMODEL_STRUCT_HPP__
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

// 模型相关的结构体定义
namespace GameClient {
	// 顶点数据结构体
#pragma pack(1)
	struct Vertex {
		// 顶点坐标
		glm::vec3 Position;
		// 法向量
		glm::vec3 Normal;
		// 纹理坐标
		glm::vec2 TexCoords;
		// tangent
		glm::vec3 Tangent;
		// bitangent
		glm::vec3 Bitangent;
		// 所关联骨骼的权重 
		glm::vec4 boneWeights;
		// 所关联骨骼的索引
		glm::vec4 boneIndexs;
		//所关联权重的起始索引
		int startWeight;
		// 所关联的权重总数
		int weightCount;
	};
#pragma pack()

	// 纹理结构体
	struct Texture {
		std::shared_ptr<const CTexture> poTexture;
		std::string Type;
	};

}
#endif // !__CMODEL_STRUCT_HPP__
