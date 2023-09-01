#pragma once

#include "drawable.hpp"
#include <queue>
#include "snakeGame.hpp"

enum Direction
{
    up=-1,
    down=1,
    left=-2,
    right=2
};

class SnakePiece : public Drawable
{
public:
    SnakePiece()
    {
        this->x = this->y =0;
        this->icon ='#';
    }
    SnakePiece(int y,int x)
    {
        this->x=x;
        this->y=y;
        this->icon ='#';
    }
};

class Snake
{
public:
    Snake()
    {
        cur_direction=down;
    }

    void addPiece(SnakePiece piece)
    {
        prev_pieces.push(piece);
    }

    void removePiece()
    {
        prev_pieces.pop();
    }

    SnakePiece tail()
    {
        return prev_pieces.front();
    }

    SnakePiece head()
    {
        return prev_pieces.back();
    }

    Direction getDirection(){ return cur_direction;}
    void setDirection(Direction D)
    {
        if(cur_direction+D != 0)
        cur_direction=D;
    }

    SnakePiece nextHead()
    {
        int row = head().gety();
        int col = head().getx();

        switch (cur_direction)
        {
        case down:
            row++;
            break;
        case up:
            row--;
            break;
        case right:
            col++;
            break;
        case left:
            col--;
            break;
        }
        return SnakePiece(row,col);
    
    }

private:
    std::queue<SnakePiece> prev_pieces;
    Direction cur_direction;
};