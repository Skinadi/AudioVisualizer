#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "WAVreader.h"
#include "FFT.h"
#include "DrawManager.h"
#include <vector>
using namespace std;

int main()
{

    string name;
    cout << "Wpisz nazwe muzyki: " << endl;
    //cin >> name;
    WAVReader * file = new WAVReader("BLANKFIELD-Goodbye.wav");
    FFT * channel1 = new FFT(file,22,0);
    FFT * channel2 = new FFT(file,22,1);

    sf::Clock clock;
    sf::Time time = sf::microseconds(0);

    sf::RenderWindow window(sf::VideoMode(800, 800), "AudioVisualizer");
    sf::Music music;
    music.openFromFile("BLANKFIELD-Goodbye.wav");
    music.setVolume(20);
    music.play();
    //sf::RectangleShape rect (sf::Vector2f(rectanglewidth,rectangleheight));
    //rect.getSize().x;
    DrawManager * drawmanager = new DrawManager(window,channel1);
    drawmanager->createrectangles(0,400,800,800,100,5);
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
        }
        time += clock.restart();
        cout << time.asMicroseconds() << endl;
        if(time.asMicroseconds() > 1.0f/channel1->getFPS() * 1000000)
            {
                time = sf::microseconds(0);
                channel1->calkulateNext();
                channel2->calkulateNext();
                drawmanager->updaterectangles();
            }
        window.clear();
        drawmanager->drawrectangles();
        window.display();
    }
    return 0;
}
