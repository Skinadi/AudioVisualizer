#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "WAVreader.h"
#include "FFT.h"
#include <vector>
using namespace std;

int main()
{

    string name;
    cout << "Wpisz nazwe muzyki: " << endl;
    cin >> name;
    WAVReader * file = new WAVReader("CryThunder.wav");
    FFT * channel1 = new FFT(file,60,0);
    FFT * channel2 = new FFT(file,60,1);

    sf::Clock clock;
    sf::Time time = sf::microseconds(0);

    sf::RenderWindow window(sf::VideoMode(800, 800), "AudioVisualizer");
    sf::Music music;
    music.openFromFile("CryThunder.wav");
    music.setVolume(20);
    music.play();
    vector <sf::RectangleShape> rects;
    sf::RectangleShape rect(sf::Vector2f(1,300));
    rect.setPosition(50,50);
    for(int i = 0; i<800; i++)
    {
        rect.setPosition(i,300);
        rects.push_back(rect);
        //rects[i].setSize(sf::Vector2f(i,50));
    }
    //sf::RectangleShape rect(sf::Vector2f(1,50));
    //rect.setPosition(50,50);
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
        if(time.asMicroseconds() > 1.0f/60.0f * 1000000)
            {
                time = sf::microseconds(0);
                channel1->calkulateNext();
                channel2->calkulateNext();
                for(int i = 0; i<400; i++)
                {
                    //rects[i].setPosition(i,channel1->tab[i].magnitude);
                    //rects[i+400].setPosition(i+400,channel2->tab[i].magnitude);
                    rects[i].setSize(sf::Vector2f(1,-5*(channel1->tab[i].magnitude-40)));
                    rects[i+400].setSize(sf::Vector2f(1,-5*(channel2->tab[i].magnitude-40)));
                }
            }
        window.clear();
        for(int i = 0; i<800; i++)
            window.draw(rects[i]);
        window.display();
    }
    return 0;
}
