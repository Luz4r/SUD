#include "Player_Commands.h"


Player_Commands::Player_Commands(Game *game)
	: _game(game)
{
}


Player_Commands::~Player_Commands()
{
}

void Player_Commands::look()
{
	attron(COLOR_PAIR(3));
	printw("%s\n", _game->currentTile.getCharName());
	attroff(COLOR_PAIR(3));

	attron(COLOR_PAIR(2));
	printw("%s\n\n", _game->currentTile.getDesc());
	attroff(COLOR_PAIR(2));
}

void Player_Commands::save_game()
{
	File_Manager::save_game(*_game);
}

void Player_Commands::load_game()
{
	File_Manager::load_game(*_game);
}

void Player_Commands::playerInfo()
{
	printw("Imie: %s\nRasa: %s\nKlasa: %s\n", _game->player->getCharName(), _game->player->getRace(), _game->player->getClass());
	printw("X: %d\nY: %d\n", _game->player->getValue(Character::CORDX), _game->player->getValue(Character::CORDY));
}

void Player_Commands::goToMenu()
{
	_game->state = Game::MENU;
	save_game();
}

void Player_Commands::quit()
{
	_game->state = Game::END;
	save_game();
}

void Player_Commands::move_north()
{
	auto cordinates = _game->all_tiles.find({ _game->player->getValue(Character::CORDX), (_game->player->getValue(Character::CORDY) + 1) });
	if (cordinates != _game->all_tiles.end())
	{
		_game->player->setValue(Character::CORDY_plus, 1);
		_game->currentTile = cordinates->second;
		look();
	}
	else
	{
		attron(A_REVERSE);
		printw("Nie mozesz sie tam ruszyc!\n\n");
		attroff(A_REVERSE);
	}
}

void Player_Commands::move_south()
{
	auto cordinates = _game->all_tiles.find({ _game->player->getValue(Character::CORDX), (_game->player->getValue(Character::CORDY) - 1) });
	if (cordinates != _game->all_tiles.end())
	{
		_game->player->setValue(Character::CORDY_minus, 1);
		_game->currentTile = cordinates->second;
		look();
	}
	else
	{
		attron(A_REVERSE);
		printw("Nie mozesz sie tam ruszyc!\n\n");
		attroff(A_REVERSE);
	}
}

void Player_Commands::move_west()
{
	auto cordinates = _game->all_tiles.find({ (_game->player->getValue(Character::CORDX) - 1), _game->player->getValue(Character::CORDY) });
	if (cordinates != _game->all_tiles.end())
	{
		_game->player->setValue(Character::CORDX_minus, 1);
		_game->currentTile = cordinates->second;
		look();
	}
	else
	{
		attron(A_REVERSE);
		printw("Nie mozesz sie tam ruszyc!\n\n");
		attroff(A_REVERSE);
	}
}

void Player_Commands::move_east()
{
	auto cordinates = _game->all_tiles.find({ (_game->player->getValue(Character::CORDX) + 1), _game->player->getValue(Character::CORDY) });
	if (cordinates != _game->all_tiles.end())
	{
		_game->player->setValue(Character::CORDX_plus, 1);
		_game->currentTile = cordinates->second;
		look();
	}

	else
	{
		attron(A_REVERSE);
		printw("Nie mozesz sie tam ruszyc!\n\n");
		attroff(A_REVERSE);
	}
}

void Player_Commands::fight(string str)
{
	auto mob = _game->currentTile.tile_mobs.find(str);

	if (mob != _game->currentTile.tile_mobs.end())
	{
		clear();
		Character b = mob->second;
		_game->state = Game::FIGHT;
		printw("Rozpoczynasz walke z %s\n\n", b.getCharName());

		//Character a, values
		int player_health = _game->player->getValue(Character::getHealth);
		int player_defense = (_game->player->getValue(Character::Defense) / 2);
		int player_rawDamage;
		int player_damage;

		//Character b, values
		int b_health = b.getValue(Character::getHealth);
		int b_defense = (b.getValue(Character::Defense) / 2);
		int b_rawDamage;
		int b_damage;

		printw("Punkty zycia %s: %d\n", _game->player->getCharName(), player_health);
		printw("Punkty zycia %s: %d\n\n", b.getCharName(), b_health);

		printw("Wcisnij [ENTER]: ");
		getch();

		while (_game->state == Game::FIGHT)
		{
			//Character a
			int player_hitchance = rand() % 1000 + 1;
			int player_critchance = rand() % 1000 + 1;

			//Character b
			int b_hitchance = rand() % 1000 + 1;
			int b_critchance = rand() % 1000 + 1;

			if (player_hitchance <= (_game->player->getValue(Character::HitChance) * 10))  //Character a, randomazing hitchance
			{
				player_rawDamage = rand() % ((_game->player->getValue(Character::DamageMax) - _game->player->getValue(Character::DamageMin)) + 1) + _game->player->getValue(Character::DamageMin);
				if (player_critchance <= (_game->player->getValue(Character::CritChance) * 10))  //Character a - check if crit
				{
					player_rawDamage *= 2;
				}
				if (player_rawDamage < b_defense)
					player_damage = 0;
				else
					player_damage = (player_rawDamage - b_defense);

				if (player_damage > b_health)
					player_damage = b_health;
			}
			else
				player_damage = 0;

			if (b_hitchance <= (b.getValue(Character::HitChance) * 10))  //Character b, randomazing hitchance
			{
				b_rawDamage = rand() % ((b.getValue(Character::DamageMax) - b.getValue(Character::DamageMin)) + 1) + b.getValue(Character::DamageMin);
				if (b_critchance <= (b.getValue(Character::CritChance) * 10))  //Character b - check if crit
				{
					b_rawDamage *= 2;
				}
				if (b_rawDamage < player_defense)
					b_damage = 0;
				else
					b_damage = (b_rawDamage - player_defense);

				if (b_damage > player_health)
					b_damage = player_health;
			}
			else
				b_damage = 0;

			player_health -= b_damage;  //Dealing dmg
			b_health -= player_damage;

			clear();
			printw("%s zadaje %d obrazen %s\n", _game->player->getCharName(), player_damage, b.getCharName());
			printw("%s zadaje %d obrazen %s\n\n", b.getCharName(), b_damage, _game->player->getCharName());

			printw("Punkty zycia %s: %d\n", _game->player->getCharName(), player_health);
			printw("Punkty zycia %s: %d\n", b.getCharName(), b_health);

			if (player_health == 0 || b_health == 0)  //When Character has 0 health
			{
				_game->player->setValue(Character::setHealth, player_health);
				(mob->second).setValue(Character::setHealth, b_health);
				printw("\n");
				if (player_health == 0)
					printw("Wygrywa: %s \n", b.getCharName());
				else
				{
					printw("Wygrywa: %s \n", _game->player->getCharName());
					_game->currentTile.tile_mobs.erase(mob);
				}
				_game->state = Game::GAME;
				printw("Wcisnij jakikolwiek przycisk aby kontynuowac");
				getch();
				clear();
				break;
			}
			refresh();
			wait(1);
		}
	}
	else
		printw("Z kim chcesz walczyc?\n");

	clear();
	look();
}


void Player_Commands::wait(int seconds)
{
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}
