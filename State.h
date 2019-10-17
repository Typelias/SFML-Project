#pragma once

/*!
	State is an abstract class that all the different game states inherits from
*/
class State
{
public:
	//! Constructor for the class. Takes game data as input.
	State() = default;
	//! Destructor
	virtual ~State() = default;

	/*! 
		Init runs at state creation to get everything ready.
		This function os pure virtual because every state has
		different thing to prepare
	*/
	virtual void Init() = 0;
	/*!
		Runs ever cykel to handle event input.
		This function is virtual because every state has different inputs
	*/
	virtual void HandleInput() = 0;
	/*!
		Update runs every cykel after the event input is handled and runs the main parts of the state.
		This fucntion is virtual becus every state has different ways of operating
	*/
	virtual void Update(float dt) = 0;
	/*!
		After we handled input and updates we need to display them and then we call update.
		This state is virutal because every state has different things to draw.
	*/
	virtual void Draw(float dt) = 0;

	//!Pause is used if we want to pause the state
	virtual void Pause() {}
	//!Resume is used to resume if we want to resume the state from pause
	virtual void Resume() {}

};

