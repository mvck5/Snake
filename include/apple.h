#pragma once
#include <curses.h>
#include "point.h"
#include "snake.h"

class Apple {
private:
	WINDOW* m_win;
	char m_image;
	Point2d m_pos;
	Snake& m_snake;
	int m_xMax;
	int m_yMax;
public:
	Apple(WINDOW* win, Snake& snake, char image = '@');
	void newPos();
	bool checkEaten();
	void display();
};