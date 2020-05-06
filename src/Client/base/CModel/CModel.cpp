//
// Created by CeSun on 2020/2/29.
//

#include <iostream>
#include <CClient/CClient.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CModel.hpp"
#include <Common/CLog/CLog.hpp>
#include <glm/gtc/quaternion.hpp>

namespace GameClient {
    glm::mat4 aiMat4ToGlmMat4(aiMatrix4x4 aiMat4); glm::mat4 BoneTransform(glm::vec3 postion, glm::vec3 scaling, glm::quat rotate);

    void GL_ConcatTransforms(glm::mat4 mat1, glm::mat4 mat2, glm::mat4& dest);
    CModel::CModel(const std::string& path, bool gamma) {
        loadModel(path);
    }
    void CModel::Draw(std::shared_ptr<const CShader> shader)
    {
        // 时间
        this->time = CClient::instance().getTime();
        // 计算动作矩阵
        SetUpTransaction();
        shader->use();
        shader->setInt("TransFormNum", this->BoneTransaform.size());
        shader->setMat4("TransForm", BoneTransaform[0], BoneTransaform.size());
        for (unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);


        // meshes[5].Draw(shader);
    }
    void CModel::loadModel(const std::string& path)
    {
        // 读入模型
        m_pImporter = std::make_shared<Assimp::Importer>();

        pScene = m_pImporter->ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_PopulateArmatureData);
        // 检查错误
        if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode) // if is Not Zero
        {
            APP_LOG_ERROR("ERROR::ASSIMP::%s", m_pImporter->GetErrorString());
            return;
        }
        // 模型所在路径
        directory = path.substr(0, path.find_last_of('/'));
        // 处理模型节点
        processNode(pScene->mRootNode, pScene);
        // 处理动画
        processAnimate(pScene);
    }

    void CModel::processNode(aiNode* node, const aiScene* scene)
    {

        // 处理骨骼
        {
            auto iter = BoneMap.find(node->mName.C_Str());
            if (iter == BoneMap.end()) {
                Bone bone;
                bone.ID = bones.size();
                bone.Name = node->mName.C_Str();
                bone.LocalMat = aiMat4ToGlmMat4(node->mTransformation);
                bone.OffsetMat = glm::mat4(1.0);
                if (node->mParent == nullptr) {
                    bone.ParentId = -1;
                    bone.ParentName = "Error";
                    bone.Parent = nullptr;
                }
                else {
                    // 查找父骨骼id
                    auto iter2 = BoneMap.find(node->mParent->mName.C_Str());
                    if (iter2 != BoneMap.end()) {
                        bone.ParentId = iter2->second;
                        bone.ParentName = node->mParent->mName.C_Str();
                        bones[bone.ParentId].children.push_back(bone.ID);
                        bone.Parent = &bones[bone.ParentId];
                    }
                    else {
                        APP_LOG_ERROR("Not Found Bone[%s]", node->mParent->mName.C_Str());
                        bone.ParentId = -1;
                        bone.ParentName = "Error";
                        bone.Parent = nullptr;
                    }
                }

                // BoneTransaform.push_back(bone.GlobalMat);
                // 插入骨骼
                bones.push_back(bone);
                BoneMap.insert(std::make_pair(node->mName.C_Str(), bone.ID));
            }
        }

        // 遍历当前节点中所有的网格，并且加载贴图
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // the node object only contains indices to index the actual objects in the scene. 
            // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }
        // 递归处理子节点
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }

    }

    CMesh CModel::processMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector;

            // positions
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
            // normals
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].z;
            vector.z = mesh->mNormals[i].y;

            vertex.Normal = vector;
            // texture coordinates
            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            }
            else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
            vertices.push_back(vertex);


        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // 处理材质
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        // 1. 漫反射贴图
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. 镜面贴图
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. 法向量贴图
        std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        for (int i = 0; i < mesh->mNumBones; i ++ ) {
            aiBone* bone = mesh->mBones[i];
            auto iter = BoneMap.find(bone->mName.C_Str());
            if (iter != BoneMap.end()) {
                bones[iter->second].OffsetMat = aiMat4ToGlmMat4(bone->mOffsetMatrix);
                for (int j = 0; j < bone->mNumWeights; j++) {
                    aiVertexWeight& weight = bone->mWeights[j];
                    vertices[weight.mVertexId].Bone[vertices[weight.mVertexId].NumBones] = iter->second;
                    vertices[weight.mVertexId].Weight[vertices[weight.mVertexId].NumBones] = weight.mWeight;
                    vertices[weight.mVertexId].NumBones++;

                }
            }
        }
        return CMesh(vertices, indices, textures);
    }

    std::vector<Texture> CModel::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
    {
        std::vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);
            Texture texture;
            texture.poTexture = CClient::instance().get_texturemgr().add_texture(directory + "/" +std::string(str.C_Str()));;
            texture.Type = typeName;
            textures.push_back(texture);
        }

        return textures;
    }
    

    void CModel::processAnimate(const aiScene* scene) {
        if (scene->HasAnimations()) {
            // 遍历模型的所有动作
            for (uint32_t i = 0; i < scene->mNumAnimations; i++) {
                aiAnimation& roAnimation = *scene->mAnimations[i];
                Animation animation;
                animation.Duration = roAnimation.mDuration;
                animation.Ticks = roAnimation.mTicksPerSecond;
                // 遍历动作的骨骼变换向量/四元数
                for (uint32_t j = 0; j < roAnimation.mNumChannels; j++) {
                    aiNodeAnim& roNodeAnim = *roAnimation.mChannels[j];
                   
                    Channel channel;
                    
                    // 骨骼节点名称
                    channel.BoneName = roNodeAnim.mNodeName.C_Str();
                    auto boneIter = BoneMap.find(channel.BoneName);
                    if (boneIter != BoneMap.end()) {
                        channel.BoneId = boneIter->second;
                    }
                    else {
                        APP_LOG_ERROR("Bone [%s] is not found", channel.BoneName.c_str());
                        continue;
                    }
                    // TODO 通过当前骨骼获取父节点骨骼id
                    auto iter = BoneMap.find(roNodeAnim.mNodeName.C_Str());
                    if (iter == BoneMap.end()) {
                        channel.ParentId = -1;
                    } else {
                        auto parentiter = BoneMap.find(bones[iter->second].ParentName);
                        channel.ParentName = bones[iter->second].ParentName;
                        if (parentiter != BoneMap.end()) {
                            channel.ParentId = parentiter->second;
                        }
                        else {
                            channel.ParentId = -1;
                        }
                    }
                    // 遍历位移向量
                    for (uint32_t k = 0; k < roNodeAnim.mNumPositionKeys; k++) {
                        channel.PostionKeys.push_back(glm::vec3(roNodeAnim.mPositionKeys[k].mValue.x, roNodeAnim.mPositionKeys[k].mValue.y, roNodeAnim.mPositionKeys[k].mValue.z));
                    }
                    // 遍历缩放向量
                    for (uint32_t k = 0; k < roNodeAnim.mNumScalingKeys; k++) {
                        channel.ScalingKeys.push_back(glm::vec3(roNodeAnim.mScalingKeys[k].mValue.x, roNodeAnim.mScalingKeys[k].mValue.y, roNodeAnim.mScalingKeys[k].mValue.z));
                    }
                    // 遍历旋转四元数
                    for (uint32_t k = 0; k < roNodeAnim.mNumRotationKeys; k++) {
                        channel.RotationKeys.push_back(glm::quat(roNodeAnim.mRotationKeys[k].mValue.w, roNodeAnim.mRotationKeys[k].mValue.x, roNodeAnim.mRotationKeys[k].mValue.y, roNodeAnim.mRotationKeys[k].mValue.z));
                    }
                    animation.map.insert(std::make_pair(channel.BoneId, animation.Channels.size()));
                    animation.Channels.push_back(channel);
                }
                
                animationList.push_back(animation);
            }
        }
    }

    void CModel::play() {
        start_time = time;
    }
    void CModel::SetUpTransaction() {
        // 先算出当前帧和之后的帧
        // 算出对应的时间
        Animation& animation = animationList[this->current];
        double AnimationTime = animation.Duration / animation.Ticks / animation.Ticks;
        double GoonTime = time - start_time;
        // APP_LOG_INFO("AnimationTime: %lf, GoonTime: %lf, time: %lf", AnimationTime, GoonTime, time);
        
        if (current != 0 && is_loop == false) {
            if (GoonTime > AnimationTime) {
                current = 0;
                start_time = time;
                return SetUpTransaction();
            }
        }

        if (GoonTime > AnimationTime) {
            start_time = time;
        }
        GoonTime = time - start_time;
        int f1 =  (animation.Duration / animation.Ticks) * (GoonTime / AnimationTime);
        TmpBoneTransaform.resize(bones.size());
        BoneTransaform.resize(bones.size());
        for (auto iter : bones) {
            if (iter.ParentId == -1) {
                GenTransaction(iter, f1, animationList[current]);
            }
        }
    }

    void CModel::GenTransaction(Bone& bone, int f, Animation animation) {
        glm::mat4 mat;
        auto iter = animation.map.find(bone.ID);
        if (iter == animation.map.end()) {
            mat = bone.LocalMat;
        }
        else {
            mat = BoneTransform(animation.Channels[iter->second].PostionKeys[f], animation.Channels[iter->second].ScalingKeys[0], animation.Channels[iter->second].RotationKeys[f]) ;
        }

        if (bone.ParentId < 0) {
            TmpBoneTransaform[bone.ID] = mat; //bone.LocalMat;
            BoneTransaform[bone.ID] =  TmpBoneTransaform[bone.ID] * bone.OffsetMat;
        }
        else {
            TmpBoneTransaform[bone.ID] = TmpBoneTransaform[bone.ParentId] * mat;// bone.LocalMat;
            BoneTransaform[bone.ID] = TmpBoneTransaform[bone.ID]* bone.OffsetMat;
        }

        for (auto iter : bone.children) {
            bones[iter].ParentId = bone.ID;
            GenTransaction(bones[iter], f, animation);
        }
    }
       
    glm::mat4 aiMat4ToGlmMat4(aiMatrix4x4 aiMat4) {
        glm::mat4 glMat4;
#ifndef 行主序

        glMat4[0][0] = aiMat4.a1;
        glMat4[1][0] = aiMat4.a2;
        glMat4[2][0] = aiMat4.a3;
        glMat4[3][0] = aiMat4.a4;
        glMat4[0][1] = aiMat4.b1;
        glMat4[1][1] = aiMat4.b2;
        glMat4[2][1] = aiMat4.b3;
        glMat4[3][1] = aiMat4.b4;
        glMat4[0][2] = aiMat4.c1;
        glMat4[1][2] = aiMat4.c2;
        glMat4[2][2] = aiMat4.c3;
        glMat4[3][2] = aiMat4.c4;
        glMat4[0][3] = aiMat4.d1;
        glMat4[1][3] = aiMat4.d2;
        glMat4[2][3] = aiMat4.d3;
        glMat4[3][3] = aiMat4.d4;  

#else
        glMat4[0][0] = aiMat4.a1;
        glMat4[0][1] = aiMat4.a2;
        glMat4[0][2] = aiMat4.a3;
        glMat4[0][3] = aiMat4.a4;
        glMat4[1][0] = aiMat4.b1;
        glMat4[1][1] = aiMat4.b2;
        glMat4[1][2] = aiMat4.b3;
        glMat4[1][3] = aiMat4.b4;
        glMat4[2][0] = aiMat4.c1;
        glMat4[2][1] = aiMat4.c2;
        glMat4[2][2] = aiMat4.c3;
        glMat4[2][3] = aiMat4.c4;
        glMat4[3][0] = aiMat4.d1;
        glMat4[3][1] = aiMat4.d2;
        glMat4[3][2] = aiMat4.d3;
        glMat4[3][3] = aiMat4.d4;
#endif // 列主序
        return glMat4;
    }
    void GL_ConcatTransforms(glm::mat4 mat1, glm::mat4 mat2, glm::mat4& dest)
    {
        dest[0][0] = mat1[0][0] * mat2[0][0] + mat1[1][0] * mat2[0][1] + mat1[2][0] * mat2[0][2] + mat1[3][0] * mat2[0][3];
        dest[0][1] = mat1[0][1] * mat2[0][0] + mat1[1][1] * mat2[0][1] + mat1[2][1] * mat2[0][2] + mat1[3][1] * mat2[0][3];
        dest[0][2] = mat1[0][2] * mat2[0][0] + mat1[1][2] * mat2[0][1] + mat1[2][2] * mat2[0][2] + mat1[3][2] * mat2[0][3];
        dest[0][3] = mat1[0][3] * mat2[0][0] + mat1[1][3] * mat2[0][1] + mat1[2][3] * mat2[0][2] + mat1[3][3] * mat2[0][3];

        dest[1][0] = mat1[0][0] * mat2[1][0] + mat1[1][0] * mat2[1][1] + mat1[2][0] * mat2[1][2] + mat1[3][0] * mat2[1][3];
        dest[1][1] = mat1[0][1] * mat2[1][0] + mat1[1][1] * mat2[1][1] + mat1[2][1] * mat2[1][2] + mat1[3][1] * mat2[1][3];
        dest[1][2] = mat1[0][2] * mat2[1][0] + mat1[1][2] * mat2[1][1] + mat1[2][2] * mat2[1][2] + mat1[3][2] * mat2[1][3];
        dest[1][3] = mat1[0][3] * mat2[1][0] + mat1[1][3] * mat2[1][1] + mat1[2][3] * mat2[1][2] + mat1[3][3] * mat2[1][3];

        dest[2][0] = mat1[0][0] * mat2[2][0] + mat1[1][0] * mat2[2][1] + mat1[2][0] * mat2[2][2] + mat1[3][0] * mat2[2][3];
        dest[2][1] = mat1[0][1] * mat2[2][0] + mat1[1][1] * mat2[2][1] + mat1[2][1] * mat2[2][2] + mat1[3][1] * mat2[2][3];
        dest[2][2] = mat1[0][2] * mat2[2][0] + mat1[1][2] * mat2[2][1] + mat1[2][2] * mat2[2][2] + mat1[3][2] * mat2[2][3];
        dest[2][3] = mat1[0][3] * mat2[2][0] + mat1[1][3] * mat2[2][1] + mat1[2][3] * mat2[2][2] + mat1[3][3] * mat2[2][3];

        dest[3][0] = mat1[0][0] * mat2[3][0] + mat1[1][0] * mat2[3][1] + mat1[2][0] * mat2[3][2] + mat1[3][0] * mat2[3][3];
        dest[3][1] = mat1[0][1] * mat2[3][0] + mat1[1][1] * mat2[3][1] + mat1[2][1] * mat2[3][2] + mat1[3][1] * mat2[3][3];
        dest[3][2] = mat1[0][2] * mat2[3][0] + mat1[1][2] * mat2[3][1] + mat1[2][2] * mat2[3][2] + mat1[3][2] * mat2[3][3];
        dest[3][3] = mat1[0][3] * mat2[3][0] + mat1[1][3] * mat2[3][1] + mat1[2][3] * mat2[3][2] + mat1[3][3] * mat2[3][3];
    }



    void VectorCopy(glm::vec3 src, glm::vec3 dest)
    {
        dest[0] = src[0];
        dest[1] = src[1];
        dest[2] = src[2];
    }
    void GL_QuaternionMatrix(glm::quat quat, glm::mat4& mat)
    {
        float s, xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;

        s = 2.0 / (quat[0] * quat[0] + quat[1] * quat[1] + quat[2] * quat[2] + quat[3] * quat[3]);

        xs = quat[0] * s;
        ys = quat[1] * s;
        zs = quat[2] * s;

        wx = quat[3] * xs;
        wy = quat[3] * ys;
        wz = quat[3] * zs;

        xx = quat[0] * xs;
        xy = quat[0] * ys;
        xz = quat[0] * zs;

        yy = quat[1] * ys;
        yz = quat[1] * zs;

        zz = quat[2] * zs;

        mat[0][0] = 1.0 - (yy + zz);
        mat[1][0] = xy - wz;
        mat[2][0] = xz + wy;

        mat[0][1] = xy + wz;
        mat[1][1] = 1.0 - (xx + zz);
        mat[2][1] = yz - wx;

        mat[0][2] = xz - wy;
        mat[1][2] = yz + wx;
        mat[2][2] = 1.0 - (xx + yy);

        mat[3][0] = mat[3][1] = mat[3][2] = mat[0][3] = mat[1][3] = mat[2][3] = 0.0;
        mat[3][3] = 1.0;
    }


    glm::mat4 BoneTransform(glm::vec3 postion, glm::vec3 scaling, glm::quat rotate) {
        glm::mat4 result;
         //result = glm::scale(result, scaling);
         //result = result * glm::mat4_cast(rotate);
         //result = glm::translate(result, postion);
        // result = glm::mat4_cast(rotate);
        // GL_QuaternionMatrix(rotate, result);
        // VectorCopy(postion, result[3]);

       
        result = glm::mat4_cast(rotate);
        result[0][0] *= scaling.x;
        result[0][1] *= scaling.x;
        result[0][2] *= scaling.x;


        result[1][0] *= scaling.y;
        result[1][1] *= scaling.y;
        result[1][2] *= scaling.y;

        result[2][0] *= scaling.z;
        result[2][1] *= scaling.z;
        result[2][2] *= scaling.z;


        result[3][0] = postion.x;
        result[3][1] = postion.y;
        result[3][2] = postion.z;

        return result;
    }
}