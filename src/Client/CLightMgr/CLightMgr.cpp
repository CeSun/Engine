/*
 *  文 件: CLightMgr.hpp
 *  功 能: 光源管理
 *  时 间: 2020/03/28
 *  作 者: SunCe
*/
#include "CLightMgr.hpp"
#include <Client/CClient/CClient.hpp>
#include <sstream>
#include <iostream>
namespace GameClient {
    void CLightMgr::add_light(std::string key, std::shared_ptr<CLight> light) {
        if (lightMap.size() >= MAX_LIGHT_NUM) {
            return;
        }
        lightMap[key] = light;
    }
    void CLightMgr::del_light(std::string key) {
        auto iter = lightMap.find(key);
        if (iter != lightMap.end()) {
            lightMap.erase(key);
        }
    }
    void CLightMgr::update_shader() const {
        CClient::intance().get_shadermgr().setInt("lightNum", lightMap.size());
        int i = 0;
        for (auto iter = lightMap.begin(); iter != lightMap.end(); iter++) {
            CLight::LightParam& lightparam = iter->second->lightParam;
            std::stringstream attribute;
            attribute << "lightParam[" << i << "].";
            CClient::intance().get_shadermgr().setInt(attribute.str() + "lighttype", lightparam.type);
            CClient::intance().get_shadermgr().setVec3(attribute.str() + "position", lightparam.position);
            CClient::intance().get_shadermgr().setVec3(attribute.str() + "color", lightparam.color);
            CClient::intance().get_shadermgr().setVec3(attribute.str() + "direction", lightparam.direction);
            CClient::intance().get_shadermgr().setFloat(attribute.str() + "cutOff", lightparam.cutOff);
            CClient::intance().get_shadermgr().setFloat(attribute.str() + "constant", lightparam.attenuation.constant);
            CClient::intance().get_shadermgr().setFloat(attribute.str() + "linear", lightparam.attenuation.linear);
            CClient::intance().get_shadermgr().setFloat(attribute.str() + "quadratic", lightparam.attenuation.quadratic);
            CClient::intance().get_shadermgr().setFloat(attribute.str() + "outerCutOff", lightparam.outerCutOff);
            
            i++;
        }
    }
}