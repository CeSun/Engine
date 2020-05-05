#ifndef __CHlModel_HPP__
#define __CHlModel_HPP__
#include <string>
#include <base/CShader/CShader.hpp>

namespace GameClient {
	class CHlModel {
	public:
		// 初始化模型
		CHlModel(const std::string& path);
		// 绘制
		void Draw(const CShader& shader);
		// 设置播放动作 
		void SetAnimation(int index, bool isLoop = true);
		// 设置播放动作
		void SetAnimation(const std::string name, bool isLoop = true);

	private:

	};
}


#endif // !__CHlModel_HPP__
