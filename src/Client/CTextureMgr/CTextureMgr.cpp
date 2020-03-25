//
// Created by Sunce on 2020/3/25.
//

#include "CTextureMgr.hpp"
#include <Client/base/CTexture/CTexture.hpp>

namespace GameClient {
	const CTexture& CTextureMgr::add_texture(const std::string& filename) {
		auto iter = texturemap.find(filename);
		if (iter == texturemap.end()) {
			// map里没有那就加载纹理
			std::shared_ptr<CTexture> poTexture = std::make_shared<CTexture>(filename);
			// 插入map
			texturemap[filename] = poTexture;
		}
		// map里有，那就直接返回
		return *(texturemap[filename]);
	}
}