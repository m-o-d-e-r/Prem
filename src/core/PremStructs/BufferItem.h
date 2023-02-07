
#ifndef _BUFFER_ITEM_H_
#define _BUFFER_ITEM_H_

#include <ncurses.h>


//#define PREM_USE_UNICODE_BUFFER


class UnicodeBufferItem;
class ASCIIBufferItem;

#ifdef PREM_USE_UNICODE_BUFFER
    #define __PremChar wchar_t

    #define __BufferItem UnicodeBufferItem
    #define __add_item_to_window(win, y, x, char_value) (mvwadd_wch(win, y, x, char_value))

#else
    #define __PremChar char

    #define __BufferItem ASCIIBufferItem
    #define __add_item_to_window(win, y, x, char_value) (mvwaddch(win, y, x, char_value))

#endif



char __get_buffer_item_data(int int_ch);
wchar_t __get_buffer_item_data(wint_t uint_ch);



template <typename ItemType, typename ItemIntegerType>
class BaseBufferItem
{
protected:
    ItemType data;

public:
    BaseBufferItem() = delete;
    BaseBufferItem(ItemIntegerType);

    ItemType& getItemData();

};


template <typename ItemType, typename ItemIntegerType>
BaseBufferItem<ItemType, ItemIntegerType>::BaseBufferItem(ItemIntegerType i_value)
{
    this->data = __get_buffer_item_data(i_value);
}


template <typename ItemType, typename ItemIntegerType>
ItemType& BaseBufferItem<ItemType, ItemIntegerType>::getItemData()
{
    return this->data;
}



class ASCIIBufferItem: public BaseBufferItem<char, int>
{
public:
    ASCIIBufferItem() = delete;
    ASCIIBufferItem(int);

};


class UnicodeBufferItem: public BaseBufferItem<wchar_t, wint_t>
{
public:
    UnicodeBufferItem() = delete;
    UnicodeBufferItem(wint_t);

};




#endif
