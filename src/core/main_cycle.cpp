
#include "main_cycle.h"
#include "../interface/BufferedWindow.h"

#define PREM_KEY_ENTER 13
#define PREM_KEY_CTRL(x) ((x) & 0x1f)



void premGeneralLifeCycle(ConfigReader* __config, char* __file_name)
{
    initscr();
    raw();

    noecho();
    nonl();
    refresh();


    BufferedWindow win(20, 20, __file_name);

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
    }

}
