/**
 * Jesse Chen
 */

#include "myLib.h"
#include "text.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

//Include images
#include "title.h"
#include "win.h"
#include "lose.h"
#include "player.h"
#include "food.h"
#include "broccoli.h"

Food_t foodTypes[5] = {BURGER, PIZZA, CHICKEN, CAKE, DONUT};
Food foods[5];

/**
 * Initializes/reinitializes the game to title screen
 */
void init(Engine *e, Player *p)
{
	drawImage3(0, 0, TITLE_HEIGHT, TITLE_WIDTH, title);
	e->state = 0;
	e->level = 1;
	e->timer = 0;
	e->foodCount = 5;

	p->curRow = (SCREEN_HEIGHT / 2) - (RIGHT_HEIGHT / 2);
	p->curCol = (SCREEN_WIDTH / 2) - (RIGHT_WIDTH / 2);
	p->facing = 1;
}

void startLevel(Engine *e)
{
	for (int i = 0; i < e->foodCount; i++)
	{
		foods[i].type = foodTypes[rand() % 5];
		foods[i].isEaten = 0;
		foods[i].row = rand() % 135;
		foods[i].col = rand() % 215;

		int height = 0;
		int width = 0;
		const u16 *image;

		switch (foods[i].type)
		{
			case BURGER:
				height = BURGER_HEIGHT;
				width = BURGER_WIDTH;
				image = burger;
			break;
			case PIZZA:
				height = PIZZA_HEIGHT;
				width = PIZZA_WIDTH;
				image = pizza;
			break;
			case CHICKEN:
				height = CHICKEN_HEIGHT;
				width = CHICKEN_WIDTH;
				image = chicken;
			break;
			case CAKE:
				height = CAKE_HEIGHT;
				width = CAKE_WIDTH;
				image = cake;
			break;
			case DONUT:
				height = DONUT_HEIGHT;
				width = DONUT_WIDTH;
				image = donut;
			break;
			default:
				height = BURGER_HEIGHT;
				width = BURGER_WIDTH;
				image = burger;
			break;
		}

		drawImage3(foods[i].row, foods[i].col, height, width, image);
	}
}

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	Engine engine;
	Player player;
	init(&engine, &player);

	while (1) //Game loop
	{
		WaitForVblank();

		if (KEY_DOWN_NOW(BUTTON_SELECT))
		{
			init(&engine, &player);
		}

		switch (engine.state) //Determine game state
		{
			case 0: //Title screen
				engine.timer++;

				if (KEY_DOWN_NOW(BUTTON_START))
				{
					srand(engine.timer);

					fillScreen(BGCOLOR);

					drawImage3(player.curRow, player.curCol, RIGHT_HEIGHT, RIGHT_WIDTH, right);
					engine.state = 1;

					startLevel(&engine);
				}
			break;
			case 1: //Main gameplay
				player.oldRow = player.curRow;
				player.oldCol = player.curCol;

				if (KEY_DOWN_NOW(BUTTON_UP))
					movePlayer(&player, 0);
				if (KEY_DOWN_NOW(BUTTON_DOWN))
					movePlayer(&player, 1);
				if (KEY_DOWN_NOW(BUTTON_LEFT))
					movePlayer(&player, 2);
				if (KEY_DOWN_NOW(BUTTON_RIGHT))
					movePlayer(&player, 3);
				else
					movePlayer(&player, -1);

				int isEmpty = 1;
				for (int i = 0; i < engine.foodCount; i++)
				{
					if (foods[i].isEaten == 0)
					{
						checkCollideFood(&engine, &player, &foods[i]);
						isEmpty = 0;
					}
				}

				if (isEmpty == 1)
				{
					engine.state = 2;
				}

				if (KEY_DOWN_NOW(BUTTON_A))
					engine.state = 2;
				else if (KEY_DOWN_NOW(BUTTON_B))
					engine.state = 3;
			break;
			case 2: //Win screen
				drawImage3(0, 0, WIN_HEIGHT, WIN_WIDTH, win);
			break;
			case 3: //Lose screen
				drawImage3(0, 0, LOSE_HEIGHT, LOSE_WIDTH, lose);
			break;
		}
	} // while gameloop
}
