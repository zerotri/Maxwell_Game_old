//----------------------------------------------------------------------------
// File:         StateManager.cpp
// Description:  Implementation for the StateManager class.
//----------------------------------------------------------------------------
#include "StateManager.h"
#include "GameState.h"

//----------------------------------------------------------------------------
// Static Instance Variables
//----------------------------------------------------------------------------
StateManager* StateManager::_instance = 0;

//----------------------------------------------------------------------------
// Method:   Constructor
//----------------------------------------------------------------------------
StateManager::StateManager()
{
}

//----------------------------------------------------------------------------
// Method:   Destructor
//----------------------------------------------------------------------------
StateManager::~StateManager()
{
    // if there's anything left in the _states vector, then we have a
    // memory leak. it's up to the calling application to make sure
    // the states are cleaned up and deleted.
}

//----------------------------------------------------------------------------
// Method:   pushState
// Description:   Push a new state onto the state stack. Calls the state's
//       initialize method.
//----------------------------------------------------------------------------
void StateManager::pushState(GameState* state)
{
   state->initialize();
   _states.push_back(state);
}

//----------------------------------------------------------------------------
// Method:   popState
// Description:   Pops the current state off the state stack. Calls the state's
//       shutdown method.
// Returns:   The state that was popped. This gives the caller a chance to
//       delete the state if appropriate.
//----------------------------------------------------------------------------
GameState* StateManager::popState()
{
   GameState* state = 0;

   if (_states.size() > 0)
   {
      state = _states[_states.size()-1];
      _states.pop_back();
      state->shutdown();
   }

   return state;
}

//----------------------------------------------------------------------------
// Method:   popAll
// Description:   Pops all states from the state stack. Note that the states
//       are not deleted, so it is up to the caller to take care of
//       deleting the states. This obviously means that the states
//       must be kept in a list somewhere in the caller.
//       One possible solution is to put a "delete this;"
//       into the shutdown methods of your states.
//       That would ensure that they get deleted when
//       they get popped.
//----------------------------------------------------------------------------
void StateManager::popAll()
{
   while (popState())
      ;
}

//----------------------------------------------------------------------------
// Method:   update
// Parameters:   delta - number of seconds since last call
// Description:   Calls the current state's update method.
// Returns:   If there is a current state, then it returns the return value
//       from the current state's update method. Otherwise, it returns
//       false.
//----------------------------------------------------------------------------
bool StateManager::update(float delta)
{
   if (_states.size() > 0)
   {
      return _states[_states.size()-1]->update(delta);
   }
   else
   {
      return false;
   }
}

//----------------------------------------------------------------------------
// Method:   render
// Description:   Calls the current state's render method.
//----------------------------------------------------------------------------
void StateManager::render()
{
   if (_states.size() > 0)
   {
      _states[_states.size()-1]->render();
   }
}

//----------------------------------------------------------------------------
// Method:   getInstance
// Description:   Gets the singleton StateManager instance.
// Returns:   A pointer to the StateManager instance.
//----------------------------------------------------------------------------
StateManager* StateManager::getInstance()
{
   if (_instance == 0)
   {
      _instance = new StateManager();
   }

   return _instance;
}
