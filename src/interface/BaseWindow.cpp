
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


BaseWindow::BaseWindow(WinGeometry geometry)
{
    this->width    = std::get<0>(geometry);
    this->height   = std::get<1>(geometry);
    this->__win_dX = std::get<2>(geometry);
    this->__win_dY = std::get<3>(geometry);
}



BaseWindow::~BaseWindow() {}


WinSize BaseWindow::getSize() {return {this->width, this->height};}
