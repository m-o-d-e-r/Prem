
#ifndef _SIMPLE_WINDOW_H_
#define _SIMPLE_WINDOW_H_

#include <string>
#include <vector>

#include "BaseWindow.h"

typedef std::vector<std::string> _StringContainer;



enum class _SW_Vector_Policy
{
    HORIZONTAL,
    VERTICAL
};




class SimpleWindow: public BaseWindow
{
private:
    WINDOW* __window;

    int __width;
    int __height;
    _StringContainer* __data;
    _SW_Vector_Policy __policy;

public:
    SimpleWindow() = delete;
    SimpleWindow(int, int, _StringContainer*, _SW_Vector_Policy);
    ~SimpleWindow();

    void init();
    void update();

    WINDOW* getWindow() {return __window;}

};


#endif
