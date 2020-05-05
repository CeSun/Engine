#ifndef __CMODEL_STRUCT_HPP__
#define __CMODEL_STRUCT_HPP__
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <map>

#define NUM_BONES_PER_VEREX 4
// 模型相关的结构体定义
namespace GameClient {
	// 顶点数据结构体
// 不开启对齐
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

		int NumBones = 0;
		// 骨头id
		int Bone[NUM_BONES_PER_VEREX] = {0};
		// 骨头权重
		float Weight[NUM_BONES_PER_VEREX] = {0.0f};

	};
#pragma pack()

	// 纹理结构体
	struct Texture {
		std::shared_ptr<const CTexture> poTexture;
		std::string Type;
	};
	// 骨骼结构体
	struct Bone {
		// 骨骼id
		uint32_t ID;
		// 父节点骨骼id
		int32_t ParentId;
		// 父节点名称
		std::string ParentName;
		std::string Name;
		// 父节点
		Bone* Parent;
		// 骨骼偏移矩阵
		glm::mat4 OffsetMat;
		// 本地矩阵
		glm::mat4 LocalMat;
		// 孩子节点
		std::vector<uint32_t> children;
	};

	// 每个动画其中一个骨骼的动作信息
	struct Channel {
		// 骨骼名称
		std::string BoneName;
		// 骨骼id
		uint32_t BoneId;
		// 父节点id
		int ParentId;

		std::string ParentName;
		// 骨骼位移向量
		std::vector<glm::vec3> PostionKeys;
		// 骨骼缩放向量
		std::vector<glm::vec3> ScalingKeys;
		// 骨骼旋转的四元数
		std::vector<glm::quat> RotationKeys;
	};

	struct Animation {
		double Ticks;
		double Duration;
		std::vector<Channel> Channels;
		std::map<uint32_t, int> map;
	};
}
#endif // !__CMODEL_STRUCT_HPP__
