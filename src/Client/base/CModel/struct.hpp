#ifndef __CMODEL_STRUCT_HPP__
#define __CMODEL_STRUCT_HPP__
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <map>

#define NUM_BONES_PER_VEREX 4
// ģ����صĽṹ�嶨��
namespace GameClient {
	// �������ݽṹ��
// ����������
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

		int NumBones = 0;
		// ��ͷid
		int Bone[NUM_BONES_PER_VEREX] = {0};
		// ��ͷȨ��
		float Weight[NUM_BONES_PER_VEREX] = {0.0f};

	};
#pragma pack()

	// ����ṹ��
	struct Texture {
		std::shared_ptr<const CTexture> poTexture;
		std::string Type;
	};
	// �����ṹ��
	struct Bone {
		// ����id
		uint32_t ID;
		// ���ڵ����id
		int32_t ParentId;
		// ���ڵ�����
		std::string ParentName;
		std::string Name;
		// ���ڵ�
		Bone* Parent;
		// ����ƫ�ƾ���
		glm::mat4 OffsetMat;
		// ���ؾ���
		glm::mat4 LocalMat;
		// ���ӽڵ�
		std::vector<uint32_t> children;
	};

	// ÿ����������һ�������Ķ�����Ϣ
	struct Channel {
		// ��������
		std::string BoneName;
		// ����id
		uint32_t BoneId;
		// ���ڵ�id
		int ParentId;

		std::string ParentName;
		// ����λ������
		std::vector<glm::vec3> PostionKeys;
		// ������������
		std::vector<glm::vec3> ScalingKeys;
		// ������ת����Ԫ��
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
