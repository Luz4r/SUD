#include "Game.h"


void Game::intro()
{
	attron(COLOR_PAIR(1));
	attron(A_BOLD);
	printw("Witaj w mojej grze ktora nie wyjdzie, ale probuje sie czegos nauczyc!\n");
	attroff(A_BOLD);
	attroff(COLOR_PAIR(1));
	attron(A_REVERSE);
	printw("ENJOY!\n");
	attroff(A_REVERSE);
}

Game::Game()
{
	initscr();
	if (has_colors() == false)
	{
		endwin();
		printf("Twoja konsola nie obsluguje kolorow\n");
		return;
	}
	state = MENU;
}


Game::~Game()
{
	endwin();
}

void Game::runGame()
{
	createColors();
	intro();
	noecho();
	getch();
	while (state != END)
	{
		switch (state)
		{
		case MENU:
			runMenu();
			break;
		case GAME:
			break;
		}
	}
}

void Game::createColors()
{
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
}

void Game::runMenu()
{
	do
	{
		keypad(stdscr, true);
		clear();
		printw("Wybierz opcje:\n");
		switch (which)
		{
		case 1:
			attron(A_REVERSE);
			printw("%s\n", option1);
			attroff(A_REVERSE);
			printw("%s\n", option2);
			printw("%s\n", option3);
			break;
		case 2:
			printw("%s\n", option1);
			attron(A_REVERSE);
			printw("%s\n", option2);
			attroff(A_REVERSE);
			printw("%s\n", option3);
			break;
		case 3:
			printw("%s\n", option1);
			printw("%s\n", option2);
			attron(A_REVERSE);
			printw("%s\n", option3);
			attroff(A_REVERSE);
			break;
		}
		mark = getch();
		if (mark == KEY_UP && which != 1)
			which--;
		else if (mark == KEY_DOWN && which != 3)
			which++;
		else if (mark == KEY_UP && which == 1)
			which = 3;
		else if (mark == KEY_DOWN && which == 3)
			which = 1;
		if (mark == 10)
		{
			switch (which)
			{
			case 1:
				clear();
				printw("Tutaj rozpoczniesz nowa rozgrywke\n");
				play();
				getch();
				break;
			case 2:
				clear();
				printw("Tutaj wczytasz swoja zapisana gre\n");
				play();
				getch();
				break;
			case 3:
				clear();
				state = END;
				break;
			}
		}
	} while (state == MENU);
}

void Game::play()
{
	Player player(10, "Rafal", "Czlowiek", "Wojownik");
	Enemy wolf(5, "Wolf", "Wolf", "Wojownik");
	fight(wolf, player);
}

void Game::fight()
{
	state = FIGHT;
	while (FIGHT == state)
	{
	
	}
}
