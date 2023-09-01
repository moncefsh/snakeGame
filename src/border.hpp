#pragma once

#include <ncurses.h>
#include "drawable.hpp"
#include <time.h>
#include <stdlib.h>
#include "time.hpp"




class Board
{
public:
    Board(int height ,int width,int speed)
    {
        constructer( height, width,speed);

    }

    Board()
    {
        constructer(0,0,300);
    }

    void initialize()
    {
        clear();
        refresh();
    }

    void add(Drawable drawable)
    {
        mvwaddch(board_win,drawable.gety(),drawable.getx(),drawable.geticon());
    }

    void addAt(int y,int x, char ch)
    {
        mvwaddch(board_win,y,x,ch);
    }

    chtype getInput()
    {
        time_t time_last_input = Time::milleseconds();
        chtype input = wgetch(board_win);
        chtype new_input= ERR;
        setTimeout(0);
        while(time_last_input + timeout >= Time::milleseconds())
            new_input = wgetch(board_win);

        setTimeout(timeout);

        if(new_input != ERR)
            input = new_input;
        return input;
    }

    chtype getchartAt(int y,int x)
    {
        return mvwinch(board_win,y,x);
    }

    void getEmptyCoordinates(int &y,int &x)
    {
        while(mvwinch(board_win,y=rand() % height,x=rand() % width) !=' ')
            ;
    }

    void addborder()
    {
        box(board_win,0,0);
    }

    void clear()
    {
        wclear(board_win);
        addborder();
    }

    void refresh()
    {
        wrefresh(board_win);
    }

    void setTimeout(int timeout)
    {
        wtimeout(board_win,timeout);
    }
    int getStartRow(){return start_row;}
    int getStartCol(){return start_col;}
    int getTimeout()
    {
        return timeout;
    }

private:
    WINDOW *board_win;
    int height,width,start_row,start_col;
    int timeout;
    void constructer(int height,int width,int speed)
    {
        int xmax,ymax;
        getmaxyx(stdscr,ymax,xmax);
        board_win=newwin(height,width,(ymax/2)-(height/2),(xmax/2)-(width/2));
        this->height=height;
        this->width=width;
        timeout=speed;

        start_row=(ymax/2)-(height/2);
        start_col=(xmax/2)-(width/2);
        keypad(board_win,true);

        wtimeout(board_win,speed);
    }
};