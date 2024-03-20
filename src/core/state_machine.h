
#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_



enum class PremStates
{
    EDIT_TEXT,
    SHOW_HINTS

};



class StateMachine
{
private:
    PremStates __previous_state;
    PremStates __current_state;

public:
    void set_default_state();
    void set_current_state(PremStates);
    PremStates get_current_state();

};





#endif
