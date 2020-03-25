//
// Created by Sunce on 2020/3/2.
//

#ifndef _CTEXTUREMGR_HPP_
#define _CTEXTUREMGR_HPP_
#include <map>
#include <string>
#include <memory>

namespace GameClient {
	class CTexture;
	class CTextureMgr {
	public:
		CTextureMgr() {}
		~CTextureMgr() {}
		const CTexture& add_texture(const std::string& filename);
	private:
		std::map<std::string, std::shared_ptr<CTexture>> texturemap;
	};
}

#endif // !_CTEXTUREMGR_HPP_
