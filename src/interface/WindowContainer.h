
#ifndef _WINDOW_CONTAINER_H_
#define _WINDOW_CONTAINER_H_

#include <memory>
#include <vector>

#include "BaseWindow.h"


enum class WinTypes {
    WORKSPACE,
    HINT_SIDEBAR,
    STATUSBAR
};




class WindowContainer: public BaseWindow
{
private:
    std::vector<BaseWindow*> __window_objects;

public:
    WindowContainer();
    ~WindowContainer();

    void init();
    void update();

    void addLayout(short, int, int);
    void addWindowToLayout();

};


#endif
