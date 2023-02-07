
#include "WindowContainer.h"



_Layout::_Layout(short id, _LayoutPolicy policy, int width, int height)
{
    __id     = id;
    __policy = policy;
    __width  = width;
    __height = height;

}

short _Layout::getId() {return this->__id;}


__L_WindowObjects& _Layout::getWinObjects() {return this->__win_objects;}


_LayoutPolicy _Layout::getLayoutPolicy() {return this->__policy;}


void _Layout::addWindow(BufferedWindow* window)
{
    __win_objects.push_back(window);
}


void _Layout::addWindow(SimpleWindow* window)
{
    __win_objects.push_back(window);
}







WindowContainer::WindowContainer()
    : BaseWindow(COLS, LINES) // TODO: set global window width & height
{
    __width  = COLS;
    __height = LINES;

}


WindowContainer::~WindowContainer() {}


void WindowContainer::init() {}


void WindowContainer::update() {}


void WindowContainer::addLayout(short id, float width_cof, float height_cof)
{
    /*this->__layouts.push_back(
        std::make_shared<_Layout>(id, __width * width_cof, height * height_cof)
    );*/

}


_Layout* WindowContainer::getLayoutById(short id)
{
    for (auto layout : this->__layouts)
    {
        if (layout.get()->getId() == id)
            return layout.get();
    }
    // TODO: raise error

}
