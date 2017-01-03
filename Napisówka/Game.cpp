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
	srand(time(NULL));
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
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
}

void Game::createPlayer()
{
	char *name;
	Character::Rasa playerRace;
	Character::Klasa playerClass;

	unsigned short int number;

	printw("Podaj swoje imie: ");
	echo();
	getstr(name = new char [sizeof(name)]);

	do {
		chooseRace();
		number = getch();
	} while (number < 49 || number > 52);

	switch (number)
	{
	case 49:
		playerRace = Character::Cz�owiek;
		break;
	case 50:
		playerRace = Character::Elf;
		break;
	case 51:
		playerRace = Character::Krasnolud;
		break;
	case 52:
		playerRace = Character::Gnom;
		break;
	}

	do {
		chooseClass();
		number = getch();
	} while (number < 49 || number > 51);

	switch (number)
	{
	case 49:
		playerClass = Character::Wojownik;
		break;
	case 50:
		playerClass = Character::�ucznik;
		break;
	case 51:
		playerClass = Character::�otrzyk;
		break;
	}

	noecho();

	Character player(name, playerRace, playerClass);
	clear();
	printw("Imie: %s\nRasa: %s\nKlasa: %s", player.getName(), player.getRace(), player.getClass());
}

void Game::chooseRace()
{
	clear();
	printw("Wybierz rase swojej postaci:");
	mvprintw(2, 0, "1. Czlowiek");
	mvprintw(3, 0, "2. Elf");
	mvprintw(4, 0, "3. Krasnolud");
	mvprintw(2, 15, "4. Gnom");
	mvprintw(3, 15, "5. ...");
	mvprintw(4, 15, "6. ...");
	mvprintw(6, 0, "Wybierz numer: ");
}

void Game::chooseClass()
{
	clear();
	printw("Wybierz klase swojej postaci:");
	mvprintw(2, 0, "1. Wojownik");
	mvprintw(3, 0, "2. Lucznik");
	mvprintw(4, 0, "3. Lotrzyk");
	mvprintw(2, 15, "4. ...");
	mvprintw(3, 15, "5. ...");
	mvprintw(4, 15, "6. ...");
	mvprintw(6, 0, "Wybierz numer: ");
}

void Game::runMenu()
{
	const char option1[12] = "1. Nowa Gra";
	const char option2[15] = "2. Wczytaj gre";
	const char option3[9] = "3. Wyjdz";

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
				createPlayer();
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
	state = GAME;
	/*Character player(300, "Rafal", Krasnolud, Wojownik, 40, 30, 100, 76, 14);
	Character wolf(200, "Wilk", Wilk, Wojownik, 20, 53, 74, 69, 9);					//Example fight
	state = FIGHT;
	fight(player, wolf);*/
	state = MENU;
}

void Game::fight(Character a, Character b)
{
	clear();
	printw("Rozpoczynasz walke z %s\n", b.getName());
	getch();

	//Character a, values
	unsigned short int a_health = a.getValue(Character::getHealth);
	unsigned short int a_defense = (a.getValue(Character::Defense)/2);
	unsigned short int a_rawDamage;
	unsigned short int a_damage;

	//Character b, values
	unsigned short int b_health = b.getValue(Character::getHealth);
	unsigned short int b_defense = (b.getValue(Character::Defense)/2);
	unsigned short int b_rawDamage;
	unsigned short int b_damage;


	while (state == FIGHT)
	{
		//Character a
		unsigned short int a_hitchance = rand() % 1000 + 1;
		unsigned short int a_critchance = rand() % 1000 + 1;

		//Character b
		unsigned short int b_hitchance = rand() % 1000 + 1;
		unsigned short int b_critchance = rand() % 1000 + 1;

		if (a_hitchance <= (a.getValue(Character::HitChance)*10))  //Character a, randomazing hitchance
		{
			a_rawDamage = rand() % ((a.getValue(Character::DamageMax) - a.getValue(Character::DamageMin)) + 1) + a.getValue(Character::DamageMin);
			if (a_critchance <= (a.getValue(Character::CritChance) * 10))  //Character a - check if crit
			{
				a_rawDamage *= 2;
			}
			if (a_rawDamage < b_defense)
				a_damage = 0;
			else
				a_damage = (a_rawDamage - b_defense);

			if (a_damage > b_health)
				a_damage = b_health;
		}
		else
			a_damage = 0;

		if (b_hitchance <= (b.getValue(Character::HitChance)*10))  //Character b, randomazing hitchance
		{
			b_rawDamage = rand() % ((b.getValue(Character::DamageMax) - b.getValue(Character::DamageMin)) + 1) + b.getValue(Character::DamageMin);
			if (b_critchance <= (b.getValue(Character::CritChance) * 10))  //Character b - check if crit
			{
				b_rawDamage *= 2;
			}
			if (b_rawDamage < a_defense)
				b_damage = 0;
			else
				b_damage = (b_rawDamage - a_defense);

			if (b_damage > a_health)
				b_damage = a_health;
		}
		else
			b_damage = 0;
		
		a_health -= b_damage;  //Dealing dmg
		b_health -= a_damage;

		clear();
		printw("%s zadaje %d obrazen %s\n", a.getName(), a_damage, b.getName());
		printw("%s zadaje %d obrazen %s\n\n", b.getName(), b_damage, a.getName());

		printw("Punkty zycia %s: %d\n",a.getName(), a_health);
		printw("Punkty zycia %s: %d\n",b.getName(), b_health);

		if (a_health == 0 || b_health == 0)  //When Character has 0 health
		{
			a.setValue(Character::setHealth, a_health);
			b.setValue(Character::setHealth, b_health);
			//getch();
			state = GAME;
		}
		getch();
	}
}
