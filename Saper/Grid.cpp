#include "Grid.h"

void Grid::build()
{
    tiles=(Tile**)malloc((X+2)*sizeof(Tile*));
    for(int i=0; i<X+2; i++)
    {
        tiles[i]=(Tile*)malloc((Y+2)*sizeof(Tile));
        for(int j=0; j<Y+2; j++)
        {
            tiles[i][j].value=0;
            tiles[i][j].mode=0;
        }
    }
}
void Grid::increase_mine_neighbours(int x, int y)
{
    if(tiles[x][y].value!=9)
    {
        tiles[x][y].value++;
    }
}
void Grid::reveal_tile(int x, int y)
{
    if(tiles[x][y].mode==1)
    {
        return;
    }
    tiles[x][y].mode=1;
    if(x>0 && y>0 && x<X+1 && y<Y+1)
    {
        revealed_tiles++;
        if(revealed_tiles==X*Y-n)
        {
            game_state=2;
        }
        if(tiles[x][y].value==0)
        {
            reveal_tile(x,y+1);
            reveal_tile(x,y-1);
            reveal_tile(x+1,y);
            reveal_tile(x-1,y);
            reveal_tile(x+1,y+1);
            reveal_tile(x-1,y+1);
            reveal_tile(x+1,y-1);
            reveal_tile(x-1,y-1);
        }
    }
}
void Grid::create_mines(int x_start, int y_start)
{
    srand(time(nullptr));
    int indexes[X*Y];
    for(int i=0; i<X*Y; i++)
    {
        indexes[i]=i+1;
    }
    int tiles_removed=0;
    indexes[(y_start-1)*X+x_start-1]=indexes[X*Y-1-tiles_removed];
    tiles_removed++;
    if(y_start>1)
    {
        indexes[(y_start-2)*X+x_start-1]=indexes[X*Y-1-tiles_removed];
        tiles_removed++;
    }
    if(x_start>1)
    {
        indexes[(y_start-1)*X+x_start-2]=indexes[X*Y-1-tiles_removed];
        tiles_removed++;
    }
    if(y_start<Y)
    {
        indexes[(y_start)*X+x_start-1]=indexes[X*Y-1-tiles_removed];
        tiles_removed++;
    }
    if(x_start<X)
    {
        indexes[(y_start-1)*X+x_start]=indexes[X*Y-1-tiles_removed];
        tiles_removed++;
    }
    if(y_start<Y && x_start>1)
    {
        indexes[(y_start)*X+x_start-2]=indexes[X*Y-1-tiles_removed];
        tiles_removed++;
    }
    if(y_start>1 && x_start<X)
    {
        indexes[(y_start-2)*X+x_start]=indexes[X*Y-1-tiles_removed];
        tiles_removed++;
    }
    if(y_start>1 && x_start>1)
    {
        indexes[(y_start-2)*X+x_start-2]=indexes[X*Y-1-tiles_removed];
        tiles_removed++;
    }
    if(y_start<Y && x_start<X)
    {
        indexes[(y_start)*X+x_start]=indexes[X*Y-1-tiles_removed];
        tiles_removed++;
    }
    for(int i=0; i<n; i++)
    {
        int chosen=rand()%(X*Y-tiles_removed);
        int x=(indexes[chosen]-1)%X+1;
        int y=(indexes[chosen]-1)/X+1;
        tiles[x][y].value=9;
        increase_mine_neighbours(x,y+1);
        increase_mine_neighbours(x,y-1);
        increase_mine_neighbours(x+1,y);
        increase_mine_neighbours(x-1,y);
        increase_mine_neighbours(x+1,y+1);
        increase_mine_neighbours(x-1,y+1);
        increase_mine_neighbours(x+1,y-1);
        increase_mine_neighbours(x-1,y-1);
        indexes[chosen]=indexes[X*Y-1-tiles_removed];
        tiles_removed++;
    }
}
void Grid::terminate()
{
    for(int i=0; i<X+2; i++)
    {
        delete tiles[i];
    }
    delete tiles;
}