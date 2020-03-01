//
// Created by SunCe on 2020/2/19.
//

#ifndef ENGINE_CCAMERA_HPP
#define ENGINE_CCAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GameClient{
    class CCamera {
    public:
        CCamera(glm::vec3 position, float pitch,float yaw, glm::vec3 worldup);
        // 获取观察矩阵
        glm::mat4 getViewMatrix();
        void upDateCameraMatrix();
        ~CCamera();

        // setter getter

        void setPitch(float pitch);
        float getPitch();
        void setYaw(float yaw);
        float getYaw();
        void setPosition(glm::vec3 position);
        glm::vec3 getPosition() {
            return position;
        }
    protected:
    private:
    private:
        glm::vec3 position;
        glm::vec3 forword;
        glm::vec3 right;
        glm::vec3 up;
        glm::vec3 worldUp;
        float pitch;
        float yaw;
        // glm::mat4 GetViewMatrix;
    };

}


#endif //ENGINE_CCAMERA_HPP
