#include "snake.h"

Snake::Snake(WINDOW* win, char image) :
	m_win{ win },
	m_body{ Point2d(1,1)},
	m_image{ image },
	m_dir{ Right },
	m_lastDir{ Right },
	m_tail{ 0 },
	m_head{ 0 } {
		getmaxyx(m_win, m_yMax, m_xMax);
		m_body.reserve((m_yMax-2)*(m_xMax-2));
}

void Snake::changeDir(int c) {
	switch (c) {
	case 'w':
		if (m_lastDir != Down) {
			m_dir = Up;
		}
		break;
	case 'a':
		if (m_lastDir != Right) {
			m_dir = Left;
		}
		break;
	case 's':
		if (m_lastDir != Up) {
			m_dir = Down;
		}
		break;
	case 'd':
		if (m_lastDir != Left) {
			m_dir = Right;
		}
		break;
	default:
		break;
	}
}

void Snake::display() {
	for (Point2d point: m_body) {
		mvwaddch(m_win,point.y,point.x,m_image);
	}
	wrefresh(m_win);
}

void Snake::move(bool eaten) {
	switch (m_dir) {
	case Up:
		m_lastDir = Up;
		break;
	case Down:
		m_lastDir = Down;
		break;
	case Left:
		m_lastDir = Left;
		break;
	case Right:
		m_lastDir = Right;
		break;
	}

	if (!eaten) {
		mvwaddch(m_win, m_body[m_tail].y, m_body[m_tail].x, ' '); //change the tail to an empty cell
		m_body[m_tail] = m_body[m_head]; //set the tail equal to the head
		switch (m_dir) { // move in direction to make the old tail the new head
		case Up:
			m_body[m_tail].y--;
			break;
		case Left:
			m_body[m_tail].x--;
			break;
		case Down:
			m_body[m_tail].y++;
			break;
		case Right:
			m_body[m_tail].x++;
			break;
		}

		m_head = m_tail;

		if (m_tail == m_body.size()-1) {
			m_tail = 0;
		}
		else {
			m_tail++;
		}
		
	}
	else{
		switch (m_dir) {
		case Up:
			m_body.insert(m_body.begin() + m_head + 1 , Point2d(m_body[m_head].x, m_body[m_head].y - 1));
			break;
		case Down:
			m_body.insert(m_body.begin() + m_head + 1 ,Point2d(m_body[m_head].x, m_body[m_head].y + 1));
			break;
		case Left:
			m_body.insert(m_body.begin() + m_head + 1 , Point2d(m_body[m_head].x - 1, m_body[m_head].y));
			break;
		case Right:
			m_body.insert(m_body.begin() + m_head + 1 , Point2d(m_body[m_head].x + 1, m_body[m_head].y));
			break;
		}
		m_head++;

		if (m_tail != 0) {
			m_tail++;
		}
		
	}

	display();
}	

bool Snake::checkDead() {
	if (m_body[m_head].x == m_xMax-1 || m_body[m_head].y == m_yMax-1 || m_body[m_head].x == 0 || m_body[m_head].y == 0){
		return true;
	}

	for (int i{ 1 };i < m_body.size();i++) {
		for (int j{ 0 };j < m_body.size()-i;j++) {
			if (m_body[j] == m_body[j+i]) {
				return true;
			}
		}
	}

	return false;
}

bool Snake::checkWon() {
	return m_body.size() > ((m_yMax - 5) * (m_xMax - 5));
}

Point2d Snake::getHead() {
	return m_body[m_head];
}
std::vector<Point2d>& Snake::getBody() {
	return m_body;
}
