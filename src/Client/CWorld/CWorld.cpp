//
// Created by 孙策 on 2020/2/29.
//

#include "CWorld.hpp"
#include <Client/CClient/CClient.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
std::shared_ptr<GameClient::CCamera> globalCamera;

glm::vec3 glPosition(1.0);
glm::vec3 glFront(1.0);
glm::vec3 glRight(1.0);


namespace GameClient {
	void CWorld::draw() {
		glm::mat4 view = camera->GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)1024 / (float)768, 0.1f, 15000.0f);
		glm::mat4 worldarea(1.0);
		worldarea = glm::scale(worldarea, glm::vec3(1.0, 1.0, 0.5));
		worldarea = glm::translate(worldarea, glm::vec3(0.0f, 0.0f, 0.25f));
		CClient::instance().get_shadermgr().setMat4("view", view);
		CClient::instance().get_shadermgr().setVec3("viewPos", camera->Position);
		CClient::instance().get_shadermgr().setMat4("projection", projection);
		CClient::instance().get_shadermgr().setMat4("worldarea", worldarea);
		
		// 绘制skybox
		skybox->draw();
		// 遍历实体，并且绘制
		int index = 0;
		for (auto iter : EntityList) {
			if (index == ClientPlayer)
				continue;
			iter.Draw();
		}
		for (auto iter : CubeList) {
			iter->draw();
		}
		// 如果有本地玩家实体，则绘制第一人称模型
		if (ClientPlayer >= 0)
			DrawFirstModel();
		
	}
	void CWorld::init(GLFWwindow* engineWindow) {
		this->engineWindow = engineWindow;
		load();
		// CClient::instance().show_world();
	}


	void CWorld::mouse_move(double xpos, double ypos) {
		if (this->ClientPlayer >= 0) {
			EntityList[ClientPlayer].SetAngle(glm::vec3(0.0, -1* camera->Yaw,0.0));
			camera->Pitch;
			
		}

	}
	void CWorld::load() {
		std::shared_ptr<CModel> player = std::make_shared<CModel>("resource/model/player/sas/sas.mdl");
		for (int i = 0; i < 20; i++) {
			std::shared_ptr<const CTexture> texture = CClient::instance().get_texturemgr().add_texture("resource/texture/TDtps0247.jpg");
			std::shared_ptr<CCube> cube = std::make_shared<CCube>(*texture,   glm::vec3(((i-10) / 5) * 200, 0, ((i - 10) % 5) * 200), glm::vec3(100, 10, 100));
			CubeList.push_back(cube);
		}
		CEntity entity;
		entity.SetModel(player);
		entity.SetPosition(glm::vec3(-200.0, 50.0, -200.0));
		entity.SetAngle(glm::vec3(0.0,-20.0,0.0));
		entity.SetAnimation(1);
		// 设置本地玩家实体id为1
		this->ClientPlayer = EntityList.size();
		EntityList.push_back(entity);
		camera = std::make_shared<CCamera>(glm::vec3(100.0, 100.0, -40.0));
		skybox = std::make_shared<CSkyBox>("pm");
		CurrentModel = std::make_shared<CModel>("resource/model/V_M4A1/V_M4A1.mdl");
		PlayTime[1] = 0.3;
		PlayTime[4] = 3.0;
		PlayTime[0] = 5.0;
		globalCamera = camera;
		std::shared_ptr<CLight> light = std::make_shared<CLight>(CLight::LIGHTTYPE_POINT, glm::vec3(1.0, 1.0, 1.0), glm::vec3(-100.0, 400.0, -40.0));
		std::shared_ptr<CLight> light2 = std::make_shared<CLight>(CLight::LIGHTTYPE_POINT, glm::vec3(1.0, 1.0, 1.0), glm::vec3(-200, 400.0, -150));
		CClient::instance().get_lightmgr().add_light("light", light);
		CClient::instance().get_lightmgr().add_light("light2", light2);
		CurrentModel->SetAnimation(0);
	}


	void CWorld::DrawFirstModel() {
		if (CurrentModel) {
			std::shared_ptr<const CShader> shader = CClient::instance().get_shadermgr().add_shader("resource/Shader/first/shader.vs", "resource/Shader/first/shader.fs");
			glm::mat4 view_model(1.0);
			view_model =  glm::rotate(view_model, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
			view_model = glm::translate(view_model, glm::vec3(3.0, 0.0, 0.0));
			glm::mat4 worldarea(1.0);
			worldarea = glm::scale(worldarea, glm::vec3(1.0, 1.0, 0.5));
			worldarea = glm::translate(worldarea, glm::vec3(0.0f, 0.0f, -0.25f));
			CClient::instance().get_shadermgr().setMat4("worldarea", worldarea);
			CClient::instance().get_shadermgr().setMat4("view_model", view_model);

			glm::vec3 position = EntityList[ClientPlayer].GetPosition();
			glm::vec3 angle = EntityList[ClientPlayer].GetAngle();

			glm::mat4 model(1.0f);
			model = glm::translate(model, position);
			model = glm::rotate(model, glm::radians(angle.x), glm::vec3(1.0, 0.0, 0.0));
			model = glm::rotate(model, glm::radians(angle.y), glm::vec3(0.0, 1.0, 0.0));
			model = glm::rotate(model, glm::radians(angle.z), glm::vec3(0.0, 0.0, 1.0));
			CClient::instance().get_shadermgr().setMat4("model", model);
			shader->use();
			CurrentModel->Draw(shader);
			if (CClient::instance().getTime() - time > PlayTime[state]) {
				time = CClient::instance().getTime();
				state = 0;
			}
		}
	}


	void CWorld::process_input() {

		if (this->ClientPlayer >= 0) {
			static double last_time = CClient::instance().getTime();
			double now = CClient::instance().getTime();

			glm::vec3 position = EntityList[ClientPlayer].GetPosition();
			glm::vec3 angle = EntityList[ClientPlayer].GetAngle();
			
			float speed = 100.0;
			bool isMove = 0;
			float slot = speed * (now - last_time);
			last_time = now;
			glm::vec3 front = camera->Front;
			glm::vec3 right = camera->Right;
			right.y = 0;
			front.y = 0;
			if (glfwGetKey(this->engineWindow, GLFW_KEY_W) == GLFW_PRESS) {
				// camera->Front 
				position += front * (float)slot;
				isMove = 1;
			}

			if (glfwGetKey(this->engineWindow, GLFW_KEY_S) == GLFW_PRESS) {
				position -= front * (float)slot;
				isMove = 1;

			}
			if (glfwGetKey(this->engineWindow, GLFW_KEY_A) == GLFW_PRESS) {
				position -= right * (float)slot;
				isMove = 1;

			}
			if (glfwGetKey(this->engineWindow, GLFW_KEY_D) == GLFW_PRESS) {
				position += right * (float)slot;
				isMove = 1;

			}
			if (glfwGetKey(this->engineWindow, GLFW_KEY_R) == GLFW_PRESS) {
				reload();
			}

			if (glfwGetKey(this->engineWindow, GLFW_KEY_F) == GLFW_PRESS) {
				shot();
			}
			EntityList[ClientPlayer].SetPosition(position);
			glPosition = position;
			glFront = camera->Front;
			glRight = camera->Right;
			position.y += 50;
			camera->Position = position;
			if (isMove == 0) {
				EntityList[ClientPlayer].SetAnimation(1);
			}
			else {
				EntityList[ClientPlayer].SetAnimation(3);
			}
		}
		else
		{

			if (glfwGetKey(this->engineWindow, GLFW_KEY_W) == GLFW_PRESS) {
				camera->ProcessKeyboard(FORWARD, 0.5);
			}

			if (glfwGetKey(this->engineWindow, GLFW_KEY_S) == GLFW_PRESS) {
				camera->ProcessKeyboard(BACKWARD, 0.5);

			}
			if (glfwGetKey(this->engineWindow, GLFW_KEY_A) == GLFW_PRESS) {
				camera->ProcessKeyboard(LEFT, 0.5);

			}
			if (glfwGetKey(this->engineWindow, GLFW_KEY_D) == GLFW_PRESS) {
				camera->ProcessKeyboard(RIGHT, 0.5);
			}
		}
	}

	void CWorld::reload() {
		if (state == 0) {
			state = 4;
			time = CClient::instance().getTime();
			CurrentModel->SetAnimation(4);
			CurrentModel->play();
		}
	}
	void CWorld::shot() {
		if (state == 0) {
			state = 1;
			time = CClient::instance().getTime();
			CurrentModel->SetAnimation(1);
			CurrentModel->play();
		}
	}
}