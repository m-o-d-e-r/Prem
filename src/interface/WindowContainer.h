#ifndef WINDOW_CONTAINER_H
#define WINDOW_CONTAINER_H

#include <memory>
#include <vector>

#include "BaseWindow.h"


class WindowContainer: public BaseWindow
{
private:
    std::vector<std::shared_ptr<BaseWindow>> __window_objects;
    int* __window_offsets;

public:
    WindowContainer();
    ~WindowContainer();

    void init();
    void update();

};


#endif
