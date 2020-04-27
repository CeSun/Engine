//
// Created by CeSun on 2020/2/29.
//

#include <iostream>
#include <CClient/CClient.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CModel.hpp"

namespace GameClient {
    CModel::CModel(const std::string& path, bool gamma) {
        loadModel(path);
    }
    void CModel::Draw(std::shared_ptr<const CShader> shader)
    {
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(70.0f, 1.0f, 100.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        CClient::intance().get_shadermgr().setMat4("model", model);

        for (unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);
    }
    void CModel::loadModel(const std::string& path)
    {
        // 读入模型
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        // 检查错误
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return;
        }
        // 模型所在路径
        directory = path.substr(0, path.find_last_of('/'));
        // 处理模型节点
        processNode(scene->mRootNode, scene);
    }

    void CModel::processNode(aiNode* node, const aiScene* scene)
    {
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
        // data to fill
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        // Walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.

            // 针对 半条命模型的特殊处理
            // positions
            vector.x = mesh->mVertices[i].y;
            vector.y = mesh->mVertices[i].z;
            vector.z = mesh->mVertices[i].x;
            vertex.Position = vector;
            // normals
            vector.x = mesh->mNormals[i].y;
            vector.y = mesh->mNormals[i].z;
            vector.z = mesh->mNormals[i].x;

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
            vector.x = mesh->mTangents[i].y;
            vector.y = mesh->mTangents[i].z;
            vector.z = mesh->mTangents[i].x;
            vertex.Tangent = vector;
            // bitangent
            vector.x = mesh->mBitangents[i].y;
            vector.y = mesh->mBitangents[i].z;
            vector.z = mesh->mBitangents[i].x;
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
        // 处理骨骼
        if (mesh->HasBones()) {
            for (uint32_t i = 0; i < mesh->mNumBones; i++) {
                aiBone* bone = mesh->mBones[i];
                
            }
        }


        // 返回网格对象
        return CMesh(vertices, indices, textures);
    }

    std::vector<Texture> CModel::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
    {
        std::vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            Texture texture;
            std::cout << directory + "/" + std::string(str.C_Str()) << std::endl;
            texture.poTexture = CClient::intance().get_texturemgr().add_texture(directory + "/" +std::string(str.C_Str()));;
            // texture.poTexture = CClient::intance().get_texturemgr().add_texture("resource/model/nanosuit/arm_dif.png");;
            texture.Type = typeName;
            textures.push_back(texture);
        }

        return textures;
    }



}