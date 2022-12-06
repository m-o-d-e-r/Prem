#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <sys/ioctl.h>

#include <ncurses.h>


#include "core/MainWindow.h"


int main()
{
    MainWindow mainWindow;
    mainWindow.initializeWindow();
    mainWindow.show();

/*
    initscr();
    WINDOW* test = newwin(20, 20, 0, 50);
    box(test, 0, 0);
    wrefresh(test);
    wgetch(test);*/

}
