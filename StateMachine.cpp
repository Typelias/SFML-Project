#include "StateMachine.h"


void StateMachine::AddState(StateRef newState, bool isReplacing)
{
	this->_isAdding = true;
	this->_isReplacing = isReplacing;

	this->_newState = std::move(newState);



}

void StateMachine::RemoveState()
{
	this->_isRemoving = true;
}

void StateMachine::ProcessStateChanges()
{
	if (_isRemoving && !_States.empty())
	{
		if (_States.empty())
		{
			_States.top()->Resume();
		}

		_isRemoving = false;
	}

	if (_isAdding)
	{
		if (!this->_States.empty())
		{
			if (this->_isReplacing)
			{
				this->_States.pop();
			}
			else
			{
				this->_States.top()->Pause();
			}
		}
		this->_States.push(std::move(_newState));
		this->_States.top()->Init();
		this->_isAdding = false;
	}


}

StateRef &StateMachine::GetActiveState()
{
	return this->_States.top();
}
