/*
 *  �� ��: CLight.hpp
 *  �� ��: ��Դ
 *  ʱ ��: 2020/03/28
 *  �� ��: SunCe
*/

#ifndef __CLIGHT_HPP__
#define __CLIGHT_HPP__

#include <glm/glm.hpp>

namespace GameClient {
    class CLight {
    public:
        enum LIGHTTYPE
        {
            LIGHTTYPE_POINT = 1,        // ���Դ
            LIGHTTYPE_SPOT,             // �۹�
            LIGHTTYPE_DIRECTIONAL,      // ƽ�й�
        };
        // ��˥���ṹ
        struct Attenuation
        {
            float constant;             // ����
            float linear;               // һ����
            float quadratic;            // ������
        };
        struct LightParam
        {
            LIGHTTYPE type;
            glm::vec3 position;      // λ��
            glm::vec3 color;        // ��ɫ
            glm::vec3 direction;    // ƽ�йⷽ��
            float cutOff;           // �۹�Ƕ�
            float outerCutOff;
            Attenuation attenuation = { 1.0, 0.045, 0.0075 };     // ˥������
        };
    public:
        // ����дgetter��setter��ֱ��public��(��ʵҲû�б�Ҫд)
        LightParam lightParam;

    public:
        CLight();
        // ��Դ���ͣ���ɫ��λ�ã����򣬽Ƕȣ�˥��������
        CLight(LIGHTTYPE type, glm::vec3 color, glm::vec3 position, glm::vec3 direction, float cutOff);
        // ���Դ: ��ɫ��λ�ã�˥������
        CLight(LIGHTTYPE type, glm::vec3 color, glm::vec3 position);
        // �۹�: ��ɫ��λ�ã����򣬽Ƕȣ�˥������
        CLight(glm::vec3 color, glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff);
        // ƽ�й�: ��ɫ������
        CLight(glm::vec3 color, glm::vec3 direction);
    };
}
#endif // !__CLIGHT_HPP__
