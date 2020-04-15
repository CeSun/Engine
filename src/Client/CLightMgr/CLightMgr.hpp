/*
 *  文 件: CLightMgr.hpp
 *  功 能: 光源管理
 *  时 间: 2020/03/28
 *  作 者: SunCe
*/

#ifndef __CLIGHTMGR_HPP__
#define __CLIGHTMGR_HPP__
#define MAX_LIGHT_NUM 20
#include <Client/base/CLight/CLight.hpp>
#include <unordered_map>
#include <memory>
#include <string>

namespace GameClient {
    class CLightMgr {
    public:
        void add_light(std::string key, std::shared_ptr<CLight> light);
        void del_light(std::string key);
        void update_shader() const;
    private:
        std::unordered_map<std::string, std::shared_ptr<CLight>> lightMap;
    };
}
#endif // !__CLIGHTMGR_HPP__
