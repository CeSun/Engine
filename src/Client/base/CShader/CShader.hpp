//
// Created by SunCe on 2020/2/3.
//

#ifndef ENGINE_CSHADER_HPP
#define ENGINE_CSHADER_HPP

#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <Client/base/CTexture/CTexture.hpp>
#include <glad\glad.h>
namespace GameClient {
    class CShader {
    public:

        /*  ����: ���캯��, ��ʼ����ɫ������
         *  ����:
         *    vertexPath   [����]: ������ɫ�����ļ�·��
         *    fragmentPath [����]: Ƭ����ɫ�����ļ�·��
         */
        CShader (const std::string& vertexPath, const std::string& fragmentPath);
        ~CShader();

        /*  ����: ʹ����ɫ��
         *  ����: ��
         *  ����: ��
         */
        void use() const;

        /*  ����: ����bool���͵�uniform
         *  ����:
         *    name  [����]: uniform��������
         *    value [����]: ������ɫ����ֵ
         *  ����: ��
         */
        void setBool(const std::string &name, bool value) const;

        /*  ����: ����int���͵�uniform
         *  ����:
         *    name  [����]: uniform��������
         *    value [����]: ������ɫ����ֵ
         *  ����: ��
         */
        void setInt(const std::string &name, int value) const;

        /*  ����: ����float���͵�uniform
         *  ����:
         *    name  [����]: uniform��������
         *    value [����]: ������ɫ����ֵ
         *  ����: ��
         */
        void setFloat(const std::string &name, float value) const;

        /*  ����: ���ö�ά�������͵�uniform
         *  ����:
         *    name  [����]: uniform��������
         *    value [����]: ������ɫ����ֵ
         *  ����: ��
         */
        void setVec2(const std::string &name, const glm::vec2 &value) const;
        void setVec2(const std::string &name, float x, float y) const;

        /*  ����: ������ά�������͵�uniform
         *  ����:
         *    name  [����]: uniform��������
         *    value [����]: ������ɫ����ֵ
         *  ����: ��
         */
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        void setVec3(const std::string &name, float x, float y, float z) const;

        /*  ����: ������ά�������͵�uniform
         *  ����:
         *    name  [����]: uniform��������
         *    value [����]: ������ɫ����ֵ
         *  ����: ��
         */
        void setVec4(const std::string &name, const glm::vec4 &value) const;
        void setVec4(const std::string &name, float x, float y, float z, float w);

        /*  ����: ����2*2�������͵�uniform
         *  ����:
         *    name  [����]: uniform��������
         *    value [����]: ������ɫ����ֵ
         *  ����: ��
         */
        void setMat2(const std::string &name, const glm::mat2 &mat) const;

        /*  ����: ����3*3�������͵�uniform
         *  ����:
         *    name  [����]: uniform��������
         *    value [����]: ������ɫ����ֵ
         *  ����: ��
         */
        void setMat3(const std::string &name, const glm::mat3 &mat) const;

        /*  ����: ����4*4�������͵�uniform
         *  ����:
         *    name  [����]: uniform��������
         *    value [����]: ������ɫ����ֵ
         *  ����: ��
         */
        void setMat4(const std::string &name, const glm::mat4 &mat, int size = 1) const;

        void setUinform1i(const std::string& name, GLint index) const;


    public:
    private:
        unsigned ID;
    };
}
#endif //ENGINE_CSHADER_HPP
