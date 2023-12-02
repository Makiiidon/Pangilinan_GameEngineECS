#include "UIManager.h"
#include "GraphicsEngine.h"
#include "ProfilerScreen.h"
#include "MenuScreen.h"
#include "InspectorScreen.h"
#include "HierarchyScreen.h"
#include "MaterialScreen.h"
#include "ScenePlayOptions.h"
#include "ActionScreen.h"


UIManager* UIManager::sharedInstance = NULL;

UIManager* UIManager::getInstance()
{
	return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
	sharedInstance = new UIManager(windowHandle);
}

void UIManager::destroy()
{
	delete sharedInstance;
}

void UIManager::setEnabled(String uiName, bool flag)
{
	if (this->uiTable[uiName] != nullptr)
	{
		this->uiTable[uiName]->SetEnabled(flag);
	}
}

AUIScreen* UIManager::findUIByName(String uiName)
{
	if (this->uiTable[uiName] != nullptr) 
	{
		return uiTable[uiName];
	}
	return nullptr;
}

void UIManager::drawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (int i = 0; i < this->uiList.size(); i++) {
		this->uiList[i]->drawUI();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::UIManager(HWND windowHandle)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	GraphicsEngine* graphEngine = GraphicsEngine::get();
	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(graphEngine->getDirect3DDevice(), graphEngine->getImmediateDeviceContext()->getDeviceContext());

	//populate UI table
	UINames uiNames;
	ProfilerScreen* profilerScreen = new ProfilerScreen();
	this->uiTable[uiNames.PROFILER_SCREEN] = profilerScreen;
	this->uiList.push_back(profilerScreen);

	MenuScreen* menuScreen = new MenuScreen();
	this->uiTable[uiNames.MENU_SCREEN] = menuScreen;
	this->uiList.push_back(menuScreen);

	InspectorScreen* inspectorScreen = new InspectorScreen();
	this->uiTable[uiNames.INSPECTOR_SCREEN] = inspectorScreen;
	this->uiList.push_back(inspectorScreen);

	HierarchyScreen* hierarchyScreen = new HierarchyScreen();
	this->uiTable[uiNames.HIERARCHY_SCREEN] = hierarchyScreen;
	this->uiList.push_back(hierarchyScreen);

	ScenePlayOptions* scenePlayOptions = new ScenePlayOptions();
	this->uiTable[uiNames.SCENE_PLAY_OPTIONS] = scenePlayOptions;
	this->uiList.push_back(scenePlayOptions);

	ActionScreen* actionScreen = new ActionScreen();
	this->uiTable[uiNames.ACTION_SCREEN] = actionScreen;
	this->uiList.push_back(actionScreen);

	//UIs that will show during runtime
	MaterialScreen* materialScreen = new MaterialScreen();
	this->uiTable[uiNames.MATERIAL_SCREEN] = materialScreen;
	this->uiList.push_back(materialScreen);
	materialScreen->SetEnabled(false);

}

UIManager::~UIManager()
{
}
