
#include "SimpleWindow.h"



SimpleWindow::SimpleWindow(int width, int height, _StringContainer* data, _SW_Vector_Policy policy)
    : BaseWindow(width, height)
{
    __data   = data;
    __policy = policy;
    this->init();
}


SimpleWindow::SimpleWindow(WinGeometry geometry, _StringContainer* data, _SW_Vector_Policy policy)
    : BaseWindow(geometry)
{
    __data   = data;
    __policy = policy;
    this->init();
}


SimpleWindow::~SimpleWindow()
{
    if (__data)
        delete __data;

    wclear(__window);

}


void SimpleWindow::update() {wrefresh(__window);}


void SimpleWindow::init()
{
    __window = newwin(height, width, __win_dY, __win_dX);

    int row_line = 0;
    std::string tmp_string;
    for (auto item : *__data)
    {
        if (__policy == _SW_Vector_Policy::HORIZONTAL)
        {
            tmp_string = item + "  |  ";

            wprintw(__window, tmp_string.c_str());

        }
        else {
            tmp_string = item;

            mvwprintw(__window, row_line, 0, "----------");
            row_line++;
            mvwprintw(__window, row_line, 0, tmp_string.c_str());
            row_line++;

        }

    }

    this->update();

}


void SimpleWindow::updateStorage(_StringContainer* data)
{
    __data = data;
}
