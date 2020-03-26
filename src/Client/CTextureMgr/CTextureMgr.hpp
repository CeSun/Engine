//
// Created by Sunce on 2020/3/2.
//

#ifndef _CTEXTUREMGR_HPP_
#define _CTEXTUREMGR_HPP_
#include <map>
#include <string>
#include <memory>
#include <Client/base/CTexture/CTexture.hpp>

namespace GameClient {
	class CTextureMgr {
	public:
		CTextureMgr() {}
		~CTextureMgr() {}
		std::shared_ptr<const CTexture> add_texture(const std::string& filename);
	private:
		std::map<std::string, std::shared_ptr<CTexture>> texturemap;
	};
}

#endif // !_CTEXTUREMGR_HPP_
