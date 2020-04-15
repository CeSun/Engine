/*
 *  文 件: CLight.hpp
 *  功 能: 光源
 *  时 间: 2020/03/28
 *  作 者: SunCe
*/

#ifndef __CLIGHT_HPP__
#define __CLIGHT_HPP__

#include <glm/glm.hpp>

namespace GameClient {
    class CLight {
    public:
        enum LIGHTTYPE
        {
            LIGHTTYPE_POINT = 1,        // 点光源
            LIGHTTYPE_SPOT,             // 聚光
            LIGHTTYPE_DIRECTIONAL,      // 平行光
        };
        // 光衰减结构
        struct Attenuation
        {
            float constant;             // 常量
            float linear;               // 一次项
            float quadratic;            // 二次项
        };
        struct LightParam
        {
            LIGHTTYPE type;
            glm::vec3 position;      // 位置
            glm::vec3 color;        // 颜色
            glm::vec3 direction;    // 平行光方向
            float cutOff;           // 聚光角度
            float outerCutOff;
            Attenuation attenuation = { 1.0, 0.045, 0.0075 };     // 衰减参数
        };
    public:
        // 懒得写getter和setter，直接public。(其实也没有必要写)
        LightParam lightParam;

    public:
        CLight();
        // 光源类型，颜色，位置，方向，角度，衰弱参数。
        CLight(LIGHTTYPE type, glm::vec3 color, glm::vec3 position, glm::vec3 direction, float cutOff);
        // 点光源: 颜色，位置，衰弱参数
        CLight(LIGHTTYPE type, glm::vec3 color, glm::vec3 position);
        // 聚光: 颜色，位置，方向，角度，衰弱参数
        CLight(glm::vec3 color, glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff);
        // 平行光: 颜色，方向
        CLight(glm::vec3 color, glm::vec3 direction);
    };
}
#endif // !__CLIGHT_HPP__
