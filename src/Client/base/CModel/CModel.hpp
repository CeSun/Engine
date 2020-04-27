//
// Created by 孙策 on 2020/2/29.
//

#ifndef ENGINE_CMODEL_HPP
#define ENGINE_CMODEL_HPP
#include <vector>
#include <string>
#include "CMesh/CMesh.hpp"
#include <base/CShader/CShader.hpp>
#include <stb/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "CModel.hpp"
#include <memory>


namespace GameClient {
    class CModel {
    public:
        // 构造函数
        CModel(const std::string& path, bool gamma = false);
        // 绘制函数
        void Draw(std::shared_ptr<const CShader> shader);
    private:
        // 加载模型
        void loadModel(const std::string& path);
        // 处理节点
        void processNode(aiNode* node, const aiScene* scene);
        // 处理网格
        CMesh processMesh(aiMesh* mesh, const aiScene* scene);
        // 加载模型纹理
        std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);

    public:
        // 模型网格
        std::vector<CMesh> meshes;
        // 模型路径
        std::string directory;


        bool gammeCorrection;
    private:
        glm::vec3 angle;
        glm::vec3 postion;
    };
}

#endif //ENGINE_CMODEL_HPP
