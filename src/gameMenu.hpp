#pragma once
#include <string>
#include <ncurses.h>




class Menu
{
public:
    Menu(int height,int width,std::string *opt,int num)
    {
        int xmax,ymax;
        getmaxyx(stdscr,ymax,xmax);
        menu_win=newwin(height,width,(ymax/2)-(height/2),(xmax/2)-(width/2));
        this->height=height;
        this->width=width;
        options =opt;
        opt_num = num;
        selected_opt=0;
        keypad(menu_win,true);
    }

    void refresh()
    {
        wrefresh(menu_win);
    }

    void clear()
    {
        wclear(menu_win);
    }
    //this should not be here 
    void help()
    {
        mvwprintw(menu_win,2,2,"a simple snake game writing\n  using ncurses (c++ lib)");
        mvwprintw(menu_win,4,2,"you can play by using \n  arrows or w a s d keys");
        mvwprintw(menu_win,7,2,"to exit press any key");
        wgetch(menu_win);
        this->clear();

    }

    //WINDOW *getwin(){return menu_win;}
    
    void draw()
    { 
        box(menu_win,0,0);
        mvwprintw(menu_win,1,width/2 -5,"Snake Game");
        int start_y=3;
        for(int i=0;i<opt_num;i++)
        { 
            mvwprintw(menu_win,i+start_y,width/2 -5,"%s",options[i].c_str());

            if (selected_opt == i)
            	mvwchgat(menu_win, i+start_y, 1, width-2, A_NORMAL, 1, NULL);
        	else
            	mvwchgat(menu_win, i+start_y, 1, width-2, A_STANDOUT, 0, NULL);
        }
        mvwprintw(menu_win,opt_num+start_y+1,width/2 -5," x to select option");
        refresh();
    }

    int handle_input()
    {
        chtype input = wgetch(menu_win);
        switch (input)
        {
        case KEY_ENTER: case 'x':
            return selected_opt;
            break;
        case KEY_UP: 
            if(selected_opt>0)
                selected_opt--;
            break;
        case KEY_DOWN:
            if(selected_opt<opt_num-1)
                selected_opt++;
            break;
        default:
            break;
        }
        return -1;// -1 mean the user still didnt press entre an any option on the screan
    }

private:
WINDOW *menu_win;
std::string *options;
int opt_num;
int height, width;
int selected_opt;


};

