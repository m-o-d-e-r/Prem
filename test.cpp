
#include <string>
#include <iostream>

#include <ncurses.h>

#include "src/interface/BaseWindow.h"
#include "src/interface/BufferedWindow.h"


#define PREM_KEY_ENTER 13
#define PREM_KEY_CTRL(x) ((x) & 0x1f)

#include "src/core/PremStructs/BufferItem.h"

#include "src/core/args_preprocessor.h"

//#include "src/core/config_reader.h"



int main(int argc, char** argv)
{
//    ConfigReader config;

    setlocale(LC_ALL, "");


    ArgsPreprocessor __args_preprocessor(argc, argv);
    __args_preprocessor.parse();


    /*initscr();
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

            case PREM_KEY_CTRL('v'):
                win.pasteToBuffer();
                break;

            default:
                win.modifyBuffer(input);
                break;

        }
    }*/


    return 0;
}

/*
g++ -o test test.cpp src/core/PremStructs/BufferItem.cpp src/interface/BaseWindow.cpp src/interface/BufferedWindow.cpp  -lncursesw
*/