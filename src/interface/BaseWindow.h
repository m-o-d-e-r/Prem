
#ifndef _BASE_WINDOW_H_
#define _BASE_WINDOW_H_

#include <tuple>

#include <ncurses.h>

#include "../core/PremStructs/BufferItem.h"


typedef std::tuple<int, int> WinSize;


class BaseWindow
{
protected:
    int width;
    int height;

public:
    BaseWindow() = delete;
    BaseWindow(WinSize size);
    BaseWindow(int width, int height);
    virtual ~BaseWindow();

    virtual void init()   = 0;
    virtual void update() = 0;

    WinSize getSize();

};


#endif
