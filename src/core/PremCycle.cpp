#include "PremCycle.h"



KeyType keyRouter(int i_key)
{
    if (i_key == KEY_UP || i_key == KEY_DOWN || i_key == KEY_LEFT || i_key == KEY_RIGHT)
        return KeyType::CURSOR_MOVE;

    return KeyType::TEXT_ENTER;
}
