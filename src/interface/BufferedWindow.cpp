
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cstring>
#include <locale.h>
#include <codecvt>

#include "BufferedWindow.h"


#define PREM_SPECIAL_SYMBOL L'\n'



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


BufferedWindow::~BufferedWindow()
{
    // call window destructor

    delwin(this->window);


    // clear the buffer
    /*for (int i = 0; i < this->height; i++)
    {
        if (this->buffer[i])
            delete this->buffer[i];
    }*/

}


WINDOW* BufferedWindow::getWindow() {return this->window;}


void BufferedWindow::init()
{
    // initialize ncurses window
    this->window = newwin(this->height, this->width, 0, 0);

    keypad(this->window, TRUE);


    // initialize window buffer

    this->buffer.resize(this->height);
    for (int i = 0; i < this->height; i++)
    {
        this->buffer[i] = new std::vector<__BufferItem*>(this->width);
    }
//    this->bufferLineSize.resize(this->width);

    for (int i = 0; i < this->height; i++)
    {
//        this->bufferLineSize[i] = this->width;

        for (int n = 0; n < this->width; n++)
        {
            (*this->buffer[i])[n] = new __BufferItem(PREM_SPECIAL_SYMBOL);
        }
    }

    // read data from specified file
    if (this->filename)
    {
        this->__from_file_to_buffer();
    }

//    this->__from_buffer_to_window();
//    wmove(this->window, this->currentY, this->currentX);
//    this->update();
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


        int currentLine = this->currentY + this->currentViewY;


        if (this->buffer[currentLine + dY]->size() < this->width)
        {
            this->currentViewX = 0;

            while (this->currentX > this->buffer[currentLine + dY]->size())
            {
                this->currentX--;
            }

        }
        else if (this->buffer[currentLine + dY]->size() >= this->width && this->currentViewX != 0)
        {

            if (
//                (this->buffer[currentLine]->size() > this->buffer[currentLine + dY]->size()) &&
                (this->currentViewX + this->currentX > this->buffer[currentLine + dY]->size())
            )
            {
                this->currentX -= this->buffer[currentLine]->size() - this->buffer[currentLine + dY]->size();
            }

        }

        this->currentY += dY;

        __from_buffer_to_window();
    }

}


void BufferedWindow::moveHorizontal(int dX)
{

    int lineIndex = this->currentViewY + this->currentY;



    int columns_count;
    bool is_extended_row = false;
    if (this->buffer[lineIndex]->size() >= this->width)
    {
        is_extended_row = true;
        columns_count = this->width;
    } else {
        columns_count = this->buffer[lineIndex]->size();
    }



    this->currentX += dX;


    if (this->currentX < 0)
    {
        if (lineIndex > 0)
        {
            if (this->buffer[lineIndex - 1]->size() > this->width)
            {
                this->currentViewX = this->buffer[lineIndex - 1]->size() - this->width + 1;
                this->currentX = this->width - 1;
            } else {
                this->currentViewX = 0;
                this->currentX = this->buffer[lineIndex - 1]->size();
            }

        } else {
            this->currentX = 0;
        }

        this->doScroll(-1);

    } else if (this->currentX + this->currentViewX > this->buffer[lineIndex]->size())
    {
        this->doScroll(1);
        this->currentX = 0;

        this->currentViewX = 0;
    } else {

        if (this->currentX == this->width - 2 && dX == 1)
        {
            this->currentViewX++;
            this->currentX--;

        } else if (this->currentX == 0 && this->currentViewX > 0)
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
            (*this->buffer[newLineIndex - 1])[i + this->currentX]->getItemData()->chars[0]
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
    int lineIndex = this->currentViewY + this->currentY;

    if (lineIndex == 0 && this->currentX == 0)
        return;

    this->currentX--;
    if (this->currentX >= 0)
    {
        std::vector<__BufferItem*>::iterator rowIter = this->buffer[lineIndex]->begin();

        delete (*this->buffer[lineIndex])[this->currentX];
        (*this->buffer[lineIndex]).erase(rowIter + this->currentX);

    } else {

        int tmp_size = this->buffer[lineIndex - 1]->size();

        for (int i = 0; i < this->buffer[lineIndex]->size(); i++)
        {
            this->buffer[lineIndex - 1]->push_back(
                new __BufferItem(
                    (*this->buffer[lineIndex])[i]->getItemData()->chars[0]
                )
            );

            delete (*this->buffer[lineIndex])[i];
        }

        std::vector<std::vector<__BufferItem*>*>::iterator currLineIter = this->buffer.begin();

        delete this->buffer[lineIndex];
        this->buffer.erase(currLineIter + lineIndex);

        if (this->currentViewY != 0)
            this->currentViewY--;
        else
            this->currentY--;

        this->moveHorizontal(tmp_size + 1);

    }

    __from_buffer_to_window();
}


void BufferedWindow::deleteCurrentChar()
{
    int lineIndex = this->currentViewY + this->currentY;

    if (this->currentX != this->buffer[lineIndex]->size())
    {
        std::vector<__BufferItem*>::iterator rowIter = this->buffer[lineIndex]->begin();

        delete (*this->buffer[lineIndex])[this->currentX];
        (*this->buffer[lineIndex]).erase(rowIter + this->currentX);

    } else {
        if (lineIndex + 1 == this->buffer.size())
            return;

        for (int i = 0; i < this->buffer[lineIndex + 1]->size(); i++)
        {
            this->buffer[lineIndex]->push_back(
                new __BufferItem(
                    (*this->buffer[lineIndex + 1])[i]->getItemData()->chars[0]
                )
            );

            delete (*this->buffer[lineIndex + 1])[i];
        }


        std::vector<std::vector<__BufferItem*>*>::iterator currLineIter = this->buffer.begin();
        currLineIter += lineIndex + 1;

        delete this->buffer[lineIndex + 1];
        this->buffer.erase(currLineIter);


        if (this->currentViewY != 0)
        {
            this->currentViewY--;

            if (this->currentY + 1 < this->height - 1)
                this->currentY++;
        }

    }

    __from_buffer_to_window();
}


void BufferedWindow::modifyBuffer(wint_t* character)
{
    // call when user modifing the text

    int lineIndex = this->currentY + this->currentViewY;

    std::vector<__BufferItem*>::iterator bufferLineIter = this->buffer[lineIndex]->begin();
    this->buffer[lineIndex]->insert(
        bufferLineIter + this->currentX,
        new __BufferItem(*character)
    );

    if (this->currentX != this->width - 1)
    {
        this->currentX++;
    }

//    this->bufferLineSize[lineIndex]++;

    __from_buffer_to_window();
}


void BufferedWindow::__from_buffer_to_window()
{
    // read data from the buffer and add character to new position after moving

    // clear the window
    for (int i = 0; i < this->height; i++)
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

            __add_item_to_window(
                this->window,
                i, n,
                (*this->buffer[this->currentViewY + i])[this->currentViewX + n]->getItemData()
            );
        }
    }
    wmove(this->window, this->currentY, this->currentX);

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
        std::wfstream file("/mnt/d/pyrus/PreM/text_out", std::ios::out);

        std::locale loc(std::locale(), new std::codecvt_utf8_utf16<wchar_t>);
        file.imbue(loc);

        for (int i = 0; i < this->buffer.size(); i++)
        {
            for (int n = 0; n < this->buffer[i]->size(); n++)
            {
                line += (*this->buffer[i])[n]->getItemData()->chars[0];
            }
            file << line << "\n";

            line.clear();
        }
    }

    return false;

}

