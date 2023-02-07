
#ifndef _WINDOW_CONTAINER_H_
#define _WINDOW_CONTAINER_H_

#include <memory>
#include <vector>
#include <variant>

#include "BaseWindow.h"
#include "BufferedWindow.h"
#include "SimpleWindow.h"


class _Layout;

typedef std::vector<std::variant<BufferedWindow*, SimpleWindow*>> __L_WindowObjects;
typedef std::vector<std::shared_ptr<_Layout>> __L_Container;



enum class _LayoutPolicy
{
    HORIZONTAL,
    VERTICAL

};



class _Layout
{
private:
    __L_WindowObjects __win_objects;

    short __id;
    _LayoutPolicy __policy;
    int __width;
    int __height;

public:
    _Layout() = delete;
    _Layout(short id, _LayoutPolicy policy, int width, int height);

    short getId();
    __L_WindowObjects& getWinObjects();
    _LayoutPolicy getLayoutPolicy();

    void addWindow(BufferedWindow* window);

    void addWindow(SimpleWindow* window);

};




enum class _WinTypes
{
    SIMPLE,
    BUFFERED
};




// only horizontal orientation (only for the first time)
// TODO: add vertical policy to WindowContainer
class WindowContainer: public BaseWindow
{
private:
    __L_Container __layouts;

    int __width;
    int __height;

public:
    WindowContainer();
    ~WindowContainer();

    void init();
    void update();

    void addLayout(short /* layout id */, float, float);
    _Layout* getLayoutById(short);

    template <typename T>
    void addWindowToLayoutById(short, T*, _WinTypes, void*);

};


template <typename T>
void WindowContainer::addWindowToLayoutById(short id, T* window, _WinTypes win_type, void* unique_param)
{
    _Layout* _layout = this->getLayoutById(id);

    if (_layout)
    {
        if (!window)
        {
            if (win_type == _WinTypes::BUFFERED)
                window = new T(20, 20, (char*)unique_param);
            else
                window = new T(20, 20, (_StringContainer*)unique_param);

        }

        _layout->addWindow(window);

    }

    // FIX

}






#endif
