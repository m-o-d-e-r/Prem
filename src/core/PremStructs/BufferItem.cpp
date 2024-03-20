
#include "BufferItem.h"





char __get_buffer_item_data(int int_ch) {
    return static_cast<char>(int_ch);
}

wchar_t __get_buffer_item_data(wint_t uint_ch)
{
    return static_cast<wchar_t>(uint_ch);

    /*cchar_t cchar_data;

    cchar_data.attr = 0;
    cchar_data.chars[0] = uint_ch;
    cchar_data.chars[1] = L'\0';

    return cchar_data;*/
}


ASCIIBufferItem::ASCIIBufferItem(int int_ch)
    : BaseBufferItem<char, int>(int_ch)
{

}


UnicodeBufferItem::UnicodeBufferItem(wint_t uint_ch)
    : BaseBufferItem<wchar_t, wint_t>(uint_ch)
{

}
