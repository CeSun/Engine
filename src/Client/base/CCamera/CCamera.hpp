//
// Created by SunCe on 2020/2/19.
//


#ifndef ENGINE_CCAMERA_HPP
#define ENGINE_CCAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

namespace GameClient{
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    const float YAW         = -90.0f;
    const float PITCH       =  0.0f;
    const float SPEED       =  2.5f;
    const float SENSITIVITY =  0.1f;
    const float ZOOM        =  55.0f;

    class CCamera {
    public:
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
        // 欧拉角
        float Yaw;
        float Pitch;
        // 相机参数
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

        CCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 1.0f, 0.0f)), MovementSpeed(SPEED),
                                                        MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
            Position = position;
            WorldUp = up;
            Yaw = yaw;
            Pitch = pitch;
            updateCameraVectors();
        }

        // 通过角度值构造
        CCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(
                glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
            Position = glm::vec3(posX, posY, posZ);
            WorldUp = glm::vec3(upX, upY, upZ);
            Yaw = yaw;
            Pitch = pitch;
            updateCameraVectors();
        }

        // 获取观察矩阵
        glm::mat4 GetViewMatrix() {
            return glm::lookAt(Position, Position + Front, Up);
        }

        // 处理输入(使用枚举屏蔽硬件)
        void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
            float velocity = MovementSpeed * deltaTime * 50;
            if (direction == FORWARD)
                Position += Front * velocity;
            if (direction == BACKWARD)
                Position -= Front * velocity;
            if (direction == LEFT)
                Position -= Right * velocity;
            if (direction == RIGHT)
                Position += Right * velocity;
        }

        // (处理鼠标的 位移)
        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
            xoffset *= MouseSensitivity;
            yoffset *= MouseSensitivity;
            Yaw += xoffset;
            Pitch += yoffset;
            // 防止万向死循环
            if (constrainPitch) {
                if (Pitch > 89.0f)
                    Pitch = 89.0f;
                if (Pitch < -89.0f)
                    Pitch = -89.0f;
            }

            // 更新矩阵
            updateCameraVectors();
        }

        // 处理鼠标灵敏度缩放
        void ProcessMouseScroll(float yoffset) {
            if (Zoom >= 1.0f && Zoom <= 45.0f)
                Zoom -= yoffset;
            if (Zoom <= 1.0f)
                Zoom = 1.0f;
            if (Zoom >= 45.0f)
                Zoom = 45.0f;
        }

    private:
        void updateCameraVectors() {
            // Calculate the new Front vector
            glm::vec3 front;
            front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            front.y = sin(glm::radians(Pitch));
            front.z = sin(glm::radians(Yaw))* cos(glm::radians(Pitch));
            Front = glm::normalize(front);
            // Also re-calculate the Right and Up vector
            Right = glm::normalize(glm::cross(Front,
                                              WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            Up = glm::normalize(glm::cross(Right, Front));
        }
    };
}



#endif //ENGINE_CCAMERA_HPP
