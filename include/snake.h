#pragma once
#include <curses.h>
#include <vector>
#include "point.h"


class Snake {
private:
	enum Direction {
		Up,Down,Left,Right
	};
	WINDOW* m_win;
	std::vector<Point2d> m_body;
	char m_image;
	Direction m_dir;
	Direction m_lastDir;
	int m_tail;
	int m_head;
	int m_xMax;
	int m_yMax;
public:
	Snake(WINDOW* win, char image = '#');
	void changeDir(int c);
	void display();
	void move(bool eaten);
	bool checkDead();
	bool checkWon();
	Point2d getHead();
	std::vector<Point2d>& getBody();

};