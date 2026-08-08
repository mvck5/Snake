#include "apple.h"
#include "random.h"

Apple::Apple(WINDOW* win, Snake& snake, char image):
	m_win{ win },
	m_snake{ snake },
	m_image{ image },
	m_pos{Point2d(15,12)} {
	getmaxyx(m_win, m_yMax, m_xMax);
	newPos();
}

void Apple::newPos() {
	bool allowed{ true };
	do {
		m_pos = Point2d(Random::get(1, m_xMax-2), Random::get(1, m_yMax-2));
		for (Point2d point : m_snake.getBody()) {
			if (m_pos == point) {
				allowed = false;
				break;
			}
		}
	} while (!allowed); // makess sure apple doesn't spawn in snakes body
	
}

bool Apple::checkEaten() {
	if (m_snake.getHead() == m_pos) {
		return true;
	}
	return false;
}

void Apple::display() {
	mvwaddch(m_win, m_pos.y, m_pos.x, m_image);
	wrefresh(m_win);
}
