#include "ActionMemento.h"

ActionMemento::ActionMemento(EditorAction* oldAction, EditorAction* newAction)
{
    this->oldAction = oldAction;
    this->newAction = newAction;
}

ActionMemento::~ActionMemento()
{
}

EditorAction* ActionMemento::getOldAction()
{
    return oldAction;
}

EditorAction* ActionMemento::getNewAction()
{
    return newAction;
}

String ActionMemento::getOwnerName()
{
    return String();
}
