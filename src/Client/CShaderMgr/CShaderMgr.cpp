//
// Created by SunCe on 2020/3/24.
//

#include "CShaderMgr.hpp"
#include <Client/base/CShader/CShader.hpp>

namespace GameClient {

    CShaderMgr::CShaderMgr() {}

    CShaderMgr::~CShaderMgr() {
        for (auto iter : shaderlist) {
        }
    }

    const CShader& CShaderMgr::add_shader(const std::string& vsname, const std::string& fsname) {
        std::shared_ptr<CShader> shader = std::make_shared<CShader>(vsname, fsname);
        if (shader != nullptr) {
            this->shaderlist.push_back(shader);
            return *shader;
        }
        return *shader;
    }
    void CShaderMgr::useShader(int shaderId) const {
        this->shaderlist[shaderId]->use();
    }
    void CShaderMgr::setBool(const std::string& name, bool value) const {
        for (auto iter : shaderlist) {
            iter->use();
            iter->setBool(name, value);
        }
    }
    void CShaderMgr::setInt(const std::string& name, int value) const {
        for (auto iter : shaderlist) {
            iter->use();
            iter->setInt(name, value);
        }
    }
    void CShaderMgr::setFloat(const std::string& name, float value) const {
        for (auto iter : shaderlist) {
            iter->use();
            iter->setFloat(name, value);
        }
    }
    void CShaderMgr::setVec2(const std::string& name, const glm::vec2& value) const {
        for (auto iter : shaderlist) {
            iter->use();
            iter->setVec2(name, value);
        }
    }
    void CShaderMgr::setVec2(const std::string& name, float x, float y) const {
        for (auto iter : shaderlist) {
            iter->use();
            iter->setVec2(name, x, y);
        }
    }
    void CShaderMgr::setVec3(const std::string& name, const glm::vec3& value) const {
        for (auto iter : shaderlist) {
            iter->use();
            iter->setVec3(name, value);
        }
    }
    void CShaderMgr::setVec3(const std::string& name, float x, float y, float z) const {
        for (auto iter : shaderlist) {
            iter->use();
            iter->setVec3(name, x, y, z);
        }
    }
    void CShaderMgr::setVec4(const std::string& name, const glm::vec4& value) const {
        for (auto iter : shaderlist) {
            iter->use();
            iter->setVec4(name, value);
        }
    }
    void CShaderMgr::setVec4(const std::string& name, float x, float y, float z, float w) const {
        for (auto iter : shaderlist) {
            iter->use();
            iter->setVec4(name, x, y, z, w);
        }
    }
    void CShaderMgr::setMat2(const std::string& name, const glm::mat2& mat) const {
        for (auto iter : shaderlist) {
            iter->use();
            iter->setMat2(name, mat);
        }
    }
    void CShaderMgr::setMat3(const std::string& name, const glm::mat3& mat) const {
        for (auto iter : shaderlist) {
            iter->use();
            iter->setMat3(name, mat);
        }
    }
    void CShaderMgr::setMat4(const std::string& name, const glm::mat4& mat) const {
        for (auto iter : shaderlist) {
            iter->use();
            iter->setMat4(name, mat);
        }
    }
}