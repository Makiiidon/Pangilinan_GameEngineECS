#pragma once
#include "AUIScreen.h"
#include <imgui.h>

class ActionScreen : public AUIScreen
{
private:
	ActionScreen();
	~ActionScreen();
	virtual void drawUI() override;

	friend class UIManager;
};

