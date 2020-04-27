//
// Created by SunCe on 2020/2/3.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "CShader.hpp"

namespace GameClient {
    CShader::CShader(const std::string& vertexPath, const std::string& fragmentPath) {

        std::ifstream vertexFile;
        std::ifstream fragmentFile;
        vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        std::stringstream vShaderStream,fShaderStream;
        std::string vShaderSource;
        std::string fShaderSource;
        try {
            vertexFile.open(vertexPath);
            fragmentFile.open(fragmentPath);
            vShaderStream << vertexFile.rdbuf();
            fShaderStream << fragmentFile.rdbuf();
            vertexFile.close();
            fragmentFile.close();
            vShaderSource = vShaderStream.str();
            fShaderSource = fShaderStream.str();

        } catch (const std::exception& ex) {
            std::cout << ex.what() << std::endl;
        }
        unsigned int vertexShader,fragmentShader;

        const char* vShaderCode = vShaderSource.c_str();
        const char* fShaderCode = fShaderSource.c_str();
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
        glCompileShader(vertexShader);
        std::cout << vertexPath << std::endl;
        checkCompileErrors(vertexShader, CompileType::SHADER);

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
        glCompileShader(fragmentShader);
        std::cout << fragmentPath << std::endl;
        checkCompileErrors(fragmentShader, CompileType::SHADER);

        this->ID = glCreateProgram();
        glAttachShader(this->ID, vertexShader);
        glAttachShader(this->ID, fragmentShader);
        glLinkProgram(this->ID);
        checkCompileErrors(this->ID, CompileType::PROGRAM);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    }
    void CShader::use() const {
        glUseProgram(this->ID);
    }
    void CShader::setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void CShader::setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void CShader::setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void CShader::setVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void CShader::setVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }
    void CShader::setVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void CShader::setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    void CShader::setVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void CShader::setVec4(const std::string &name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    void CShader::setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void CShader::setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void CShader::setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void CShader::setUinform1i(const std::string& name, GLint index) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), index);
    }
    CShader::~CShader() {
        glDeleteProgram(this->ID);
    }

    void checkCompileErrors(unsigned int id, CompileType type) {
        int success;
        static char infoLog[512];
        if (type == CompileType::SHADER) {
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(id, sizeof(infoLog), nullptr, infoLog);
                std::cout << "[ERROR] Shader Compile faild:" << infoLog << std::endl;
            }
        } else {
            glGetProgramiv(id, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(id, sizeof(infoLog), nullptr, infoLog);
                std:: cout << "[ERROR] Program Link faild:" << infoLog << std::endl;
            }
        }
    }
}
