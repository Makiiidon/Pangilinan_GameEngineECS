#pragma once
#define NOMINMAX
#include <Windows.h>

class Window
{
public:
	Window();
	~Window();

	// Initialize the Window
	bool init();
	// When window is running:
	bool broadcast();
	// Release the Window
	bool release();

	bool isRunning();

	RECT getClientWindowRect();

	void setHWND(HWND hwnd);

	// Events
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy();

	static const int WINDOW_WIDTH = 1440;
	static const int WINDOW_HEIGHT = 900;

protected:
	HWND m_hwnd;
	bool m_is_running;
};

