#pragma once
#include <memory>
#include <stack>

#include "State.h"

/*! \typedef StateRef
	StateRef is used to create the unique pinters to the creates states
*/
using StateRef = std::unique_ptr<State> ;

/*!
	The StateMachine is the heart of the game engine and provides the necessary operation
	to make the game run and to switch the states and keep track of them
*/
class StateMachine
{
public:
	//! The constructor for the StateMachine
	StateMachine() {}
	//! The destructor for the StateMachine
	~StateMachine() {}

	//! AddState adds a new state. It can replace the current state or add it on top
	void AddState(StateRef newState, bool isReplacing = true);
	//! RemoveState removes the current state 
	void RemoveState();

	//! Provides the necessary operations to add or remove the states
 	void ProcessStateChanges();

	//! Returns a ponter to the current active state
	StateRef &GetActiveState();

private:
	std::stack<StateRef> _States;
	StateRef _newState;
	bool _isRemoving;
	bool _isAdding;
	bool _isReplacing;
};

