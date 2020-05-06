/*
 *  ��������ҳ��
 *
 */

#ifndef __CPAGE_HPP__
#define __CPAGE_HPP__
#include <Client/libraries/imgui/imgui.h>
#include <Client/libraries/imgui/imgui_impl_glfw.h>
#include <Client/libraries/imgui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include <Common/TSingleton/TSingleton.hpp>
namespace GameClient {
	class CPage: public TSingleton<CPage> {
    public:
        CPage();
        ~CPage() ;

        // ����
        void Draw();

        // ��ʼ��
        void Init(GLFWwindow* window);
    private:

        void DrawMainPage();

        void DrawLogo();
        ImGuiIO* io;

	};
}

#endif // __CPAGE_HPP__
