#include "AppWindow.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

#include "Cube.h"
#include "Vector3D.h"
#include "EngineTime.h"
#include "GameObjectManager.h"
#include "GraphicsEngine.h"
#include "InputSystem.h"
#include "MathUtils.h"
#include "Matrix4x4.h"
#include "SceneCameraHandler.h"


#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "UIManager.h"

#include <reactphysics3d/reactphysics3d.h>

#include "PhysicsSystem.h"
#include "ShaderLibrary.h"
#include "TextureManager.h"

using namespace reactphysics3d;

void AppWindow::onCreate()
{
	initializeEngine();
	initializeUI();
}
void AppWindow::onUpdate()
{
	ticks += EngineTime::getDeltaTime() * 1.0f;

	InputSystem::getInstance()->update();

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(m_swap_chain, 0.2f, 0.2f, 0.2f, 1);

	RECT rc = getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(width, height);

	// Update rest of the systems
	GameObjectManager::getInstance()->updateAll();
	BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();
	GameObjectManager::getInstance()->renderAll(width, height);
	SceneCameraHandler::getInstance()->update();
	UIManager::getInstance()->drawAllUI();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vertex_buffer->release();
	m_index_buffer->release();
	m_constant_buffer->release();

	m_vertex_shader->release();
	m_pixel_shader->release();

	InputSystem::destroy();
	ShaderLibrary::destroy();
	TextureManager::destroy();
	BaseComponentSystem::destroy();
	GameObjectManager::destroy();
	GraphicsEngine::get()->release();
	UIManager::destroy();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void AppWindow::initializeEngine()
{
	GraphicsEngine::get()->init();
	EngineTime::initialize();
	TextureManager::initialize();
	ShaderLibrary::initialize();
	InputSystem::initialize();

	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = getClientWindowRect();

	std::cout << "hwnd: " << this->m_hwnd;
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	GameObjectManager::initialize();
	BaseComponentSystem::initialize();

	SceneCameraHandler::initialize();
}

void AppWindow::initializeUI()
{
	UIManager::initialize(this->m_hwnd);
}

AppWindow::AppWindow()
= default;

AppWindow::~AppWindow()
= default;
