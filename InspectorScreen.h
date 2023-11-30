#pragma once
#include "AUIScreen.h"
#include <imgui.h>
#include <imfilebrowser.h>
#include "Texture.h"

class AGameObject;
class InspectorScreen : public AUIScreen
{
public:
	void SendResult(String materialPath);

private:
	InspectorScreen();
	~InspectorScreen();

	void onTransformUpdate();
	virtual void drawUI() override;
	void drawMaterialsTab();
	void FormatMatImage();
	void updateTransformDisplays();
	void deleteSelected();
	friend class UIManager;

	float positionDisplay[3] = { 0.0f, 0.0f, 0.0f };
	float rotationDisplay[3] = { 0.0f, 0.0f, 0.0f };
	float scaleDisplay[3] = { 1.0f, 1.0f, 1.0f };

	AGameObject* selectedObject = NULL;

	bool popupOpen = false;
	ImGui::FileBrowser* openFileDialog;
	String materialPath, materialName;
	Texture* materialDisplay;
};

