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

        /*  概括: 构造函数, 初始化着色器对象
         *  参数:
         *    vertexPath   [输入]: 顶点着色器的文件路径
         *    fragmentPath [输入]: 片段着色器的文件路径
         */
        CShader (const std::string& vertexPath, const std::string& fragmentPath);
        ~CShader();

        /*  概括: 使用着色器
         *  参数: 无
         *  返回: 无
         */
        void use() const;

        /*  概括: 设置bool类型的uniform
         *  参数:
         *    name  [输入]: uniform变量名称
         *    value [输入]: 传给着色器的值
         *  返回: 无
         */
        void setBool(const std::string &name, bool value) const;

        /*  概括: 设置int类型的uniform
         *  参数:
         *    name  [输入]: uniform变量名称
         *    value [输入]: 传给着色器的值
         *  返回: 无
         */
        void setInt(const std::string &name, int value) const;

        /*  概括: 设置float类型的uniform
         *  参数:
         *    name  [输入]: uniform变量名称
         *    value [输入]: 传给着色器的值
         *  返回: 无
         */
        void setFloat(const std::string &name, float value) const;

        /*  概括: 设置二维向量类型的uniform
         *  参数:
         *    name  [输入]: uniform变量名称
         *    value [输入]: 传给着色器的值
         *  返回: 无
         */
        void setVec2(const std::string &name, const glm::vec2 &value) const;
        void setVec2(const std::string &name, float x, float y) const;

        /*  概括: 设置三维向量类型的uniform
         *  参数:
         *    name  [输入]: uniform变量名称
         *    value [输入]: 传给着色器的值
         *  返回: 无
         */
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        void setVec3(const std::string &name, float x, float y, float z) const;

        /*  概括: 设置四维向量类型的uniform
         *  参数:
         *    name  [输入]: uniform变量名称
         *    value [输入]: 传给着色器的值
         *  返回: 无
         */
        void setVec4(const std::string &name, const glm::vec4 &value) const;
        void setVec4(const std::string &name, float x, float y, float z, float w);

        /*  概括: 设置2*2矩阵类型的uniform
         *  参数:
         *    name  [输入]: uniform变量名称
         *    value [输入]: 传给着色器的值
         *  返回: 无
         */
        void setMat2(const std::string &name, const glm::mat2 &mat) const;

        /*  概括: 设置3*3矩阵类型的uniform
         *  参数:
         *    name  [输入]: uniform变量名称
         *    value [输入]: 传给着色器的值
         *  返回: 无
         */
        void setMat3(const std::string &name, const glm::mat3 &mat) const;

        /*  概括: 设置4*4矩阵类型的uniform
         *  参数:
         *    name  [输入]: uniform变量名称
         *    value [输入]: 传给着色器的值
         *  返回: 无
         */
        void setMat4(const std::string &name, const glm::mat4 &mat, int size = 1) const;

        void setUinform1i(const std::string& name, GLint index) const;


    public:
    private:
        unsigned ID;
    };
}
#endif //ENGINE_CSHADER_HPP
