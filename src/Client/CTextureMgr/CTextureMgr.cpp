//
// Created by Sunce on 2020/3/25.
//

#include "CTextureMgr.hpp"
#include <Client/base/CTexture/CTexture.hpp>

namespace GameClient {
	std::shared_ptr<const CTexture> CTextureMgr::add_texture(const std::string& filename) {
		auto iter = texturemap.find(filename);
		if (iter == texturemap.end()) {
			// map��û���Ǿͼ�������
			std::shared_ptr<CTexture> poTexture = std::make_shared<CTexture>(filename);
			if (poTexture == nullptr) {
				return nullptr;
			} else {
				// ����map
				texturemap[filename] = poTexture;
				return poTexture;
			}
		}
		else {
			// map���У��Ǿ�ֱ�ӷ���
			return texturemap[filename];
		}
	}
}