
#include <ncurses.h>

#include "main_cycle.h"
#include "../interface/WindowContainer.h"
#include "../core/PremStructs/Trie.h"
#include "../core/help_functions.h"

#define PREM_KEY_ENTER 13
#define PREM_KEY_CTRL(x) ((x) & 0x1f)



void premGeneralLifeCycle(ConfigReader* __config, char* __file_name)
{
    initscr();

    /*BufferedWindow* editorWorkPlace = nullptr;
    SimpleWindow* keyBarWindow = new SimpleWindow(
        100,
        30,
        new _StringContainer {
            "^q Quit",
            "^c Copy",
            "^v Paste"
        },
        _SW_Vector_Policy::HORIZONTAL
    );
    keyBarWindow->init();

    _Layout l1(0, _LayoutPolicy::HORIZONTAL, 100, 20);
    l1.addWindow(keyBarWindow);*/


    /*WindowContainer mainWindow;

    mainWindow.addLayout(0, 1, 0.8f);
    mainWindow.addLayout(1, 1, 0.2f);

    mainWindow.addWindowToLayoutById(
        0, editorWorkPlace, _WinTypes::BUFFERED, __file_name
    );*/
    /*mainWindow.addWindowToLayoutById(
        1, keyBarWindow
    );*/



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
    commandStorage.insert("Python");
    commandStorage.insert("C++");
    commandStorage.insert("Java");
    commandStorage.insert("Java Script");
    commandStorage.insert("C#");
    commandStorage.insert("C");
    commandStorage.insert("Rust");
    commandStorage.insert("Ruby");
    commandStorage.insert("Perl");


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
                    commandStorage.find(win.getCurrentWord())
                );
                break;

            case KEY_DC:
                win.deleteCurrentChar();
                keyBarWindow.updateStorage(
                    commandStorage.find(win.getCurrentWord())
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
                MEVENT mouse_event;

                if (getmouse(&mouse_event) == OK)
                {
                    win.mouseMovement(&mouse_event);
                }

                break;
            }

            default:
                win.modifyBuffer(input);
                keyBarWindow.updateStorage(
                    commandStorage.find(win.getCurrentWord())
                );
                break;

        }

    }

}
