#include "ActionHistory.h"
#include "EngineBackend.h"
#include "ActionMemento.h"
#include "EditorAction.h"
#include "ActionHistory.h"

ActionHistory* ActionHistory::sharedInstance = nullptr;
ActionHistory* ActionHistory::getInstance()
{
    return sharedInstance;
}

void ActionHistory::initialize()
{
    sharedInstance = new ActionHistory();
}

void ActionHistory::destroy()
{
    delete sharedInstance;
}

void ActionHistory::startRecordAction(AGameObject* gameObject)
{
	if (EngineBackend::getInstance()->getMode() == EngineBackend::EditorMode::EDITOR) {
		// Change into Memento
		ActionMemento* editorAction = new ActionMemento(gameObject->getEditState(), NULL);
		this->actionsPerformed.push(editorAction);

		//std::cout << "Stored action " << gameObject->getName() << "\n";
	}
}

void ActionHistory::endRecordAction(AGameObject* gameObject)
{
	if (EngineBackend::getInstance()->getMode() == EngineBackend::EditorMode::EDITOR) {
		// Change into Memento
		ActionMemento* editorAction = new ActionMemento(this->actionsPerformed.top()->getOldAction(), gameObject->getEditState());
		actionsPerformed.pop();
		this->actionsPerformed.push(editorAction);

		//std::cout << "Stored action " << gameObject->getName() << "\n";
	}
}

bool ActionHistory::hasRemainingUndoActions()
{
	return !this->actionsPerformed.empty();
}

bool ActionHistory::hasRemainingRedoActions()
{
	return !this->actionsUndid.empty();
}

EditorAction* ActionHistory::undoAction()
{
	//do not undo actions during play mode.
	if (EngineBackend::getInstance()->getMode() != EngineBackend::EditorMode::EDITOR) {
		//std::cout << "Cannot perform any undo during play. \n";
		return NULL;
	}

	if (this->hasRemainingUndoActions()) {
		// change into Memento
		ActionMemento* action = this->actionsPerformed.top();
		this->actionsPerformed.pop();
		this->actionsUndid.push(action);
		return action->getOldAction();
	}
	else {
		//std::cout << "No more actions remaining. \n";
		return NULL;
	}
}

EditorAction* ActionHistory::redoAction()
{
	//do not undo actions during play mode.
	if (EngineBackend::getInstance()->getMode() != EngineBackend::EditorMode::EDITOR) {
		//std::cout << "Cannot perform any redo during play. \n";
		return NULL;
	}

	if (this->hasRemainingRedoActions()) {
		// Change into Memento
		ActionMemento* action = actionsUndid.top();
		this->actionsUndid.pop();
		this->actionsPerformed.push(action);
		return action->getNewAction();
	}
	else {
		//std::cout << "No more actions remaining. \n";
		return NULL;
	}
}

void ActionHistory::clear()
{
	while (this->hasRemainingUndoActions()) {
		ActionMemento* action = this->actionsPerformed.top();
		delete action;
		this->actionsPerformed.pop();
	}

	while (this->hasRemainingRedoActions()) {
		ActionMemento* action = this->actionsUndid.top();
		delete action;
		this->actionsUndid.pop();
	}
}

ActionHistory::ActionHistory()
{
}

ActionHistory::~ActionHistory()
{
}
