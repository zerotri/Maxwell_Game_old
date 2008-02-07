
//----------------------------------------------------------------------------
// File:         GameState.h
// Description:  Interface for the GameState abstract class.
//----------------------------------------------------------------------------
#ifndef _GAMESTATE_H
#define _GAMESTATE_H
#include "utils.h"
#include "ApplicationBase.h"
class GameState
{
    public:
        // initialize the state
        virtual void initialize(ApplicationBase* _app) = 0;
        // shutdown the state
        virtual void shutdown() = 0;

        // handle frame update
        virtual bool update(time_type delta) = 0;
        // handle frame rendering
        virtual void render() = 0;
    protected:
        ApplicationBase* app;
};

#endif
