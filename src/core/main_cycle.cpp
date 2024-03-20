
#include <ncurses.h>

#include "main_cycle.h"
#include "../interface/WindowContainer.h"
#include "../core/PremStructs/Trie.h"
#include "../core/help_functions.h"
#include "../core/state_machine.h"
#include "../core/dict_reader.h"


#define PREM_KEY_ENTER 13
#define PREM_KEY_CTRL(x) ((x) & 0x1f)
#define PREM_KEY_ESC 27



void premGeneralLifeCycle(ConfigReader* __config, char* __file_name)
{
    StateMachine stateMachine;

    DictReader dictReader(__config->getDictPath(), "vsftpd"); // TODO: 
    dictReader.read_dict();

    initscr();
    raw();

    noecho();
    nonl();
    refresh();


    BufferedWindow win(
        {
            COLS * 0.7 - 1,
            LINES,
            2,
            1
        },
        __file_name
    );



    CommandTrie commandStorage;
    for (auto item : *dictReader.get_dict_data())
    {
        commandStorage.insert(item);
    }

    SimpleWindow keyBarWindow(
        {
            COLS * 0.3 - 3,
            LINES,
            COLS * 0.7 + 3,
            0
        },
        nullptr,
        _SW_Vector_Policy::VERTICAL
    );




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
                keyBarWindow.updateStorage(
                    &commandStorage.find(win.getCurrentWord())
                );
                break;

            case KEY_DC:
                win.deleteCurrentChar();
                keyBarWindow.updateStorage(
                    &commandStorage.find(win.getCurrentWord())
                );
                break;

            case PREM_KEY_CTRL('q'):
                run = false;
                break;

            case PREM_KEY_CTRL('s'):
                win.__from_buffer_to_file();
                break;

            case PREM_KEY_CTRL('c'):
                win.copySingleWord();
                break;

            case PREM_KEY_CTRL('l'):
                win.copyCurrentLine();
                break;

            case PREM_KEY_CTRL('v'):
                win.pasteToBufferedWindow();
                break;

            case KEY_MOUSE:
            {
                /*MEVENT mouse_event;

                if (getmouse(&mouse_event) == OK)
                {
                    win.mouseMovement(&mouse_event);
                }*/

                break;
            }

            case PREM_KEY_ESC:
                stateMachine.set_default_state();
                break;

            default:
                /*if (static_cast<char>(*input) == ' ')
                {
                    stateMachine.set_default_state();
                } else {
                    stateMachine.set_current_state(PremStates::SHOW_HINTS);
                }*/

                win.modifyBuffer(input);
                keyBarWindow.updateStorage(&commandStorage.find(win.getCurrentWord()));
                break;

        }

    }

}
