//
// Created by 孙策 on 2020/2/29.
//

#ifndef ENGINE_CWORLD_HPP
#define ENGINE_CWORLD_HPP

#include <vector>
#include <Client/base/CEntity/CEntity.hpp>
#include <Client/base/CCamera/CCamera.hpp>
#include <memory>
#include <Client/base/CSkyBox/CSkyBox.hpp>
#include <Client/base/CLight/CLight.hpp>
#include <GLFW/glfw3.h>
#include <map>
#include <vector>
#include <base/CCube/CCube.hpp>

namespace GameClient {
    class CWorld {
    public:
        void init(GLFWwindow* engineWindow);

        void draw();

        void load();
        

        void process_input();

        void mouse_move(double xpos, double ypos);

    private:
        void DrawFirstModel();
        std::vector<CEntity> EntityList;
        std::shared_ptr<CCamera> camera;
        std::shared_ptr<CSkyBox> skybox;
        std::shared_ptr<CModel> CurrentModel;
        GLFWwindow* engineWindow;
        int ClientPlayer = -1;

        int state = 0;
        double time;
        void reload();

        void shot();
        
        std::map<int, double> PlayTime;
        std::vector<std::shared_ptr<CCube>> CubeList;
    };
};



#endif //ENGINE_CWORLD_HPP
