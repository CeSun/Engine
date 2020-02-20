//
// Created by SunCe on 2020/2/19.
//

#include "CCamera.hpp"


namespace GameClient {

    CCamera::CCamera(glm::vec3 position, float pitch,float yaw, glm::vec3 worldup) {
        this->position = position;
        this->worldUp = worldup;
        this->pitch = pitch;
        this->yaw = yaw;
        upDateCameraMatrix();
    }
    glm::mat4 CCamera::getViewMatrix() {
        return glm::lookAt(position,position+forword,worldUp);
    }

    void CCamera::upDateCameraMatrix() {
        forword.x = glm::cos(pitch) * glm::sin(yaw);
        forword.y = glm::sin(pitch);
        forword.z = glm::cos(pitch) * glm::cos(yaw);
        right = glm::normalize(glm::cross(forword, worldUp));
        up = glm::normalize(glm::cross(forword,right));
    }
    void CCamera::setPitch(float pitch) {
        this->pitch = pitch;
        if (this->pitch > glm::radians(90.0f)) {
            this->pitch =  glm::radians(90.0f);
        }
        else if (this->pitch <  glm::radians(-90.0f)) {
            this->pitch =  glm::radians(-90.0f);
        }


    }
    void CCamera::setYaw(float yaw) {
        this->yaw = yaw;
    }
    void CCamera::setPosition(glm::vec3 position) {
        this->position = position;
    }


    float CCamera::getPitch(){
        return this->pitch;
    }
    float CCamera::getYaw() {
        return this->yaw;
    }
    CCamera::~CCamera() {
    }
}