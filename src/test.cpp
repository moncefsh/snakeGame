#include "gameMenu.hpp"


#define BOARD_DIM 13
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM* 2.5


int main()
{
    initscr();
    refresh();
    noecho();

    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLUE);
    curs_set(0);

    std::string st[3]={"play" ,  "help" ,"quit"};

    Menu menu(BOARD_ROWS,BOARD_COLS,st,3);
    while(true)
    {
        menu.draw();
        if(menu.handle_input()!=-1) break;
        
    }
    

    

    endwin();

    return 0;


}