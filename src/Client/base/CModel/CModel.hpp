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
#include <map>

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
        // void updateAnimationBoneMat();
        // 处理动画
        void processAnimate(const aiScene* scene);
        
        void SetUpTransaction();

        // 获取父结点变换矩阵
        void GenTransaction(Bone& bone, int f, Animation animation);
    public:
        // 模型网格
        std::vector<CMesh> meshes;
        // 模型路径
        std::string directory;
    private:
        // 骨骼offset矩阵
        std::vector<Bone> bones;
        // 骨骼id和name的映射
        std::map<std::string, uint32_t> BoneMap;
        // 加载模型的import对象
        std::shared_ptr<Assimp::Importer> m_pImporter;
        // 模型的场景指针, 不需要手动析构, importer析构会析构此对象
        const aiScene* pScene;

        // 矩阵是否初始化
        std::vector<bool> BoneIsSetUp;
        // 变换矩阵, 用来传给着色器用的
        std::vector<glm::mat4> BoneTransaform;
        // 变换矩阵,
        std::vector<glm::mat4> TmpBoneTransaform;

        // 当前动作
        uint32_t current = 3;
        // 倍速播放
        float speed = 1.0;
        
        std::vector<Animation> animationList;

        double time;

        double start_time = 0;
        // 暂未实现
        glm::vec3 angle;
        glm::vec3 postion;

    };
}

#endif //ENGINE_CMODEL_HPP
