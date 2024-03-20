
#include "state_machine.h"



void StateMachine::set_default_state()
{
    __previous_state = PremStates::EDIT_TEXT;
    __current_state  = PremStates::EDIT_TEXT;

}



void StateMachine::set_current_state(PremStates state)
{
    if (state == __current_state)
        return;

    __previous_state = __current_state;
    __current_state  = state;

}


PremStates StateMachine::get_current_state() {return __current_state;}
