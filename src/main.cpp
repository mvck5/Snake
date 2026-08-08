#include <curses.h>
#include <string>
#include <iostream>
#include "timer.h"
#include "snake.h"
#include "apple.h"


void displayBoard(WINDOW* win,Snake& snake, Apple& apple) {
	snake.display();
	apple.display();
}


int main() {
	///////////////////////////////////////////////////////game settings
	double speed;
	int size;
	std::cout << "What speed would you like (10-1): ";
	std::cin >> speed;
	std::cout << "What size board would you like (10-1): ";
	std::cin >> size;
	///////////////////////////////////////////////////////



	/* CURSES START */
	initscr(); // initialises the screen
	noecho(); // makes user input not visible on screen
	cbreak(); //sets input to be unbuffered
	timeout(10);

	int yMax{};
	int xMax{};
	getmaxyx(stdscr, yMax, xMax);

	
	WINDOW* board;
	
	switch (size) {//creates newwin(height,width,start_y,start_x)
	case 1:
		board = newwin(yMax - 5, xMax - 40, (yMax / 2) - 13, 5);
		break;
	case 2:
		board = newwin(yMax - 7, xMax - 46, (yMax / 2) - 13, 5);
		break;
	case 3:
		board = newwin(yMax - 9, xMax - 52, (yMax / 2) - 13, 5);
		break;
	case 4:
		board = newwin(yMax - 11, xMax - 58, (yMax / 2) - 13, 5);
		break;
	case 5:
		board = newwin(yMax - 13, xMax - 64, (yMax / 2) - 13, 5);
		break;
	case 6:
		board = newwin(yMax - 15, xMax - 70, (yMax / 2) - 13, 5);
		break;
	case 7:
		board = newwin(yMax - 17, xMax - 76, (yMax / 2) - 13, 5);
		break;
	case 8:
		board = newwin(yMax - 19, xMax - 82, (yMax / 2) - 13, 5);
		break;
	case 9:
		board = newwin(yMax - 21, xMax - 88, (yMax / 2) - 13, 5);
		break;
	case 10:
		board = newwin(yMax - 23, xMax - 94, (yMax / 2) - 13, 5);
		break;
	default:
		board = newwin(yMax - 25, xMax - 40, (yMax / 2) - 13, 5);
		break;
	}
	
	WINDOW* instructions{ newwin(yMax - 22, xMax - 100, (yMax / 2) - 13, 95) };
	wborder(instructions, '|', '|', '-', '-', '#', '#', '#', '#');
	refresh();
	wrefresh(instructions);
	mvwprintw(instructions, 1, 1, "w - move up");
	mvwprintw(instructions, 2, 1, "a - move left");
	mvwprintw(instructions, 3, 1, "s - move down");
	mvwprintw(instructions, 4, 1, "d - move right");
	mvwprintw(instructions, 5, 1, "q - quit");
	mvwprintw(instructions, 6, 1, "p - pause/unpause");
	wrefresh(instructions);

	
	

	//window border(window,left,right,top,bottom,tlc,trc,blc,brc)
	wborder(board, '|', '|', '-', '-', '#', '#', '#', '#');
	refresh();
	wrefresh(board);

	int c{};
	Timer time{};
	Snake snake(board);
	Apple apple(board,snake);

	/////////////////////////////////////////////////////// main game loop
	while (true) {
		displayBoard(board, snake, apple);
		c = getch();
		time.start();
		time.end();
		while (time.getDuration() < speed / 50) {
			snake.changeDir(c);
			time.end();
		}
		if (c == 'q') {
			printw("You quit");
			break;
		}	
		if (c == 'p') {
			mvprintw(0,0,"Paused      ");
			c = -1;
			while (true) {
				c = getch();
				if (c == 'p') {
					mvprintw(0,0,"Unpaused    ");
					break;
				}
			}
		}
		if (snake.checkWon()) {
			printw("You won");
			break;
		}
		if (apple.checkEaten()) {
			snake.move(true);
			apple.newPos();
		}
		else {
			snake.move(false);
		}
		if (snake.checkDead()) {
			printw("You died");
			break;
		}
	}
	///////////////////////////////////////////////////////


	timeout(5000);
	clear();
	mvprintw(yMax/2, xMax/2-14, "***Thank you for playing***");
	getch();
	getch();
	getch();
	getch();
	getch();
	endwin(); // deallocates memory, ends curses
	/* CURSES END */

	return 0;
}