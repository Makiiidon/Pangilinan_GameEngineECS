#include "ProfilerScreen.h"
#include "imgui.h"

ProfilerScreen::ProfilerScreen() :AUIScreen("ProfilerScreen")
{

}

ProfilerScreen::~ProfilerScreen()
{
	AUIScreen::~AUIScreen();
}

void ProfilerScreen::drawUI()
{
	ImGui::Begin("Engine Profiler");           
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}
