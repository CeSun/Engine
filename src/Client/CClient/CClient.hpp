//
// Created by SunCe on 2020/2/1.
//

#ifndef ENGINE_CCLIENT_HPP
#define ENGINE_CCLIENT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Client/CShaderMgr/CShaderMgr.hpp>
#include <Client/CWorld/CWorld.hpp>
#include <Client/CTextureMgr/CTextureMgr.hpp>
#include <Client/CLightMgr/CLightMgr.hpp>
#include <Client/base/CCamera/CCamera.hpp>
#include <Common/TSingleton/TSingleton.hpp>
#include <CPage/CPage.hpp>

// 状态

#define DRAW_PAGE (1 << 0)
#define DRAW_WORLD (1 << 1)

namespace GameClient {

    class CClient: public TSingleton <CClient> {
    public:
        // 析构函数
        virtual ~CClient();
        // 执行游戏
        void run ();
    public:        // methods
        // 构造函数
        CClient();
        // 客户端初始化
        int init();
        // 处理输入
        void processInput();
        // 处理鼠标移动
        void mouse_move(double x,double y);

        void close_client();

    private:             // attribute
        GLFWwindow* engineWindow = nullptr;
        const static int major = 3;
        const static int minor = 3;
        const static int width = 1024;
        const static int height = 768;
        bool is_show_mouse = true;
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    public:
        // 获取着色器管理对象
        CShaderMgr& get_shadermgr() {
            return shadermgr;
        }
        // 获取纹理管理对象
        CTextureMgr& get_texturemgr() {
            return texturemgr;
        }

        double getTime() const {
            return now;
        }
    private:
        // 着色器管理对象
        CShaderMgr shadermgr;
        // 纹理管理对象
        CTextureMgr texturemgr;
        // 光源管理对象
        CLightMgr lightMgr;
        // 世界对象
        CWorld world;
        // 界面对象
        CPage page;
        //
        double now;

        // 绘制状态
        int DrawState;
    };

}

#endif //ENGINE_CCLIENT_HPP
