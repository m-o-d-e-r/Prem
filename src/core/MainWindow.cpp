#include "MainWindow.h"

#define CTRL_(x) ((x) & 0x1f)
#define KEY_ENTER 0x157


void MainWindow::__setUpCodeEditorWin(int w, int h, int ox, int oy)
{
    this->codeEditorWin = newwin(h, w, oy, ox);
    box(this->codeEditorWin, 0, 0);
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


void MainWindow::__updateCodeEditorWin() {wrefresh(this->codeEditorWin);}
void MainWindow::__updateUserHitWin() {wrefresh(this->userHintWin);}
void MainWindow::__updateStatusBarWin() {wrefresh(this->statusBarWin);}
void MainWindow::__updateAll()
{
    wrefresh(this->codeEditorWin);
    wrefresh(this->userHintWin);
    wrefresh(this->statusBarWin);
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

    while (TRUE)
    {
        key_code = wgetch(this->codeEditorWin);
        key_type = keyRouter(key_code);


        if (key_type == KeyType::CURSOR_MOVE)
        {
            if (key_code == KEY_UP)
            {
                currentY--;
            } else if (key_code == KEY_DOWN)
            {
                currentY++;
            } else if (key_code == KEY_LEFT)
            {
                currentX--;
            } else if (key_code == KEY_RIGHT)
            {
                currentX++;
            }

            wmove(this->codeEditorWin, currentY, currentX);
        } else {
            if (key_code == CTRL_('x'))
                break;
            
            if (key_code == KEY_ENTER)
            {

            }

            mvwprintw(this->codeEditorWin, currentY, currentX, keyname(key_code));
            wmove(this->codeEditorWin, currentY, ++currentX);

            this->__updateCodeEditorWin();
        }
    }
}
