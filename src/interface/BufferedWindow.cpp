
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cstring>
#include <locale.h>
#include <codecvt>

#include <gtk/gtk.h>

#include "../core/help_functions.h"
#include "BufferedWindow.h"

#define PREM_SPECIAL_SYMBOL L'@'



BufferedWindow::BufferedWindow(WinSize size, char* filename): BaseWindow(size)
{
    this->filename = filename;
    init();
}


BufferedWindow::BufferedWindow(int width, int height, char* filename): BaseWindow(width, height)
{
    this->filename = filename;
    init();
}


BufferedWindow::BufferedWindow(WinGeometry geometry, char* filename)
    : BaseWindow(geometry)
{
    this->filename = filename;
    init();
}


BufferedWindow::~BufferedWindow()
{
    // call window destructor

    wclear(this->window);
    delwin(this->window);


    // clear the buffer
    for (int i = 0; i < this->buffer.size(); i++)
    {
        for (int n = 0; n < this->buffer[i]->size(); n++)
        {
            delete (*this->buffer[i])[n];
        }

        delete this->buffer[i];
    }

}


WINDOW* BufferedWindow::getWindow() {return this->window;}


void BufferedWindow::init()
{
    // initialize ncurses window
    this->window = newwin(this->height, this->width, __win_dY, __win_dX);

    keypad(this->window, TRUE);

    /*this->buffer.resize(this->height);
    for (int i = 0; i < this->height; i++)
    {
        this->buffer[i] = new std::vector<__BufferItem*>(this->width);
    }

    for (int i = 0; i < this->height; i++)
    {
        for (int n = 0; n < this->width; n++)
        {
            (*this->buffer[i])[n] = new __BufferItem(PREM_SPECIAL_SYMBOL);
        }
    }*/

    // read data from specified file
    if (this->filename)
    {
        if (!_is_file_exist(this->filename))
            _create_file(this->filename);

        this->__from_file_to_buffer();

    } else {
        
//        this->__from_buffer_to_window();
    }

}


void BufferedWindow::update() {wrefresh(this->window);}


void BufferedWindow::doScroll(int dY)
{
    // change current Y-value and update visible window area

    int rows_count;
    if (this->buffer.size() >= this->height)
        rows_count = this->height;
    else
        rows_count = this->buffer.size();


    if (
        (this->currentY + dY >= 0) &&
        (this->currentY + dY < rows_count)
    )
    {
        if (
            (this->currentY + dY == 0) ||
            (this->currentY + dY == rows_count - 1)
        )
        {
            if (
                (this->currentViewY + dY >= 0) &&
                (this->currentViewY + dY + rows_count <= this->buffer.size())
            )
            {
                this->currentViewY += dY;
            }

            if (
                (this->currentViewY != 0) &&
                (this->currentViewY + rows_count != this->buffer.size())
            )
                this->currentY += -dY;
        }


        if (this->buffer[__buffer_y + dY]->size() < this->width)
        {
            this->currentViewX = 0;

            if (this->currentX > this->buffer[__buffer_y + dY]->size())
                this->currentX = this->buffer[__buffer_y + dY]->size();

        }
        else if (this->buffer[__buffer_y + dY]->size() >= this->width /*&& this->currentViewX != 0*/)
        {
//            __modify_buffer_coordinates();

            if (this->buffer[__buffer_y + dY]->size() < this->buffer[__buffer_y]->size())
            {
                while (this->currentViewX + this->currentX > this->buffer[__buffer_y + dY]->size())
                {
                    // TODO:
                    // FIX:

                    this->currentViewX--;
                    /*if (this->currentX - 1 > 0)
                        this->currentX--;
                    else {
                        this->currentX--;
                        this->currentViewX++;
                    }*/

                }

            }

        }

        this->currentY += dY;

        __from_buffer_to_window();

    }

}


void BufferedWindow::moveHorizontal(int dX)
{

    int columns_count;
    bool is_extended_row = false;
    if (this->buffer[__buffer_y]->size() >= this->width)
    {
        is_extended_row = true;
        columns_count = this->width;
    } else {
        columns_count = this->buffer[__buffer_y]->size();
    }

    this->currentX += dX;

    if (this->currentX < 0)
    {
        if (__buffer_y > 0)
        {
            if (this->buffer[__buffer_y - 1]->size() > this->width)
            {
                this->currentViewX = this->buffer[__buffer_y - 1]->size() - this->width + 5;
                this->currentX = this->width - 5;
            } else {
                this->currentViewX = 0;
                this->currentX = this->buffer[__buffer_y - 1]->size();
            }

        } else {
            this->currentX = 0;
        }

        this->doScroll(-1);

    } else if (this->currentX + this->currentViewX > this->buffer[__buffer_y]->size())
    {
        this->doScroll(1);
        this->currentX = 0;

        this->currentViewX = 0;
    } else {

        if (this->currentX > this->width - 5 && dX == 1)
        {
            this->currentViewX++;
            this->currentX--;

        } else if (this->currentX <= 5 && this->currentViewX > 0)
        {
            this->currentViewX--;
            this->currentX++;
        }

    }



    __from_buffer_to_window();

}


void BufferedWindow::insertLine()
{
    int newLineIndex = this->currentViewY + this->currentY + 1;

    std::vector<std::vector<__BufferItem*>*>::iterator newLineIter = this->buffer.begin();
    newLineIter += newLineIndex;


    this->buffer.insert(
        newLineIter,
        new std::vector<__BufferItem*>(this->buffer[newLineIndex - 1]->size() - this->currentX)
    );


    for (int i = 0; i < this->buffer[newLineIndex]->size(); i++)
    {
        if ((*this->buffer[newLineIndex])[i])
            delete (*this->buffer[newLineIndex])[i];

        (*this->buffer[newLineIndex])[i] = new __BufferItem(
            (*this->buffer[newLineIndex - 1])[i + this->currentX]->getItemData()//->chars[0]
        );
    }


    for (int i = this->currentX; i < this->buffer[newLineIndex - 1]->size(); i++)
    {
        delete (*this->buffer[newLineIndex - 1])[i];
    }
    this->buffer[newLineIndex - 1]->resize(this->currentX);


    this->currentX = 0;
    if (this->currentY + 1 == this->height - 1)
    {
        this->doScroll(1);        
    } else if (this->currentY + 1 == this->height)
    {
        this->currentY--;
        this->doScroll(1);
    } else {
        this->currentY++;        
    }

    this->__from_buffer_to_window();
}


void BufferedWindow::deleteBefore()
{

    if (__buffer_y== 0 && this->currentX == 0)
        return;


    this->currentX--;

    if (this->currentViewX > 0)
    {
        if (this->currentX <= 1)
        {
            this->currentViewX--;
            this->currentX++;
        }
    }


    __modify_buffer_coordinates();
    if (this->currentX >= 0)
    {
        std::vector<__BufferItem*>::iterator rowIter = this->buffer[__buffer_y]->begin();

        delete (*this->buffer[__buffer_y])[__buffer_x];
        (*this->buffer[__buffer_y]).erase(rowIter + __buffer_x);

    } else {

        int tmp_size = this->buffer[__buffer_y - 1]->size();

        for (int i = 0; i < this->buffer[__buffer_y]->size(); i++)
        {
            this->buffer[__buffer_y - 1]->push_back(
                new __BufferItem(
                    (*this->buffer[__buffer_y])[i]->getItemData()//->chars[0]
                )
            );

            delete (*this->buffer[__buffer_y])[i];
        }

        std::vector<std::vector<__BufferItem*>*>::iterator currLineIter = this->buffer.begin();

        delete this->buffer[__buffer_y];
        this->buffer.erase(currLineIter + __buffer_y);

        if (this->currentViewY != 0)
            this->currentViewY--;
        else
            this->currentY--;



        if (tmp_size < this->width)
        {
            this->currentX = tmp_size;
        }
        else {
            this->currentViewX = this->buffer[__buffer_y - 1]->size() - this->width + 3;
            this->currentX = this->width - 3;
        }

    }

    __find_current_word();
    __from_buffer_to_window();
}


void BufferedWindow::deleteCurrentChar()
{

    if (__buffer_x != this->buffer[__buffer_y]->size())
    {
        std::vector<__BufferItem*>::iterator rowIter = this->buffer[__buffer_y]->begin();

        delete (*this->buffer[__buffer_y])[__buffer_x];
        (*this->buffer[__buffer_y]).erase(rowIter + __buffer_x);

    } else {
        if (__buffer_y + 1 == this->buffer.size())
            return;

        for (int i = 0; i < this->buffer[__buffer_y + 1]->size(); i++)
        {
            this->buffer[__buffer_y]->push_back(
                new __BufferItem(
                    (*this->buffer[__buffer_y + 1])[i]->getItemData()//->chars[0]
                )
            );
            delete (*this->buffer[__buffer_y + 1])[i];
        }


        std::vector<std::vector<__BufferItem*>*>::iterator currLineIter = this->buffer.begin();
        currLineIter += __buffer_y + 1;

        delete this->buffer[__buffer_y + 1];
        this->buffer.erase(currLineIter);

        if (this->currentViewY != 0)
        {
            this->currentViewY--;

            if (this->currentY + 1 < this->height - 1)
                this->currentY++;
        }

    }

    __find_current_word();
    __from_buffer_to_window();
}


void BufferedWindow::modifyBuffer(wint_t* character)
{
    // call when user modifing the text

    if ((char)(*character) != ' ')
        __current_word += static_cast<char>(*character);
    else
        __current_word = "";


    std::vector<__BufferItem*>::iterator bufferLineIter = this->buffer[__buffer_y]->begin();
    this->buffer[__buffer_y]->insert(
        bufferLineIter + __buffer_x,
        new __BufferItem(*character)
    );

    moveHorizontal(1);

    __from_buffer_to_window();
}


void BufferedWindow::copyFromBuffer()
{
    // fucking fuck...

    int left_border  = __buffer_x;
    int right_border = __buffer_x;
    short done;

    while (true)
    {
        done = 0;

        if (
            left_border > 0 &&
            (*this->buffer[__buffer_y])[left_border - 1]->getItemData() != ' '
        )
        {
            left_border--;
        } else {
            done++;
        }

        if (
            right_border < this->buffer[__buffer_y]->size() - 1 &&
            (*this->buffer[__buffer_y])[right_border + 1]->getItemData() != ' '
        )
        {
            right_border++;
        } else {
            done++;
        }

        if (done >= 2)
            break;

    }


    int buff_len = right_border - left_border + 1;
    __PremChar* __text_buffer = new __PremChar[buff_len];

    for (int i = left_border; i < buff_len; i++)
    {
        __text_buffer[i] = (*this->buffer[__buffer_y])[i]->getItemData();

    }


    gtk_init(0, 0);

    GtkClipboard* clip = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

    gtk_clipboard_set_text(clip, __text_buffer, buff_len);


    delete __text_buffer;

}


void BufferedWindow::pasteToBuffer()
{
    gtk_init(0, 0);

    GtkClipboard* clip = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
    std::string buffer_text = (std::string)gtk_clipboard_wait_for_text(clip);

 
    for (int i = 0; i < buffer_text.size(); i++)
    {
        this->buffer[__buffer_y]->insert(
            this->buffer[__buffer_y]->begin() + __buffer_x + i,
            new __BufferItem(buffer_text[i])
        );

    }

    if (this->buffer[__buffer_y]->size() < this->width)
    {
        this->currentX += buffer_text.size();
    } else {
        this->currentViewX = this->buffer[__buffer_y]->size() - this->width + 1;
        // FIX

    }

    __from_buffer_to_window();

}


void BufferedWindow::undo() {}


void BufferedWindow::redo() {}


std::string BufferedWindow::getCurrentWord() {return __current_word;}


void BufferedWindow::doAutocomplete()
{

}


void BufferedWindow::__find_current_word()
{
    int word_start_pos = __buffer_x;
    int word_end_pos   = __buffer_x;
    short done;


    if (this->buffer[__buffer_y]->size() == 1)
    {
        __current_word = (*this->buffer[__buffer_y])[word_start_pos - 1]->getItemData();

    }
    else if (this->buffer[__buffer_y]->size() == 0) {
        __current_word = "";
    }
    else {
        while (true)
        {
            done = 0;

            if (word_start_pos > 0)
            {
                if ((*this->buffer[__buffer_y])[word_start_pos - 1]->getItemData() != ' ')
                    word_start_pos--;
                else
                    done++;
            } else {
                done++;
            }




            if (word_end_pos < this->buffer[__buffer_y]->size() - 1)
            {
                if ((*this->buffer[__buffer_y])[word_end_pos + 1]->getItemData() != ' ')
                    word_end_pos++;
                else
                    done++;
            } else {
                done++;
            }

            if (done >= 2)
                break;

        }

    }

//    std::cout << word_start_pos << "|" << word_end_pos << "\n";


    /*__current_word = "";
    for (int i = word_end_pos; i < word_start_pos; i++)
    {
        __current_word += (*this->buffer[__buffer_y])[i]->getItemData();

    }*/

}


void BufferedWindow::__modify_buffer_coordinates()
{
    __buffer_x = this->currentViewX + this->currentX;
    __buffer_y = this->currentViewY + this->currentY;
}


void BufferedWindow::__from_buffer_to_window()
{
    // read data from the buffer and add character to new position after moving

    // clear the window
    for (int i = 0; i < this->buffer.size(); i++)
    {
        for (int n = 0; n < this->width; n++)
        {
            mvwaddch(this->window, i, n, ' ');
        }
    }


    int rows_count;
    if (this->buffer.size() >= this->height)
        rows_count = this->height;
    else
        rows_count = this->buffer.size();


    int columns_count;

//    wborder(this->window, '|', '|', '-', '-', '+', '+', '+', '+'); // TODO
    for (int i = 0; i < rows_count; i++)
    {
        if (this->buffer[this->currentViewY + i]->size() >= this->width)
        {
            columns_count = this->width;
        } else {
            columns_count = this->buffer[this->currentViewY + i]->size();
        }

        for (int n = 0; n < columns_count; n++)
        {
            if (this->currentViewX + n >= this->buffer[this->currentViewY + i]->size())
                break;


            #ifdef PREM_USE_UNICODE_BUFFER
                cchar_t cchar_data;

                cchar_data.attr = 0;
                cchar_data.chars[0] = (*this->buffer[this->currentViewY + i])[this->currentViewX + n]->getItemData();
                cchar_data.chars[1] = L'\0';

                __add_item_to_window(
                    this->window,
                    i, n,
                    &cchar_data
                );

            #else
                __add_item_to_window(
                    this->window,
                    i, n,
                    (*this->buffer[this->currentViewY + i])[this->currentViewX + n]->getItemData()
                );

            #endif


        }
    }
    wmove(this->window, this->currentY, this->currentX);

    __modify_buffer_coordinates();

    this->update();
}


void BufferedWindow::__from_file_to_buffer()
{
    // read data from the file

    std::wstring s;
    std::wfstream file(this->filename, std::ios_base::in);

    std::locale loc(std::locale(), new std::codecvt_utf8_utf16<wchar_t>);
    file.imbue(loc);

    if (file.is_open())
    {
        int lineNumber = 0;

        while (!file.eof())
        {
            std::getline(file, s);

            if (this->buffer.size() > lineNumber)
            {
                delete this->buffer[lineNumber];
                this->buffer[lineNumber] = new std::vector<__BufferItem*>(s.size());

            } else {
                this->buffer.push_back(new std::vector<__BufferItem*>(s.size()));
            }

            for (int n = 0; n < s.size(); n++)
            {
                (*this->buffer[lineNumber])[n] = new __BufferItem(s[n]);
            }

            lineNumber++;
        }
    }

    __from_buffer_to_window();
    this->update();
}


bool BufferedWindow::__from_buffer_to_file()
{
    // read data to specified file

    if (this->filename)
    {
        std::wstring line;
        std::wfstream file(this->filename, std::ios::out);

        std::locale loc(std::locale(), new std::codecvt_utf8_utf16<wchar_t>);
        file.imbue(loc);

        for (int i = 0; i < this->buffer.size(); i++)
        {
            for (int n = 0; n < this->buffer[i]->size(); n++)
            {
                line += (*this->buffer[i])[n]->getItemData();//->chars[0];
            }
            file << line << "\n";

            line.clear();
        }
    }

    return false;

}

