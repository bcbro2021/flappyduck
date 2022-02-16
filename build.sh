g++ -c main.cpp
g++ main.o -o flappyduck -lsfml-graphics -lsfml-window -lsfml-system
mkdir build
cp flappyduck ./build
cp -r assets ./build
