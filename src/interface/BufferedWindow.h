
#ifndef _BUFFERED_WINDOW_H_
#define _BUFFERED_WINDOW_H_

#include <vector>
#include <string>

#include "BaseWindow.h"



class BufferedWindow: public BaseWindow
{
private:
    char* filename = nullptr;

    std::vector<std::vector<__BufferItem*>*> buffer;
    std::vector<int> bufferLineSize;
    WINDOW* window;

    int __buffer_x;
    int __buffer_y;

    int currentViewX = 0;
    int currentViewY = 0;

    int currentX = 0;
    int currentY = 0;

    std::string __current_word;

public:
    BufferedWindow() = delete;
    BufferedWindow(WinSize size, char* filename = nullptr);
    BufferedWindow(WinGeometry geometry, char* filename = nullptr);
    BufferedWindow(int width, int height, char* filename = nullptr);
    ~BufferedWindow();

    WINDOW* getWindow();

    void init();
    void update();

    void doScroll(int);
    void moveHorizontal(int);
    void mouseMovement(MEVENT*);

    void insertLine();
    void deleteBefore();
    void deleteCurrentChar();
    void modifyBuffer(wint_t*);

    void copySingleWord();
    void copyCurrentLine();
    void pasteToBufferedWindow();

    void undo();
    void redo();

    std::string getCurrentWord();

    void doAutocomplete();

private:
    void __find_current_word();

    void __modify_buffer_coordinates();

    void __from_buffer_to_window();
    void __from_file_to_buffer();

public:
    bool __from_buffer_to_file();

};


#endif
