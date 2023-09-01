#pragma once
#include <ncurses.h>
#include <iostream>
#include <fstream>
#include "border.hpp"
#include "apple.hpp"
#include "empty.hpp"
#include "snake.hpp"
#include "scoreboard.hpp"





class SnakeGame
{
public:
    SnakeGame(int height,int width,int speed)
    {
        board = Board(height,width,speed);
        int sb_row=board.getStartRow() + height;
        int sb_col=board.getStartCol();
        score=0;
        scoreboard = Scoreboard(width,sb_row,sb_col);
        scoreboard.initialize(score);
        initialize();
        
    }

    void processInput()
    {
        chtype input = board.getInput();
        int old_timeout=board.getTimeout();

        switch (input)
        {
        case KEY_UP: case 'w':
            snake.setDirection(up);
            break;
        case KEY_DOWN: case 's':
            snake.setDirection(down);
            break;
        case KEY_RIGHT: case 'd':
            snake.setDirection(right);
            break;
        case KEY_LEFT: case 'a':
            snake.setDirection(left);
            break;
        case 'p':
            board.setTimeout(-1) ;//block input
            while(board.getInput() != 'p')
                ;
            board.setTimeout(old_timeout) ;
            break;
        default:
            break;
        }
    }

    void initialize()
    {
        board.initialize();
        game_over= false;
        srand(time(NULL));
        apple=NULL;

        snake.setDirection(down);
        
        handleNextPiece(SnakePiece(1,1));
        handleNextPiece(snake.nextHead());
        handleNextPiece(snake.nextHead());


        snake.setDirection(right);

        handleNextPiece( snake.nextHead());

        //creat apple
        if(apple == NULL)
            creatApple();


    }

    void updateState()
    {
        if(apple == NULL)
            creatApple();
        SnakePiece next= snake.nextHead();
        
        handleNextPiece(next);

        
    }



    void redraw()
    {
        board.refresh();
        scoreboard.refresh();
    }

    bool is_over()
    {
        return game_over;
    }

    int getScore()
    {
        return score;
    }

    void store_score()
    {
        if( !game_over) return;
        std::ofstream scoreFile;
        scoreFile.open ("./data/score.txt",std::ios::app);
        scoreFile << score<<'\n';  
        scoreFile.close();

    }

    int best_score()
    {
        std::ifstream scoreFile;
        scoreFile.open("./data/score.txt");
        int best_score=0,temp=0;
        while(scoreFile >> temp)    
            if(temp > best_score)
                best_score=temp;
        scoreFile.close();
        return best_score;
   
    }

    



private:
//data members
    Board board;
    bool game_over;
    Apple *apple;
    Snake snake;
    Scoreboard scoreboard;
    int score;

//implementation methods
    void creatApple()
    {
        int x,y;
        board.getEmptyCoordinates(y,x);
        apple = new Apple(y,x);
        board.add(*apple);
    }

    void handleNextPiece(SnakePiece next)
    {
        
        if(apple != NULL)
        {
            switch (board.getchartAt(next.gety(),next.getx()))
            {
            case 'A':
                eatApple();
                break;
            case ' ':
            {
                int emptyRow = snake.tail().gety();
                int emptyCol = snake.tail().getx();
                board.add(Empty(emptyRow,emptyCol));
                snake.removePiece();
                break;
            }
            default:
                game_over=true;
                break;
            }
        }
        
        board.add(next);
        snake.addPiece(next);
    }

    void eatApple()
    {
        delete apple;
        apple = NULL;
        score +=100;
        scoreboard.updateScore(score);
    }
};