#include "ScenePlayOptions.h"
#include "GameObjectManager.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "PhysicsComponent.h"

ScenePlayOptions::ScenePlayOptions() : AUIScreen("ScenePlayOptions")
{
}

ScenePlayOptions::~ScenePlayOptions()
{
}

void ScenePlayOptions::drawUI()
{
	ImGui::Begin("Scene Play Options");

	std::string buttonName = "Play";

	if (isPlay) {
		buttonName = "Stop";
	}

	if (ImGui::Button(buttonName.c_str())) {
		isPlay = !isPlay;

		// Pause Everything
		if (isPlay) 
		{
			//GameObjectManager::List gameObjects = GameObjectManager::getInstance()->getAllObjects();
			//PhysicsSystem::ComponentList physicsComponents = BaseComponentSystem::getInstance()->getPhysicsSystem()->getAllComponents();
			//for (int i = 0; i < physicsComponents.size(); i++)
			//{
			//	physicsComponents[i]->getRigidBody()->setIsSleeping(true);
			//}
		}
		else // Player Everything
		{
			/*PhysicsSystem::ComponentList physicsComponents = BaseComponentSystem::getInstance()->getPhysicsSystem()->getAllComponents();
			for (int i = 0; i < physicsComponents.size(); i++)
			{
				physicsComponents[i]->getRigidBody()->setIsSleeping(false);
			}*/
		}
	}

	if (isPlay) {
		ImGui::SameLine();
		if (ImGui::Button("Reset")) { // Remove and Reapply
			
		}
	}


	ImGui::End();
}
