//
// Created by SunCe on 2020/2/3.
//

#ifndef ENGINE_CSHADER_HPP
#define ENGINE_CSHADER_HPP

#include <glm/glm.hpp>
#include <string>
#include <Client/base/CTexture/CTexture.hpp>
namespace GameClient {
    class CShader {
    public:
        CShader (const std::string& vertexPath, const std::string& fragmentPath);
        ~CShader();
        void use() const;
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec2(const std::string &name, const glm::vec2 &value) const;
        void setVec2(const std::string &name, float x, float y) const;
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        void setVec4(const std::string &name, const glm::vec4 &value) const;
        void setVec4(const std::string &name, float x, float y, float z, float w);
        void setMat2(const std::string &name, const glm::mat2 &mat) const;
        void setMat3(const std::string &name, const glm::mat3 &mat) const;
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
    private:
        unsigned ID;
    };
}
#endif //ENGINE_CSHADER_HPP
