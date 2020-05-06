//
// Created by 孙策 on 2020/2/29.
//

#include "CEntity.hpp"
#include <Client/CClient/CClient.hpp>

namespace GameClient {

    void CEntity::SetAngle(glm::vec3 angle) {
        this->angle = angle;
    }

    void CEntity::SetPosition(glm::vec3 position) {
        this->position = position;
    }

    void CEntity::SetModel(std::shared_ptr<CModel> model) {
        this->model = model;
    }

    void CEntity::SetAnimation(int index) {
        this->current = index;
    }

    void CEntity::Draw() {
        if (this->model) {
            std::shared_ptr<const CShader> shader = CClient::instance().get_shadermgr().add_shader("resource/Shader/model/shader.vs", "resource/Shader/model/shader.fs");
            glm::mat4 model(1.0f);
            model = glm::translate(model, position);
            model = glm::rotate(model,glm::radians(angle.x), glm::vec3(1.0,0.0, 0.0));
            model = glm::rotate(model, glm::radians(angle.y), glm::vec3(0.0, 1.0, 0.0));
            model = glm::rotate(model, glm::radians(angle.z), glm::vec3(0.0, 0.0, 1.0));
            shader->use();
            shader->setMat4("model", model);
            this->model->SetAnimation(current);
            this->model->Draw(shader);
        }
    }
}