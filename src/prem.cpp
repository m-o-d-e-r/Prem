
#include <string>
#include <iostream>

#include <ncurses.h>

#include "interface/BaseWindow.h"
#include "interface/BufferedWindow.h"


#define PREM_KEY_ENTER 13
#define PREM_KEY_CTRL(x) ((x) & 0x1f)

#include "core/PremStructs/BufferItem.h"

#include "core/args_preprocessor.h"
#include "core/args_router.h"

#include "core/config_reader.h"

#include "core/help_functions.h"


#include <xcb/xcb.h>
#include "libs/clipboard/include/libclipboard.h"


int main(int argc, char** argv)
{
    setlocale(LC_ALL, "");


    /*clipboard_c* cb = clipboard_new(NULL);
    clipboard_set_text_ex(cb, "Hello 123", 5, LCB_CLIPBOARD);

    int l = 5;
    char* some_text_from_clipboard = clipboard_text_ex(cb, &l, LCB_CLIPBOARD);

    std::cout << some_text_from_clipboard << '\n';*/

//    clipboard_clear(cb, LCB_CLIPBOARD);
//    clipboard_free(cb);


    ConfigReader* config = new ConfigReader;

    ArgsPreprocessor __args_preprocessor;
    __args_preprocessor.parse(argc, argv);


    ArgsRouter __args_router(__args_preprocessor.getArgsInfo(), config);
    __args_router.run();


    delete config;

    return 0;
}
