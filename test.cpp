
#include <string>
#include <iostream>

#include <ncurses.h>

#include "src/interface/BaseWindow.h"
#include "src/interface/BufferedWindow.h"


#define PREM_KEY_ENTER 13
#define PREM_KEY_CTRL(x) ((x) & 0x1f)

#include "src/core/PremStructs/BufferItem.h"






int main()
{
    setlocale(LC_ALL, "");

    initscr();
    raw();
//    cbreak();
    noecho();
    nonl();

    refresh();

    BufferedWindow win(20, 20, const_cast<char*>("/mnt/d/pyrus/PreM/text"));

    wint_t* input = new wint_t;
    bool run = true;
    while (run)
    {
        wget_wch(win.getWindow(), input);
//        input = wgetch(win.getWindow());

//        std::cout << *input << ")\n";
        switch (*input)
        {
            case KEY_UP:
                win.doScroll(-1);
                break;

            case KEY_DOWN:
                win.doScroll(1);
                break;

            case KEY_LEFT:
                win.moveHorizontal(-1);
                break;

            case KEY_RIGHT:
                win.moveHorizontal(1);
                break;

            case PREM_KEY_ENTER:
                win.insertLine();
                break;

            case KEY_BACKSPACE:
                win.deleteBefore();
                break;

            case KEY_DC:
                win.deleteCurrentChar();
                break;

            case PREM_KEY_CTRL('q'):
                run=false;
                break;

            case PREM_KEY_CTRL('s'):
                win.__from_buffer_to_file();
                break;

            default:
                win.modifyBuffer(input);
                break;

        }
    }


//    BaseWindow* window = new BufferedWindow(20, 10);

   /* initscr();
    cbreak();
    noecho();
    nonl();
    refresh();

    int viewPort = 10;
    WINDOW* mainWin = newwin(viewPort, 4, 0, 0);
    keypad(mainWin, TRUE);

    int currentY = 0;


    int len_ = 20;
    char b[len_][4] = {
        {'1', '1', '2', '3'},
        {'2', 'b', 'c', 'd'},
        {'3', 'b', 'c', 'd'},
        {'4', 'b', 'c', '1'},
        {'5', 'b', 'c', 'd'},
        {'6', 'b', 'c', 'd'},
        {'7', 'b', 'c', 'd'},
        {'8', 'b', 'c', '1'},
        {'9', 'b', 'c', 'd'},
        {'a', 'b', 'c', 'd'},
        {'b', 'b', 'c', 'd'},
        {'c', 'b', 'c', '1'},
        {'d', 'b', 'c', 'd'},
        {'e', 'b', 'c', 'd'},
        {'f', 'b', 'c', 'd'},
        {'g', 'b', 'c', '1'}
    };


    from_buffer_to_window(b, mainWin, currentY);
    wrefresh(mainWin);


    int input;

    wmove(mainWin, currentY, 0);
    while (true)
    {
        input = wgetch(mainWin);

        switch (input)
        {
            case KEY_UP:
                currentY--;
                break;

            case KEY_DOWN:
                currentY++;
                break;
        }
    
        from_buffer_to_window(b, mainWin, currentY);
        wrefresh(mainWin);
    }



    getch();*/

    return 0;
}

