#pragma once
#include <ncurses.h>

class Drawable
{
public:

    Drawable():x(0),y(0),icon(' '){}
    Drawable(int xx,int yy,chtype ch):x(xx),y(yy),icon(ch){}
    int getx(){return x;}
    int gety(){return y;}
    chtype geticon(){return icon;}



protected:
    int y,x;
    chtype icon;
};