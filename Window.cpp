#include "Window.h"
#include "Utilities.h"
#include <stdexcept>

#include "EngineTime.h"
#include "imgui.h"

const HMODULE moduleHandle = GetModuleHandle(nullptr);

//Window* window = nullptr;

Window::Window()
{
	m_is_running = false;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{

	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		return true;

	switch (msg)
	{
	case WM_CREATE:
	{
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->setHWND(hwnd);
		window->onCreate();
		break;
	}
	case WM_DESTROY:
	{
		Window* window = (Window*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

bool Window::init()
{
	const LPCWSTR class_name = L"Main_GameEngine";
	WNDCLASSEX wc = {};

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = class_name;
	wc.lpszMenuName = L"";
	wc.hInstance = moduleHandle;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc))
		// RegisterClassEx fails.
		throw std::runtime_error(Utilities::GetErrorStr());


	//if (!window)
	//	window = this;

	// Window Creation
	m_hwnd = ::CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW, class_name, L"DirectX Application",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		WINDOW_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, moduleHandle, this
	);

	if (!m_hwnd)
		// CreateWindowEx fails.
		throw std::runtime_error(Utilities::GetErrorStr());

	// show up the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);


	m_is_running = true;

	return true;
}

// Message Pump
bool Window::broadcast()
{
	EngineTime::LogFrameStart();
	this->onUpdate(); // ensure that a final frame update is made (to flush values) before releasing the resources

	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);
	EngineTime::LogFrameEnd();
	return true;
}


bool Window::release()
{
	// Destroy the window
	if (!::DestroyWindow(m_hwnd))
		// DestroyWindow fails.
		throw std::runtime_error(Utilities::GetErrorStr());

	return true;
}

bool Window::isRunning()
{
	return m_is_running;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	GetClientRect(m_hwnd, &rc);

	return rc;
}

void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

void Window::onDestroy()
{
	m_is_running = false;
}

Window::~Window()
{
}
