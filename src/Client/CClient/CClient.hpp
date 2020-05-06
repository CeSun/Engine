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

// ״̬

#define DRAW_PAGE (1 << 0)
#define DRAW_WORLD (1 << 1)

namespace GameClient {

    class CClient: public TSingleton <CClient> {
    public:
        // ��������
        virtual ~CClient();
        // ִ����Ϸ
        void run ();
    public:        // methods
        // ���캯��
        CClient();
        // �ͻ��˳�ʼ��
        int init();
        // ��������
        void processInput();
        // ��������ƶ�
        void mouse_move(double x,double y);

        void close_client();
        void show_world() {
            DrawState = DrawState | DRAW_WORLD;
        }
        void show_page() {
            DrawState = DrawState | DRAW_PAGE;
        }
        void close_world() {
            DrawState = DrawState & (~DRAW_WORLD);
        }
        void close_page() {
            DrawState = DrawState & (~DRAW_PAGE);
        }

    private:             // attribute
        GLFWwindow* engineWindow = nullptr;
        const static int major = 3;
        const static int minor = 3;
        const static int width = 1024;
        const static int height = 768;
        bool is_show_mouse = true;
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    public:
        // ��ȡ��ɫ���������
        CShaderMgr& get_shadermgr() {
            return shadermgr;
        }
        // ��ȡ����������
        CTextureMgr& get_texturemgr() {
            return texturemgr;
        }

        // ��ȡ����������
        CLightMgr& get_lightmgr() {
            return lightMgr;
        }
        double getTime() const {
            return now;
        }
    private:
        // ��ɫ���������
        CShaderMgr shadermgr;
        // ����������
        CTextureMgr texturemgr;
        // ��Դ�������
        CLightMgr lightMgr;
        // �������
        CWorld world;
        // �������
        CPage page;
        //
        double now;

        // ����״̬
        int DrawState;
    };

}

#endif //ENGINE_CCLIENT_HPP
