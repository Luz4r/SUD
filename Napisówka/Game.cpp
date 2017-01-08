#include "Game.h"

void Game::intro()
{
	int ycord, xcord;
	char mesg[] = "Witaj w mojej grze ktora nie wyjdzie, ale probuje sie czegos nauczyc!";
	getmaxyx(stdscr, ycord, xcord);
	attron(COLOR_PAIR(1));
	attron(A_BOLD);
	mvprintw(ycord/3, (xcord-strlen(mesg))/2,"%s", mesg);
	attroff(A_BOLD);
	attroff(COLOR_PAIR(1));
	attron(A_REVERSE);
	mvprintw((ycord/2)+2, (xcord-6)/2, "ENJOY!\n");
	move((ycord / 2) + 2, (xcord / 2) + 3);
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
	player = new Character();
	state = MENU;
}


Game::~Game()
{
	delete player;
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
			play();
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

Character Game::createPlayer()
{
	char *name;
	Character::Rasa playerRace;
	Character::Klasa playerClass;

	unsigned short int number;

	printw("Podaj swoje imie: ");
	echo();
	getstr(name = new char[sizeof name]);

	do {
		chooseRace();
		number = getch();
	} while (number < 49 || number > 52);

	switch (number)
	{
	case 49:
		playerRace = Character::Cz³owiek;
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
		playerClass = Character::£ucznik;
		break;
	case 51:
		playerClass = Character::£otrzyk;
		break;
	}

	noecho();

	Character* createdPlayer = new Character(name, playerRace, playerClass, 500, 50, 50, 55, 80, 50);		//example player character with stats, which goes to fight
	clear();
	printw("Imie: %s\nRasa: %s\nKlasa: %s", createdPlayer -> getCharName(), createdPlayer -> getRace(), createdPlayer -> getClass());

	saveGame(*createdPlayer);

	return *createdPlayer;
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
				*player = createPlayer();
				loadGame();
				state = GAME;
				getch();
				break;
			case 2:
				clear();
				loadGame();
				state = GAME;
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

void Game::saveGame(Character& savingPlayer)
{
	unsigned short int choice;
		
	do {
		clear();
		attron(A_REVERSE);
		printw("Czy napewno chcesz zapisac gre?!\n\n");
		printw("To usunie twoje poprzednie zapisy!\n\n");
		attroff(A_REVERSE);
		printw("Wybierz liczbe:\n\n");
		printw("1. TAK\n");
		printw("2. NIE\n\n");
		printw(": ");
		echo();
		choice = getch();
		noecho();
	} while (choice != 49 && choice != 50);

	if (choice == 49)
	{
		Gamesaver save =
		{
			savingPlayer.getValue(Character::getHealth),
			savingPlayer.getValue(Character::HitChance),
			savingPlayer.getValue(Character::CritChance),
			savingPlayer.getValue(Character::DamageMin),
			savingPlayer.getValue(Character::DamageMax),
			savingPlayer.getValue(Character::Defense),
			savingPlayer.getValue(Character::CharacterRace),
			savingPlayer.getValue(Character::CharacterClass)
		};

		ofstream file("save.bin", ios::binary);
		if (file.good())
		{
			file.write((const char *)& save, sizeof save);
			file.write((savingPlayer.getStringName()).c_str(), savingPlayer.getStringName().size() + 1);
			file.close();
		}
		else
		{
			clear();
			printw("Wystapil blad podczas zapisywania pliku");
		}
	}
	else {
		clear();
		printw("Nie wykonano zapisu");
	}
}

void Game::loadGame()
{
	Gamesaver save;
	string name;

	ifstream file("save.bin", ios::binary);

	if (file.good())
	{
		file.read((char *)& save, sizeof(save));
		getline(file, name, '\0');
	
		player = new Character(name, Character::Rasa(save.charRace), Character::Klasa(save.charClass), save.health, save.defense_value, save.damage_min, save.damage_max, save.hit_chance, save.crit_chance);
	}
	else
	{
		printw("Twoj zapis jest niemozliwy do odczytania");
	}
	file.close();
}

void Game::play()
{
	state = GAME;
	//Character gnom("Gnom", Character::Gnom, Character::Wojownik, 200, 20, 53, 74, 69, 9);					//Example fight
	//fight(*player, gnom);
	state = MENU;
}

void Game::fight(Character a, Character b)
{
	state = FIGHT;
	clear();
	printw("Rozpoczynasz walke z %s\n\n", b.getCharName());

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

	printw("Punkty zycia %s: %d\n", a.getCharName(), a_health);
	printw("Punkty zycia %s: %d\n\n", b.getCharName(), b_health);
	getch();


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
		printw("%s zadaje %d obrazen %s\n", a.getCharName(), a_damage, b.getCharName());
		printw("%s zadaje %d obrazen %s\n\n", b.getCharName(), b_damage, a.getCharName());

		printw("Punkty zycia %s: %d\n",a.getCharName(), a_health);
		printw("Punkty zycia %s: %d\n",b.getCharName(), b_health);

		if (a_health == 0 || b_health == 0)  //When Character has 0 health
		{
			a.setValue(Character::setHealth, a_health);
			b.setValue(Character::setHealth, b_health);
			getch();
			clear();
			if (a_health == 0)
				printw("Wygrywa: %s", b.getCharName());
			else
				printw("Wygrywa: %s", a.getCharName());
			state = GAME;
		}
		getch();
	}
}
