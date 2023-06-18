#ifndef SAPER_GRID_H
#define SAPER_GRID_H
#include <cstdlib>
#include <cstdio>
#include <ctime>

struct Tile
{
    int value; // 0-8 dla pol, 9 dla min
    int mode; // 0 dla zakrytego, 1 dla odkrytego, 2 dla oflagowanego
};

class Grid
{
public:
    Grid(int X, int Y):X(X),Y(Y){};
    void build(); //tworzy plansze
    void increase_mine_neighbours(int x, int y); //kafelek z indeksem x,y zwieksza liczbe sasiadow-min o jeden
    void reveal_tile(int x, int y); //odkrywa kafelek
    void create_mines(int x_start, int y_start); //tworzy miny w zaleznosci od poczatkowo kliknietego pola
    void terminate(); //zwalnia pamiec
    Tile* operator[](int i) //dostep do wartosci kafelkow
    {
        return tiles[i];
    }
    void set_game_state(int i)
    {
        game_state=i;
    }
    int get_game_state() const
    {
        return game_state;
    }
private:
    int X; //szerokosc
    int Y; //wysokosc
    const int n=X*Y/5; //liczba min
    int revealed_tiles=0; //odkryte kafelki - za odkrycie wszystkich jest zwyciestwo
    int game_state=0; //0-ciagle gramy, 1-przegrana, 2-wygrana
    Tile** tiles=nullptr; //dwuwymiarowa tablica z kafelkami
};

#endif //SAPER_GRID_H
