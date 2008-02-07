

//----------------------------------------------------------------------------
// File:         StateManager.h
// Description:  Interface for the StateManager class.
//----------------------------------------------------------------------------
#ifndef _STATEMANAGER_H
#define _STATEMANAGER_H

#include <vector>
#include "utils.h"
#include "ApplicationBase.h"
#define StateMan() StateManager::getInstance()
// forward declaration for GameState class
class GameState;

//----------------------------------------------------------------------------
// Class:          StateManager
// Description:  Manages game states for the engine.
//----------------------------------------------------------------------------
class StateManager
{
    public:
        // Constructor
        StateManager();
        // Destructor
        ~StateManager();

        // Push a new state onto the stack
        void pushState(GameState* state);

        // Pop the current state off the stack
        GameState* popState();

        // Remove all states from the stack
        void popAll();

        // Call the current state's update method
        bool update(time_type delta);

        // Call the current state's render method
        void render();

        // Return the singleton StateManager instance
        static StateManager* getInstance();

        // Register the ApplicationBase class
        void RegisterApplicationBase(ApplicationBase* _app);

    private:
        ApplicationBase* app;
        std::vector<GameState*> _states;
        static StateManager* _instance;
};
#endif
