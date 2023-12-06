#pragma once
#include "AUIScreen.h"
#include <imgui.h>
#include <imfilebrowser.h>
class MenuScreen : public AUIScreen
{
private:
	MenuScreen();
	~MenuScreen();

	virtual void drawUI() override;
	void OnCreateCubeClicked();
	void OnCreateTexturedCubeClicked();
	void OnCreateSphereClicked();
	void OnCreatePlaneClicked();

	void OnRigidBodyComponentClicked();
	void OnPhysicsCubeClicked();
	void OnPhysicsPlaneClicked();

	friend class UIManager;

	bool isOpen = false;

	ImGui::FileBrowser* openFileDialog;
	ImGui::FileBrowser* openYAMLFileDialog;
	ImGui::FileBrowser* saveFileDialog;

};

