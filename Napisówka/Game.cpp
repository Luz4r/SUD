#include "Player_Commands.h"

void Game::intro()
{
	char mesg[] = "Witaj w mojej grze ktora jest pretekstem do nauki C++";
	attron(COLOR_PAIR(1));
	attron(A_BOLD);
	mvprintw(ycord/3, (xcord-strlen(mesg))/2,"%s", mesg);
	attroff(A_BOLD);
	attroff(COLOR_PAIR(1));
	attron(A_REVERSE);
	mvprintw((ycord/2)+2, (xcord-6)/2, "ENJOY!\n");
	mvcur(0, 0, (ycord / 2) + 2, (xcord / 2) + 3);
	attroff(A_REVERSE);
}

void Game::create_colors()
{
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
}

Game::Game()
{
	initscr();
	resize_term(60, 120);
	scrollok(stdscr, TRUE);
	getmaxyx(stdscr, ycord, xcord);
	srand(time(nullptr));
	if (has_colors() == false)
	{
		endwin();
		printf("Twoja konsola nie obsluguje kolorow\n");
		exit(1);
	}
	player = new Character();
	player_commands = new Player_Commands(this);

	create_colors();
	create_commands();
	
	state = MENU;
}


Game::~Game()
{
	delete player;
	delete player_commands;
	endwin();
}

void Game::run_game()
{
	intro();
	noecho();
	getch();
	while (state != END)
	{
		switch (state)
		{
		case MENU:
			run_menu();
			break;
		case GAME:
			play();
			break;
		}
	}
}

void Game::run_menu()
{
	unsigned short int which = 1;
	unsigned short int mark;

	const char *choices[] = {
		"1. Nowa Gra",
		"2. Wczytaj gre",		//menu choices
		"3. Wyjdz",
	};

	int n_choices = sizeof(choices) / sizeof(char *);

	do
	{
		keypad(stdscr, true);
		clear();
		attron(COLOR_PAIR(1));
		mvprintw((ycord / 3), (xcord - 14) / 2, "Wybierz opcje:");
		attroff(COLOR_PAIR(1));
		int y = 2;

		for (int i = 0; i < n_choices; i++)
		{
			if (which == i + 1)
			{
				attron(A_REVERSE);
				mvprintw((ycord / 3) + y, (xcord - strlen(choices[i])) / 2, "%s", choices[i]);
				attroff(A_REVERSE);
			}
			else
				mvprintw((ycord / 3) + y, (xcord - strlen(choices[i])) / 2, "%s", choices[i]);
			y++;
		}

		mark = getch();
		if (mark == KEY_UP && which != 1)
			which--;
		else if (mark == KEY_DOWN && which != n_choices)
			which++;
		else if (mark == KEY_UP && which == 1)
			which = 3;
		else if (mark == KEY_DOWN && which == n_choices)
			which = 1;
		if (mark == 10)
		{
			switch (which)
			{
			case 1:
				clear();
				createPlayer();
				if (state != GAME)
					break;
				player_commands->save_game();
				getch();
				break;
			case 2:
				clear();
				player_commands->load_game();
				break;
			case 3:
				clear();
				state = END;
				break;
			}
		}
	} while (state == MENU);
}

void Game::checkInput()
{
	char* buffor = new char[50];
	char* buffor2 = new char[50];

	printw("Wpisz komende [save, quit, kill <mob>, info, menu, north, south, west, east, look]: ");
	echo();
	scanw("%s%s", buffor, buffor2);
	printw("\n");
	noecho();

	auto search = commands.find(buffor);
	auto search2 = commands2.find(buffor);
	if (search != commands.end())
	{
		myfunction = search->second;
		(player_commands->*(this->myfunction))();
	}
	else if (search2 != commands2.end())
	{
		myfunction2 = search2->second;
		(player_commands->*(this->myfunction2))(buffor2);
	}
	else
		printw("Nie znaleziono komendy!\n\n");

	delete[] buffor;
	delete[] buffor2;
}

void Game::play()
{
	Character gnome("Gnome", Character::Gnome, Character::Wojownik, 200, 20, 53, 74, 69, 9);
	currentTile.tile_mobs["gnome"] = gnome;
	clear();
	player_commands->look();
	while (GAME == state)
	{
		checkInput();
	}
}

void Game::createPlayer()
{
	char *buffor = new char[50];
	Character::Rasa playerRace;
	Character::Klasa playerClass;

	char number;

	mvprintw((ycord / 3), (xcord - 19) / 2, "Podaj swoje imie: ");

	echo();

	getnstr(buffor, 50);

	string stringname = buffor;

	delete[] buffor;

	do {
		chooseRace();
		number = getch();
	} while (number < '1' || number > '4');

	switch (number)
	{
	case '1':
		playerRace = Character::Cz³owiek;
		break;
	case '2':
		playerRace = Character::Elf;
		break;
	case '3':
		playerRace = Character::Krasnolud;
		break;
	case '4':
		playerRace = Character::Gnome;
		break;
	}

	do {
		chooseClass();
		number = getch();
	} while (number < '1' || number > '3');

	switch (number)
	{
	case '1':
		playerClass = Character::Wojownik;
		break;
	case '2':
		playerClass = Character::£ucznik;
		break;
	case '3':
		playerClass = Character::£otrzyk;
		break;
	}

	noecho();

	player = new Character(stringname, playerRace, playerClass, 500, 50, 50, 55, 80, 50, 0, 0);		//tworzenie gracza

	ifstream file("files\\tiles.txt", ios::in);
		if (file.good())
		{
			string buffor;
			string name;
			string desc;
			int nr_linii = 1;
			ammount_of_tiles = 0;
			vector<int> cords;

			while (getline(file, buffor))
			{
				switch(nr_linii)
				{
				case 1:
					name = buffor;
					break;
				case 2:
					desc = buffor;
					break;
				case 3:
					cords.push_back(stoi(buffor));
					break;
				case 4:
					cords.push_back(stoi(buffor));
					all_tiles[cords] = Tile(name, desc, cords[0], cords[1]);
					ammount_of_tiles++;
					nr_linii = 0;
					cords.clear();
					break;
				}
				nr_linii++;
			}
			
			auto cordinates = all_tiles.find({ 0,0 });
			currentTile = cordinates->second;

			player->setValue(Character::CORDX_replace, currentTile.cords[0]);
			player->setValue(Character::CORDY_replace, currentTile.cords[1]);

			state = GAME;
		}
		else
		{
			clear();
			printw("Nie mozna odczytac pliku: 'tiles.txt' !");
			getch();
			state = MENU;
		}
		file.close();
		clear();
}

void Game::chooseRace()
{
	char *raceChoices[] =
	{
		"1. Czlowiek",
		"2. Elf",
		"3. Krasnolud",				//Rasy
		"4. Gnom",
		"5. ...",
		"6. ..."
	};

	int n_choices = sizeof(raceChoices) / sizeof(char *);
	int y_max = n_choices / 2;

	clear();
	mvprintw((ycord / 3), (xcord - 29) / 2, "Wybierz rase swojej postaci:");

	int y = 2;
	int x = 15;

	for (int i = 0; i < n_choices; i++)
	{
		if (i < y_max)
			mvprintw((ycord / 3) + y, ((xcord - strlen(raceChoices[i])) / 2) - x, "%s", raceChoices[i]);
		else
			mvprintw((ycord / 3) + y, ((xcord - strlen(raceChoices[i])) / 2) + x, "%s", raceChoices[i]);
		y++;
		if (i == y_max - 1)
			y = 2;
	}
	mvprintw((ycord / 3) + y_max + 3, (xcord - 16) / 2, "Wybierz numer: ");
}

void Game::chooseClass()
{
	char *classChoices[] =
	{
		"1. Wojownik",
		"2. Lucznik",
		"3. Lotrzyk",			//Klasy
		"4. ...",
		"5. ...",
		"6. ..."
	};

	int n_choices = sizeof(classChoices) / sizeof(char *);
	int y_max = n_choices / 2;

	clear();
	mvprintw((ycord / 3), (xcord - 30) / 2, "Wybierz klase swojej postaci:");

	int y = 2;
	int x = 15;

	for (int i = 0; i < n_choices; i++)
	{
		if (i < y_max)
			mvprintw((ycord / 3) + y, ((xcord - strlen(classChoices[i])) / 2) - x, "%s", classChoices[i]);
		else
			mvprintw((ycord / 3) + y, ((xcord - strlen(classChoices[i])) / 2) + x, "%s", classChoices[i]);
		y++;
		if (i == y_max - 1)
			y = 2;
	}
	mvprintw((ycord / 3) + y, (xcord - strlen("Wybierz numer: ")) / 2, "Wybierz numer: ");
}

void Game::create_commands()
{
	pointer_type pointer[] =
	{
		&Player_Commands::save_game,
		&Player_Commands::quit,
		&Player_Commands::playerInfo,
		&Player_Commands::goToMenu,
		&Player_Commands::move_north,
		&Player_Commands::move_south,
		&Player_Commands::move_west,
		&Player_Commands::move_east,
		&Player_Commands::look
	};

	pointer_type2 pointer2[] =
	{
		&Player_Commands::fight
	};

	string commandName[] =														//tworzenie komend
	{
		"save",
		"quit",
		"info",
		"menu",
		"north",
		"south",
		"west",
		"east",
		"look"
	};

	string commandName2[] =
	{
		"kill"
	};

	int n_pointer = sizeof(pointer) / sizeof(pointer_type);
	int n_pointer2 = sizeof(pointer2) / sizeof(pointer_type);

	for (int i = 0; i < n_pointer; i++)
		commands[commandName[i]] = pointer[i];
	for (int i = 0; i < n_pointer2; i++)
		commands2[commandName2[i]] = pointer2[i];
}