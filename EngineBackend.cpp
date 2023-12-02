#include "EngineBackend.h"
#include "GameObjectManager.h"

EngineBackend* EngineBackend::sharedInstance = nullptr;
EngineBackend* EngineBackend::getInstance()
{
    return sharedInstance;
}

void EngineBackend::initialize()
{
    sharedInstance = new EngineBackend();

}

void EngineBackend::destroy()
{
    delete sharedInstance;
}

void EngineBackend::setMode(EditorMode mode)
{
	this->editorMode = mode;
	if (this->editorMode == EditorMode::PLAY) {
		//GameObjectManager::getInstance()->saveEditStates();
	}
	else if (this->editorMode == EditorMode::EDITOR) {
		//GameObjectManager::getInstance()->restoreEditStates();
	}
}

void EngineBackend::startFrameStep()
{
}

void EngineBackend::endFrameStep()
{
}

EngineBackend::EditorMode EngineBackend::getMode()
{
    return editorMode;
}

EngineBackend::EngineBackend()
{
}

EngineBackend::~EngineBackend()
{
}
