#include "InspectorScreen.h"
#include "imgui.h"
#include "GameObjectManager.h"
#include "UIManager.h"
#include "AGameObject.h"
#include "TextureManager.h"
#include "TexturedCube.h"
#include "ObjectRenderer.h"
#include "StringUtils.h"
#include "MaterialScreen.h"

void InspectorScreen::SendResult(String materialPath)
{
	TexturedCube* texturedObj = static_cast<TexturedCube*>(this->selectedObject);
	texturedObj->getRenderer()->setRenderer(materialPath);
	this->popupOpen = false;
}

InspectorScreen::InspectorScreen() : AUIScreen("InspectorScreen")
{
	openFileDialog = new ImGui::FileBrowser();
}

InspectorScreen::~InspectorScreen()
{
}

void InspectorScreen::drawUI()
{
	ImGui::Begin("Inspector Window");
	ImGui::SetWindowPos(ImVec2(Window::WINDOW_WIDTH - 275, 20));
	ImGui::SetWindowSize(ImVec2(250, Window::WINDOW_HEIGHT));
	this->selectedObject = GameObjectManager::getInstance()->getSelectedObject();
	if (this->selectedObject != NULL) {
		String name = this->selectedObject->getName();
		ImGui::Text("Selected Object: %s", name.c_str());

		this->updateTransformDisplays();
		bool enabled = this->selectedObject->isEnabled();
		if (ImGui::Button("Delete", ImVec2(0, 0))) { this->deleteSelected(); }
		if (ImGui::Checkbox("Enabled", &enabled)) { this->selectedObject->setEnabled(enabled); }
		if (ImGui::DragFloat3("Position", this->positionDisplay, .1f)) { this->onTransformUpdate(); }
		if (ImGui::DragFloat3("Rotation", this->rotationDisplay, .4f)) { this->onTransformUpdate(); }
		if (ImGui::DragFloat3("Scale", this->scaleDisplay, .4f)) { this->onTransformUpdate(); }

		if(selectedObject->getObjectType() == AGameObject::TEXTURED_CUBE)
			this->drawMaterialsTab();
	}
	else {
		ImGui::Text("No object selected. Select an object first.");
	}
	ImGui::End();
}

void InspectorScreen::drawMaterialsTab()
{
	int WINDOW_WIDTH = 225;
	int WINDOW_HEIGHT = 20;

	TexturedCube* texturedObj = static_cast<TexturedCube*>(this->selectedObject);
	this->materialPath = texturedObj->getRenderer()->getMaterialPath();
	this->FormatMatImage();
	ImGui::SetCursorPosX(50);
	ImGui::Image(static_cast<void*>(this->materialDisplay->getShaderResource()), ImVec2(150,150));
	std::vector<String> paths = StringUtils::split(this->materialPath, '\\');
	this->materialName = paths[paths.size() - 1];
	String displayText = "Material " + this->materialName;
	ImGui::Text(displayText.c_str());
	if (ImGui::Button("Add Material", ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT))) {
		this->popupOpen = !this->popupOpen;
		UINames uiNames;
		MaterialScreen* materialScreen = static_cast<MaterialScreen*>(UIManager::getInstance()->findUIByName(uiNames.MATERIAL_SCREEN));
		materialScreen->linkInspectorScreen(this, this->materialPath);
		UIManager::getInstance()->setEnabled(uiNames.MATERIAL_SCREEN, this->popupOpen);
	}
}

void InspectorScreen::FormatMatImage()
{
	//convert to wchar format
	String textureString = this->materialPath;
	std::cout << " Tex: " << textureString << "\n";
	std::wstring widestr = std::wstring(textureString.begin(), textureString.end());
	const wchar_t* texturePath = widestr.c_str();

	// Assigns the Texture to the renderer
	static_cast<TexturedCube*>(this->selectedObject)->getRenderer()->setTexture(TextureManager::getInstance()->createTextureFromFile(texturePath));

	this->materialDisplay = static_cast<Texture*>(TextureManager::getInstance()->createTextureFromFile(texturePath));
}

void InspectorScreen::updateTransformDisplays()
{
	Vector3D pos = this->selectedObject->getLocalPosition();
	this->positionDisplay[0] = pos.getX();
	this->positionDisplay[1] = pos.getY();
	this->positionDisplay[2] = pos.getZ();

	Vector3D rot = this->selectedObject->getLocalRotation();
	this->rotationDisplay[0] = rot.getX();
	this->rotationDisplay[1] = rot.getY();
	this->rotationDisplay[2] = rot.getZ();

	Vector3D scale = this->selectedObject->getLocalScale();
	this->scaleDisplay[0] = scale.getX();
	this->scaleDisplay[1] = scale.getY();
	this->scaleDisplay[2] = scale.getZ();
}

void InspectorScreen::deleteSelected()
{
	if (this->selectedObject == NULL)
		return;

	GameObjectManager::getInstance()->deleteObject(this->selectedObject);
}

void InspectorScreen::onTransformUpdate()
{
	if (this->selectedObject != NULL) {
		this->selectedObject->setPosition(Vector3D(this->positionDisplay[0], this->positionDisplay[1], this->positionDisplay[2]));
		this->selectedObject->setRotation(Vector3D(this->rotationDisplay[0], this->rotationDisplay[1], this->rotationDisplay[2]));
		this->selectedObject->setScale(Vector3D(this->scaleDisplay[0], this->scaleDisplay[1], this->scaleDisplay[2]));
	}
}
