/*
 *  文 件: CLight.cpp
 *  功 能: 光源
 *  时 间: 2020/03/28
 *  作 者: SunCe
*/
#include "CLight.hpp"
#include <Client/CClient/CClient.hpp>
namespace GameClient {
    CLight::CLight() {};

    CLight::CLight(LIGHTTYPE type, glm::vec3 color, glm::vec3 position, glm::vec3 direction, float cutOff) {
        this->lightParam.type = type;
        this->lightParam.color = color;
        this->lightParam.position = position;
        this->lightParam.direction = direction;
        this->lightParam.cutOff = cutOff;
    }
    CLight::CLight(LIGHTTYPE type, glm::vec3 color, glm::vec3 position) {
        this->lightParam.type = CLight::LIGHTTYPE::LIGHTTYPE_POINT;
        this->lightParam.color = color;
        this->lightParam.position = position;
    }

    CLight::CLight(glm::vec3 color, glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff) {
        this->lightParam.type = CLight::LIGHTTYPE::LIGHTTYPE_SPOT;
        this->lightParam.color = color;
        this->lightParam.position = position;
        this->lightParam.direction = direction;
        this->lightParam.cutOff = cutOff;
        this->lightParam.outerCutOff = outerCutOff;
    }

    CLight::CLight(glm::vec3 color, glm::vec3 direction) {
        this->lightParam.type = CLight::LIGHTTYPE::LIGHTTYPE_DIRECTIONAL;
        this->lightParam.color = color;
        this->lightParam.direction = direction;
    }

}