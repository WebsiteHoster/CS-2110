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

	p->curRow = 0;
	p->curCol = 0;
	p->facing = 1;
}

void startLevel(Engine *e)
{
	Food foods[e->foodCount];
	for (int i = 0; i < e->foodCount; i++)
	{
		foods[i].type = BURGER;
		foods[i].isEaten = 0;
		foods[i].row = 50 + rand() % 85;
		foods[i].col = 50 + rand() % 165;
		drawImage3(foods[i].row, foods[i].col, BURGER_HEIGHT, BURGER_WIDTH, burger);
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
					/*drawImage3(0, 0, BURGER_HEIGHT, BURGER_WIDTH, burger);
					drawImage3(0, 25, PIZZA_HEIGHT, PIZZA_WIDTH, pizza);
					drawImage3(0, 50, CHICKEN_HEIGHT, CHICKEN_WIDTH, chicken);
					drawImage3(0, 75, CAKE_HEIGHT, CAKE_WIDTH, cake);
					drawImage3(0, 100, DONUT_HEIGHT, DONUT_WIDTH, donut);*/
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

				for (int i = 0; i < engine.foodCount; i++)
				{
					//checkCollideFood(engine, player, food);
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
