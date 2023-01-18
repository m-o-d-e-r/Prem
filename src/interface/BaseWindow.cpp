
#include "BaseWindow.h"



BaseWindow::BaseWindow(int width, int height)
{
    this->width  = width;
    this->height = height;
}


BaseWindow::BaseWindow(WinSize size)
{
    this->width  = std::get<0>(size);
    this->height = std::get<1>(size);
}


BaseWindow::~BaseWindow() {}


WinSize BaseWindow::getSize() {return {this->width, this->height};}
