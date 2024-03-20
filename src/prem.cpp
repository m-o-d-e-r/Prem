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


/*    initscr();
    WINDOW* test = newpad(3, 20);
    scrollok(test, true);

    for (int i = 0; i < 5; i++)
    {
        wprintw(test, "Hello world\n");
    }



//    box(test, 0, 0);
    prefresh(test, 0, 0, 0, 0, 20, 20);
    wgetch(test);*/

}
