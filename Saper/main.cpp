#include <SFML/Graphics.hpp>
#include "Grid.h"

int main()
{
    const int w=32; //szerokosc kafelkow w pliku
    const int X=12; //szerokosc planszy
    const int Y=12; //wysokosc planszy
    Grid grid(X,Y);
    grid.build();
    sf::RenderWindow window(sf::VideoMode(32*X+64, 32*Y+64), "Saper"); //okno z gra
    sf::Texture tiles;
    tiles.loadFromFile("images/tiles.jpg");
    sf::Sprite s(tiles); //zaladowanie grafiki z kafelkami

    bool mines_created=false;
    while(window.isOpen())
    {
        sf::Event event{};
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
            {
                window.close();
            }
            else if(event.type==sf::Event::MouseButtonPressed)
            {
                sf::Vector2i pos=sf::Mouse::getPosition(window);
                int x=pos.x/w;
                int y=pos.y/w;
                if(event.mouseButton.button==sf::Mouse::Left)
                {
                    if(!mines_created) //po pierwszym kliknieciu tworzy miny
                    {
                        grid.create_mines(x,y); //tworzy miny na planszy
                        mines_created=true;
                    }
                    grid.reveal_tile(x,y); //odkrycie pola
                    if(grid[x][y].value==9)
                    {
                        grid.set_game_state(1); //stan gry zmienia sie na przegrany po odkryciu miny
                    }
                }
                else if(event.mouseButton.button==sf::Mouse::Right && grid[x][y].mode!=1) //oflagowanie lub zdjecie flagi
                {
                    grid[x][y].mode=2-grid[x][y].mode;
                }
            }
        }
        window.clear(sf::Color::White);
        for(int i=1; i<=X; i++) //rysowanie planszy
        {
            for(int j=1; j<=Y; j++)
            {
                if(grid.get_game_state()==0)
                {
                    int column;
                    if(grid[i][j].mode==0)
                    {
                        column=10;
                    }
                    else if(grid[i][j].mode==1)
                    {
                        column=grid[i][j].value;
                    }
                    else
                    {
                        column=11;
                    }
                    s.setTextureRect(sf::IntRect(column*w, grid.get_game_state()*w, w, w)); //wyciecie kafelka z grafiki
                }
                else
                {
                    if(grid[i][j].mode==0)
                    {
                        s.setTextureRect(sf::IntRect(10*w, 0, w, w)); //wyciecie kafelka z grafiki
                    }
                    else if(grid[i][j].mode==1)
                    {
                        s.setTextureRect(sf::IntRect(grid[i][j].value*w, grid.get_game_state()*w, w, w)); //wyciecie kafelka z grafiki
                    }
                    else
                    {
                        s.setTextureRect(sf::IntRect(11*w, 0, w, w)); //wyciecie kafelka z grafiki
                    }
                }
                s.setPosition(i*w, j*w); //nowa pozycja kafelka
                window.draw(s);
            }
        }
        window.display();
        if(grid.get_game_state()!=0) //wygrana lub porazka przerywa zabawe
        {
            while(window.pollEvent(event))
            {
                if(event.type==sf::Event::Closed)
                {
                    window.close();
                }
            }
        }
    }
    grid.terminate(); //zwolnienie pamieci
    return 0;
}
