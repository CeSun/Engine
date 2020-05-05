#ifndef __CHlModel_HPP__
#define __CHlModel_HPP__
#include <string>
#include <base/CShader/CShader.hpp>

namespace GameClient {
	class CHlModel {
	public:
		// ��ʼ��ģ��
		CHlModel(const std::string& path);
		// ����
		void Draw(const CShader& shader);
		// ���ò��Ŷ��� 
		void SetAnimation(int index, bool isLoop = true);
		// ���ò��Ŷ���
		void SetAnimation(const std::string name, bool isLoop = true);

	private:

	};
}


#endif // !__CHlModel_HPP__
