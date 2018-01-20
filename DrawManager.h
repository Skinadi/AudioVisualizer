#ifndef DrawManager_h
#define DrawManager_h

#include <SFML/Graphics.hpp>
#include "FFT.h"
#include <vector>

class DrawManager
{
private:


public:
    sf::RenderWindow * window;
    FFT * channel;
    vector <sf::RectangleShape> rects;
    DrawManager(sf::RenderWindow & window, FFT * channel )
    {
        this->window = &window;
        this->channel = channel;
    }

    ~DrawManager()
    {
        rects.clear();
    }

    void createrectangles(float x,float y,float width, float height, int amount, float rectanglewidth, float rectangleheight=-300)
    {
        float spacewidth = (width - amount * rectanglewidth)/(amount-1);
        sf::RectangleShape rect (sf::Vector2f(rectanglewidth,rectangleheight));
        rect.setPosition(x,y);
        for(int i = 0; i<amount; i++)
        {
            rect.setPosition(x,y);
            rects.push_back(rect);
            x+=rectanglewidth + spacewidth;
        }
    }
    void updaterectangles()
    {
        /*int j = 0;
        for(int i = 0; i<channel->get_data_size()/2; i+=channel->get_data_size()/2/ rects.size())
        {
            rects[j].setSize(sf::Vector2f(rects[j].getSize().x, -1* channel->tab[i].magnitude));
            j++;
        }*/
        int z = 0;
        double maxmagnitude = -1;
        for(int i = 0; i<channel->get_data_size()/2; i+=(channel->get_data_size()/2)/ rects.size())
        {
            maxmagnitude = -1;
            for(int j = i; j<i+(channel->get_data_size()/2)/rects.size() && j<channel->get_data_size()/2 ;j++)
            {
                maxmagnitude = max(maxmagnitude,channel->tab[j].magnitude);
                //cout << channel->tab[j].magnitude << endl;
            }
            if(z<rects.size())
            rects[z].setSize(sf::Vector2f(rects[z].getSize().x, -1*abs(-1 *channel->tab[i].magnitude+80)));
            z++;
        }
    }
    void drawrectangles()
    {
        for(int i = 0; i<rects.size(); i++)
        {
            window->draw(rects[i]);
        }
    }
};
#endif
