#include "MenuScreen.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include <iostream>
#include "GameObjectManager.h"
#include "GraphicsEngine.h"
#include "VertexShader.h"

MenuScreen::MenuScreen() : AUIScreen("MenuScreen")
{

}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::drawUI()
{

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Exit Editor", "Ctrl+W")) {/*Do something */ }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Game Object")) {
			if (ImGui::MenuItem("Create Sphere")) { this->OnCreateSphereClicked(); }
			if (ImGui::MenuItem("Create Cube")) { this->OnCreateCubeClicked(); }
			if (ImGui::MenuItem("Create Physics Cube")) { this->OnCreatePhysicsCubeClicked(); }
			if (ImGui::MenuItem("Create Plane")) { this->OnCreatePlaneClicked(); }
			if (ImGui::MenuItem("Create Physics Plane")) { this->OnCreatePhysicsPlaneClicked(); }
			if (ImGui::BeginMenu("Light")) {
				if (ImGui::MenuItem("Point Light")) { /* Do stuff */ }
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void MenuScreen::OnCreateCubeClicked()
{
	//initialize vertex for object
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	VertexShader* vertexShader = graphEngine->createVertexShader(shaderByteCode, sizeShader);

	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::CUBE, shaderByteCode, sizeShader);

	vertexShader->release();
}

void MenuScreen::OnCreateSphereClicked()
{
	std::cout << "Creating sphere placeholder. \n";
}

void MenuScreen::OnCreatePlaneClicked()
{
	//initialize vertex for object
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	VertexShader* vertexShader = graphEngine->createVertexShader(shaderByteCode, sizeShader);

	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::PLANE, shaderByteCode, sizeShader);

	vertexShader->release();
}

void MenuScreen::OnCreatePhysicsCubeClicked()
{
	//initialize vertex for object
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	VertexShader* vertexShader = graphEngine->createVertexShader(shaderByteCode, sizeShader);

	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::PHYSICS_CUBE, shaderByteCode, sizeShader);

	vertexShader->release();
}

void MenuScreen::OnCreatePhysicsPlaneClicked()
{
	//initialize vertex for object
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	VertexShader* vertexShader = graphEngine->createVertexShader(shaderByteCode, sizeShader);

	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::PHYSICS_PLANE, shaderByteCode, sizeShader);

	vertexShader->release();
}
