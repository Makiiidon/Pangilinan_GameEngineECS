#pragma once
#include "AUIScreen.h"
class MenuScreen : public AUIScreen
{
private:
	MenuScreen();
	~MenuScreen();

	virtual void drawUI() override;
	void OnCreateCubeClicked();
	void OnCreateSphereClicked();
	void OnCreatePlaneClicked();
	void OnCreatePhysicsCubeClicked();
	void OnCreatePhysicsPlaneClicked();

	friend class UIManager;

	bool isOpen = false;
};

