
#ifndef _BASE_WINDOW_H_
#define _BASE_WINDOW_H_

#include <tuple>

#include <ncurses.h>

#include "../core/PremStructs/BufferItem.h"


typedef std::tuple<int, int> WinSize;
typedef std::tuple<int, int, int, int> WinGeometry;


class BaseWindow
{
protected:
    int width;
    int height;
    int __win_dX = 0;
    int __win_dY = 0;

public:
    BaseWindow() = delete;
    BaseWindow(WinSize size);
    BaseWindow(int width, int height);
    BaseWindow(WinGeometry geometry);
    virtual ~BaseWindow();

    virtual void init()   = 0;
    virtual void update() = 0;

    WinSize getSize();

};


#endif
