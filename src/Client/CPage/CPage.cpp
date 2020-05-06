
#include <Client/CClient/CClient.hpp>
#include "CPage.hpp"


extern glm::vec3 glPosition;

extern glm::vec3 glFront;
extern glm::vec3 glRight;


namespace GameClient {
	CPage::CPage() {

	}

	CPage::~CPage() {
	}
	std::shared_ptr<const CTexture> logo;

	void CPage::Draw() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//设置窗口位置
		static double Time = CClient::instance().getTime();
		if (CClient::instance().getTime() - Time > 3.0) {
			DrawMainPage();
		}
		else {
			DrawLogo();
		}


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void CPage::Init(GLFWwindow* window) {

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		io = &ImGui::GetIO(); 
		(void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsLight();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
		// ImGui::Im
		logo =  CClient::instance().get_texturemgr().add_texture("./resource/texture/logo.png");

	}


	void CPage::DrawMainPage() {
		ImGui::Begin("Game Control");
		ImGui::Text("WelCome! \nThis is a Demo of Lite Engine");

		ImGui::Text("Player Position:(x:%0.2f,y:%0.2f,z:%0.2f)", glPosition.x, glPosition.y, glPosition.z);
		ImGui::Text("Player Front:(x:%0.2f,y:%0.2f,z:%0.2f)", glFront.x, glFront.y, glFront.z);
		ImGui::Text("Player Right:(x:%0.2f,y:%0.2f,z:%0.2f)", glRight.x, glRight.y, glRight.z);

		
		ImGui::Button("Create");
		ImGui::Button("Options");
		if (ImGui::Button("Cancel")) {
			CClient::instance().close_page();
		}
		if (ImGui::Button("Exit")) {
			CClient::instance().close_client();
		}

		ImGui::End();
	}


	void CPage::DrawLogo() {
		static double last_time = CClient::instance().getTime();
		float cent = (CClient::instance().getTime() - last_time) / 1.5;
		if (cent > 1)
			cent = 1 -(cent - 1);
		ImGui::SetNextWindowPos(ImVec2((1024 - 300) / 2, (768 - 300) / 2), 0, ImVec2(0, 0));
		//设置窗口的大小
		ImGui::SetNextWindowSize(ImVec2(300, 300));
		//设置窗口为透明
		ImGui::SetNextWindowBgAlpha(0);
		// 设置窗口的padding为0是图片控件充满窗口
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		//设置窗口为无边框
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
		//创建窗口使其固定在一个位置
		ImGui::Begin("背景", NULL, ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoBringToFrontOnFocus |
			ImGuiWindowFlags_NoInputs |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoScrollbar);
		ImGui::Image((ImTextureID)logo->get_id(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0), ImVec4(1.0,1.0,1.0, cent));
		ImGui::End();
		ImGui::PopStyleVar(2);
	}

}