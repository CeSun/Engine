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
namespace GameClient {
    class CCamera;
    class CClient {
    public:
        // 单例
        static CClient& intance();
        // 析构函数
        virtual ~CClient();
        // 执行游戏
        void run ();
    private:        // methods
        // 构造函数
        CClient();
        // 客户端初始化
        int init();
        // 处理输入
        void processInput();
        // 处理鼠标移动
        void mouse_move(double x,double y);

    private:             // attribute
        GLFWwindow* engineWindow = nullptr;
        const static int major = 3;
        const static int minor = 3;
        const static int width = 1024;
        const static int height = 768;
        bool is_show_mouse = true;
        friend void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    public:
        // 获取着色器管理对象
        CShaderMgr& get_shadermgr() {
            return shadermgr;
        }
        // 获取纹理管理对象
        CTextureMgr& get_texturemgr() {
            return texturemgr;
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
    };

    void mouse_callback(GLFWwindow* window, double xpos, double ypos);


}

#endif //ENGINE_CCLIENT_HPP
