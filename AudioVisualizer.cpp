#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "WAVreader.h"
#include "FFT.h"
#include "DrawManager.h"
#include <vector>
#include <math.h>
using namespace std;

int main()
{
    string name1;
    cout << "Wpisz nazwe muzyki: " << endl;
    cin >> name1;
    string name = "ffmpeg -i ";
    name+=name1;
    name+=" 0.wav";
    system(name.c_str());
    WAVReader * file = new WAVReader("0.wav");
    FFT * channel1 = new FFT(file,21,0);
    FFT * channel2 = new FFT(file,21,1);

    sf::Clock clock;
    sf::Time time = sf::microseconds(0);

    sf::RenderWindow window(sf::VideoMode(800, 800), "AudioVisualizer");
    sf::Music music;
    music.openFromFile("0.wav");
    music.setVolume(20);
    music.play();
    //sf::RectangleShape rect (sf::Vector2f(rectanglewidth,rectangleheight));
    //rect.getSize().x;
    DrawManager * drawmanager1 = new DrawManager(window,channel1);
    drawmanager1->createrectangles(0,400,800,800,100,6);

    DrawManager * drawmanager2 = new DrawManager(window,channel2);
    drawmanager2->createrectangles(0,400,800,800,100,6,300);

    //DrawManager * drawmanager3 = new DrawManager(window,channel2);
    //drawmanager3->createrectanglescircle(400,-300,200,5);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                {
                    window.close();
                    music.stop();
                }
            if(event.type == sf::Event::KeyPressed)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    window.close();
                    music.stop();
                }
            }
        }
        time += clock.restart();
        //cout << time.asMicroseconds() << endl;
        if(time.asMicroseconds() > 1.0f/channel1->getFPS() * 1000000)
            {
                time = sf::microseconds(0);
                channel1->calkulateNext();
                channel2->calkulateNext();
                drawmanager1->updaterectangles(-1);
                drawmanager2->updaterectangles(1);
                //drawmanager3->updaterectangles();
            }
        window.clear();
        drawmanager1->drawrectangles();
        drawmanager2->drawrectangles();
        //drawmanager3->drawrectangles();
        window.display();
    }
    system("rm -f 0.wav");
    return 0;
}
