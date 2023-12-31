#include "MenuScreen.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include <iostream>
#include "GameObjectManager.h"
#include "GraphicsEngine.h"
#include "VertexShader.h"
#include "ShaderLibrary.h"
#include "SceneReader.h"
#include "SceneWriter.h"

MenuScreen::MenuScreen() : AUIScreen("MenuScreen")
{
	saveFileDialog = new ImGui::FileBrowser(ImGuiFileBrowserFlags_EnterNewFilename);
	saveFileDialog->SetTitle("Save Scene");
	saveFileDialog->SetTypeFilters({ ".level" });

	openFileDialog = new ImGui::FileBrowser();
	openFileDialog->SetTitle("Open Scene");
	openFileDialog->SetTypeFilters({ ".level" });

	openYAMLFileDialog = new ImGui::FileBrowser();
	openYAMLFileDialog->SetTitle("Open YAML Scene");
	openYAMLFileDialog->SetTypeFilters({ ".unity" });
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::drawUI()
{

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Open..", "Ctrl+O")) 
			{ 
				openFileDialog->Open();
			}
			if (ImGui::MenuItem("Open Scene YAML..", "Ctrl+O"))
			{
				openYAMLFileDialog->Open();
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) 
			{ 
				saveFileDialog->Open();
			}
			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) 
			{ 
				saveFileDialog->Open();
			}
			if (ImGui::MenuItem("Exit Editor", "Ctrl+W")) {/*Do something */ }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Game Object")) {
			if (ImGui::MenuItem("Create Sphere")) { this->OnCreateSphereClicked(); }
			if (ImGui::MenuItem("Create Cube")) { this->OnCreateCubeClicked(); }
			if (ImGui::MenuItem("Create Textured Cube")) { this->OnCreateTexturedCubeClicked(); }
			if (ImGui::MenuItem("Create Placeholder Physics Cube")) { this->OnPhysicsCubeClicked(); }
			if (ImGui::MenuItem("Create Plane")) { this->OnCreatePlaneClicked(); }
			if (ImGui::MenuItem("Create Placeholder Physics Plane")) { this->OnPhysicsPlaneClicked(); }
			if (ImGui::BeginMenu("Light")) {
				if (ImGui::MenuItem("Point Light")) { /* Do stuff */ }
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Components")) {
			if (ImGui::MenuItem("Rigid Body")) { this->OnRigidBodyComponentClicked(); }
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
		openFileDialog->Display();
		openYAMLFileDialog->Display();
		saveFileDialog->Display();

		if (openFileDialog->HasSelected())
		{
			// Full File Path fileDialog.GetSelected().string()
			//std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;

			SceneReader* reader = new SceneReader(openFileDialog->GetSelected().string());
			reader->readFromFile();
			openFileDialog->ClearSelected();
			openFileDialog->Close();
		}
		if (openYAMLFileDialog->HasSelected())
		{
			SceneReader* reader = new SceneReader(openYAMLFileDialog->GetSelected().string());
			reader->readFromYAMLFile();
			openYAMLFileDialog->ClearSelected();
			openYAMLFileDialog->Close();
		}

		if (saveFileDialog->HasSelected())
		{
			// Full File Path fileDialog.GetSelected().string()
			//std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
			SceneWriter* file = new SceneWriter();
			file->setDirectory(saveFileDialog->GetSelected().string());
			file->writeToFile();
			saveFileDialog->ClearSelected();
			saveFileDialog->Close();
		}
	}
}

void MenuScreen::OnCreateCubeClicked()
{
	//initialize vertex for object
	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::CUBE);
}

void MenuScreen::OnCreateTexturedCubeClicked()
{
	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::TEXTURED_CUBE);
}

void MenuScreen::OnCreateSphereClicked()
{
	std::cout << "Creating sphere placeholder. \n";
}

void MenuScreen::OnCreatePlaneClicked()
{
	//initialize vertex for object
	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::PLANE);
}

void MenuScreen::OnRigidBodyComponentClicked()
{
	std::cout << "Creating rigid body placeholder. \n";
}

void MenuScreen::OnPhysicsCubeClicked()
{
	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::PHYSICS_CUBE);
}

void MenuScreen::OnPhysicsPlaneClicked()
{
	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::PHYSICS_PLANE);
}
