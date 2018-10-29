# AudioVisualizer
Application process .wav audio PCM file and show "sound" using FMT library to calculate data and SFML library to display results.

## Used Libraries
SFML 2.4
FFTW3
FFMPEG - tool for conversion

## How to launch
### Ubuntu
##### Installing needed libraries
Open Terminal and paste:
- sudo apt-get install libsfml-dev
- sudo apt-get install libfftw3-dev
- sudo apt-get install ffmpeg
##### Building and launching
Go to repository catalog, open terminal and paste
- g++ -c AudioVisualizer.cpp
- g++ AudioVisualizer.o -o AudioVisualizer -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lfftw3

Launch with command 
- ./AudioVisualizer

if not working paste **chmod u+x AudioVisualizer** and try again






