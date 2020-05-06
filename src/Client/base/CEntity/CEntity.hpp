//
// Created by 孙策 on 2020/2/29.
//

#ifndef ENGINE_CENTITY_HPP
#define ENGINE_CENTITY_HPP

#include <glm/glm.hpp>
#include <base/CModel/CModel.hpp>
#include <memory>

namespace GameClient {
    class CEntity {
    public:
        void SetAngle(glm::vec3 angle);
        glm::vec3 GetAngle() { return angle; };

        void SetPosition(glm::vec3 position);

        glm::vec3 GetPosition() { return position; };

        void SetModel(std::shared_ptr<CModel> model);

        void SetAnimation(int index);

        void Draw();

        virtual ~CEntity() {};

    private:
        std::shared_ptr<CModel> model;

        glm::vec3 angle;
        glm::vec3 position;

        int current =0;
    };
};


#endif //ENGINE_CENTITY_HPP
