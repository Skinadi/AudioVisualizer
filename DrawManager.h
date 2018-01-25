#ifndef DrawManager_h
#define DrawManager_h

#include <SFML/Graphics.hpp>
#include "FFT.h"
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;
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
    void createrectanglescircle(double origin,double radius, int amount, double rectanglewidth, double rectangleheight=-300)
    {
        sf::RectangleShape rect (sf::Vector2f(rectanglewidth,rectangleheight));
        double unitangle = 360/(double)amount;
        for(int i = 0; i<amount; i++)
        {
            rect.setPosition(origin + radius*sin(i*unitangle*3.14f/180),800-(origin + radius * cos(i*unitangle*3.14f/180)));
            rect.setRotation(i*unitangle);
            //cout << i*unitangle << " " << sin(i*unitangle) << endl;
            //cout << sin(3.14f) << " " << sin(6.28f) << " " << sin(180) << " " << sin(360) << endl;
            rects.push_back(rect);
        }
        //rect.setRotation(45);
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
