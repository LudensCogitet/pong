LIBS = -lsfml-graphics -lsfml-window -lsfml-system

CXX = g++
CXXFLAGS = -Wall -g

main: main.o config.o Solid.o Paddle.o Ball.o GuiText.o
	$(CXX) $(CXXFLAGS) -o main main.o config.o Solid.o Paddle.o Ball.o GuiText.o $(LIBS)

main.o: main.cpp config.h
	$(CXX) $(CXXFLAGS) -c main.cpp

config.o: config.cpp config.h
	$(CXX) $(CXXFLAGS) -c config.cpp

Solid.o: Solid.cpp
	$(CXX) $(CXXFLAGS) -c Solid.cpp

Paddle.o: Paddle.cpp
	$(CXX) $(CXXFLAGS) -c Paddle.cpp

Ball.o: Ball.cpp Paddle.h
	$(CXX) $(CXXFLAGS) -c Ball.cpp

GuiText.o: GuiText.cpp GuiText.h
	$(CXX) $(CXXFLAGS) -c GuiText.cpp
