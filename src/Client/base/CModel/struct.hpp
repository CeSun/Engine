#ifndef __CMODEL_STRUCT_HPP__
#define __CMODEL_STRUCT_HPP__
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

// ģ����صĽṹ�嶨��
namespace GameClient {
	// �������ݽṹ��
#pragma pack(1)
	struct Vertex {
		// ��������
		glm::vec3 Position;
		// ������
		glm::vec3 Normal;
		// ��������
		glm::vec2 TexCoords;
		// tangent
		glm::vec3 Tangent;
		// bitangent
		glm::vec3 Bitangent;
		// ������������Ȩ�� 
		glm::vec4 boneWeights;
		// ����������������
		glm::vec4 boneIndexs;
		//������Ȩ�ص���ʼ����
		int startWeight;
		// ��������Ȩ������
		int weightCount;
	};
#pragma pack()

	// ����ṹ��
	struct Texture {
		std::shared_ptr<const CTexture> poTexture;
		std::string Type;
	};

}
#endif // !__CMODEL_STRUCT_HPP__
