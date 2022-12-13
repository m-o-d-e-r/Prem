#include "MainWindow.h"

#include <iostream>
#include <string>

#define CTRL_(x) ((x) & 0x1f)
#define KEY_ENTER 0x157


void MainWindow::__setUpCodeEditorWin(int w, int h, int ox, int oy)
{
    this->codeEditorWin = newpad(h, w);
//    this->codeEditorWin = newwin(h, w, oy, ox);
    scrollok(this->codeEditorWin, TRUE);
//    box(this->codeEditorWin, 0, 0);
//    prefresh(this->codeEditorWin, this->scrollValue, 0, 0, 0, w, h);
}


void MainWindow::__setUpUserHintWin(int w, int h, int ox, int oy)
{
    this->userHintWin = newwin(h, w, oy, ox);
    box(this->userHintWin, 0, 0);
}


void MainWindow::__setUpStatusbarWin(int w, int h, int ox, int oy)
{
    this->statusBarWin = newwin(h, w, oy, ox);
    box(this->statusBarWin, 0, 0);

    mvwprintw(
        this->statusBarWin,
        1, 1,
        "^X Exit | "
    );
}


void MainWindow::__updateCodeEditorWin()
{
    prefresh(
        this->codeEditorWin, 0, 0,
        0, 0,
        this->globalHeight * 0.9,
        this->globalWidth * 0.7
    );
}
void MainWindow::__updateUserHitWin() {wrefresh(this->userHintWin);}
void MainWindow::__updateStatusBarWin() {wrefresh(this->statusBarWin);}
void MainWindow::__updateAll()
{
    __updateCodeEditorWin();
    __updateUserHitWin();
    __updateStatusBarWin();
}


bool MainWindow::__isInRange_w(int x)
{
    return 0;
}


bool MainWindow::__isInRange_h(int y)
{
    return 0;
}



MainWindow::MainWindow()
{
    initscr();
    cbreak();
    noecho();
    nonl();

    int x, y;
    getmaxyx(stdscr, y, x);
    this->globalWidth = x;
    this->globalHeight = y;

    this->currentX = 1;
    this->currentY = 1;
}


MainWindow::~MainWindow() {}


void MainWindow::initializeWindow()
{
    __setUpCodeEditorWin(
        this->globalWidth * 0.7,
        this->globalHeight * 0.9,
        0,
        0
    );
    __setUpUserHintWin(
        this->globalWidth * 0.3,
        this->globalHeight * 0.9,
        this->globalWidth * 0.7,
        0
    );
    __setUpStatusbarWin(
        this->globalWidth,
        this->globalHeight * 0.1 + 1,
        0,
        this->globalHeight * 0.9
    );

    keypad(this->codeEditorWin, TRUE);

    wmove(this->codeEditorWin, 1, 1);

    this->__updateAll();
}


void MainWindow::show()
{
    int key_code;
    KeyType key_type;

    
/*    for (int i = 0; i < 30; i++)
    {
        wprintw(this->codeEditorWin, std::string("Hello\t" + std::to_string(i) + "\n").c_str());
    }
    this->__updateCodeEditorWin();*/


    while (TRUE)
    {
        key_code = wgetch(this->codeEditorWin);
        key_type = keyRouter(key_code);


        if (key_type == KeyType::CURSOR_MOVE)
        {
            if (key_code == KEY_UP)
            {
                if (currentY - 1 >= 1)
                {
                    currentY--;
//                    wscrl(this->codeEditorWin, 1);
                }
            } else if (key_code == KEY_DOWN)
            {
                if (currentY + 1 < this->globalHeight * 0.9 - 2)
                {
                    currentY++;
//                    wscrl(this->codeEditorWin, -1);
                }
            } else if (key_code == KEY_LEFT)
            {
                if (currentX - 1 >= 1)
                {
                    currentX--;
                }
            } else if (key_code == KEY_RIGHT)
            {
                if (currentX + 1 <= this->globalWidth * 0.7 - 2)
                {
                    currentX++;
                }
            }

            wmove(this->codeEditorWin, currentY, currentX);
        } else {
            if (key_code == CTRL_('x'))
            {
                break;
            } else {
                if (currentX + 2 <= this->globalWidth * 0.7 - 1)
                {
                    mvwprintw(this->codeEditorWin, currentY, currentX, keyname(key_code));
                    wmove(this->codeEditorWin, currentY, ++currentX);
                }
            }
        }
        this->__updateCodeEditorWin();
    }
}
