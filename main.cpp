#include "src/snakeGame.hpp"
#include "src/gameMenu.hpp"

#define BOARD_DIM 13
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM* 2.5

enum OPTIONS
{
    PASS=-1,
    PLAY=0,
    HELP=1,
    QUIT=2
};

int main()
{
    initscr();
    refresh();
    noecho();
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLUE);
    curs_set(0);
    std::string ops[3]={"play" ,  "help" ,"quit"};
    { 
    Menu  gmenu(BOARD_ROWS,BOARD_COLS,ops,3);

    bool in_menu=true;
    while(in_menu)
    {
        gmenu.draw();
        int key=gmenu.handle_input();
        switch (key)
        {
        case PASS:
            break;
        case PLAY:
            in_menu=false;
            gmenu.clear();
            gmenu.refresh();
            break;
        case QUIT:
            endwin();
            return 0;
        case HELP:
        {
            gmenu.clear();
            gmenu.help();
            break;
        }
        default:
            break;
        }
        
        
    }
    }
    SnakeGame game(BOARD_ROWS,BOARD_COLS,200);
    while(!game.is_over())
    {
        game.processInput();
        game.updateState();
        game.redraw();
    }

    clear();
    bool new_best=false;
    int best_score= game.best_score();
    if(best_score < game.getScore())
    {
        new_best=true;
        best_score =game.getScore();

    }
        
    game.store_score();
    int ymax,xmax;
    getmaxyx(stdscr,ymax,xmax);
    int y_pos=(ymax/2)-(BOARD_ROWS/2);
    int x_pos= (xmax/2)-(BOARD_COLS/2);
    mvprintw(y_pos,x_pos,"GAME OVER ");
    mvprintw(y_pos+1,x_pos,"Score : %d",game.getScore());
    if(new_best) 
        printw("  !new best!");
    mvprintw(y_pos+2,x_pos,"Best Score : %d",best_score);
    mvprintw(y_pos+4,x_pos,"to quit press q ");

    char ch;
    while(ch=getch())
        if(ch=='q')
            break;
    endwin();

    return 0;
}