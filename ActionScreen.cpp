#include "ActionScreen.h"

ActionScreen::ActionScreen() : AUIScreen("ActionScreen")
{
}

ActionScreen::~ActionScreen()
{
}

void ActionScreen::drawUI()
{
	ImGui::Begin("Actions");

	if (ImGui::Button("Undo")) {

	}

	ImGui::SameLine();

	if (ImGui::Button("Redo")) {

	}

	ImGui::End();
}
