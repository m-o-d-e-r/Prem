#ifndef PREM_CYCLE_H_
#define PREM_CYCLE_H_

#include <ncurses.h>


enum class KeyType
{
    CURSOR_MOVE,
    TEXT_ENTER
};


KeyType keyRouter(int);


#endif
