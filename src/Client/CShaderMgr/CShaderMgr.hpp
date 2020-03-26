//
// Created by SunCe on 2020/3/24.
//

#ifndef ENGINE_CSHADERMGR_HPP
#define ENGINE_CSHADERMGR_HPP

#include <glm/glm.hpp>
#include <string>
#include <map>
#include <memory>
#include <Client/base/CShader/CShader.hpp>

// 着色器管理对象
namespace GameClient {
    class CShader;
    class CShaderMgr {
    public:
        // 构造函数
        CShaderMgr();
        // 析构函数
        ~CShaderMgr();
        // 添加着色器
        std::shared_ptr<const CShader> add_shader(const std::string& vsname, const std::string& fsname);

    private:
        struct SShaderPath {
            std::string vs;
            std::string fs;
            bool operator < (const SShaderPath& a) const {
                return this->vs < a.vs;
            }
            bool operator > (const SShaderPath& a) const {
                return this->vs > a.vs;
            }
        };
        std::map<SShaderPath, std::shared_ptr<CShader>> shaderMap;
    public:
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setVec2(const std::string& name, const glm::vec2& value) const;
        void setVec2(const std::string& name, float x, float y) const;
        void setVec3(const std::string& name, const glm::vec3& value) const;
        void setVec3(const std::string& name, float x, float y, float z) const;
        void setVec4(const std::string& name, const glm::vec4& value) const;
        void setVec4(const std::string& name, float x, float y, float z, float w) const;
        void setMat2(const std::string& name, const glm::mat2& mat) const;
        void setMat3(const std::string& name, const glm::mat3& mat) const;
        void setMat4(const std::string& name, const glm::mat4& mat) const;
    };

}


#endif //ENGINE_CSHADERMGR_HPP
