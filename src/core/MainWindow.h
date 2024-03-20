/*#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <ncurses.h>

#include "PremCycle.h"
#include "PremStructs/Trie.h"



class MainWindow
{
private:
    CommandTrie trieObject;

    WINDOW* codeEditorWin;
    WINDOW* userHintWin;
    WINDOW* statusBarWin;

    int scrollValue = 0;

    int globalWidth;
    int globalHeight;

    int currentX = 0;
    int currentY = 0;

private:
    void __setUpCodeEditorWin(int, int, int, int);
    void __setUpUserHintWin(int, int, int, int);
    void __setUpStatusbarWin(int, int, int, int);

    void __updateCodeEditorWin();
    void __updateUserHitWin();
    void __updateStatusBarWin();
    void __updateAll();

    bool __isInRange_w(int);
    bool __isInRange_h(int);

public:

    MainWindow();
    ~MainWindow();

    void initializeWindow();

    void show();

};


#endif
*/