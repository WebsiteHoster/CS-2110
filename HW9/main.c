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

#define MAX_FOOD 50

Food foods[MAX_FOOD];
int curFoodIndex;

/**
 * Initializes/reinitializes the game to title screen
 */
void init(Engine *e, Player *p)
{
	drawImage3(0, 0, TITLE_HEIGHT, TITLE_WIDTH, title);
	e->state = 0;
	e->level = 0;
	e->score = 0;
	e->timer = 0;

	p->curRow = (SCREEN_HEIGHT / 2) - (RIGHT_HEIGHT / 2);
	p->curCol = (SCREEN_WIDTH / 2) - (RIGHT_WIDTH / 2);
	p->facing = 1;
}

void startLevel(Engine *e, Player *p)
{
	fillScreen(BGCOLOR);
	drawImage3(p->curRow, p->curCol, RIGHT_HEIGHT, RIGHT_WIDTH, right);

	e->state = 1;
	e->level++;
	e->totalFood = 0;
	e->curFood = 0;

	for (curFoodIndex = 0; curFoodIndex < 5; curFoodIndex++)
	{
		addFood(e, foods, curFoodIndex);
	}
}

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	Engine engine;
	Player player;
	char scoreBuffer[11];
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
					srand(engine.timer); //Seed RNG
					startLevel(&engine, &player);
				}
			break;
			case 1: //Main gameplay
				engine.timer++;

				//Save old position
				player.oldRow = player.curRow;
				player.oldCol = player.curCol;

				//Player movement
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

				//Periodically add more food if there are less than 5 on
				//screen and less than 5 * level have appeared in total
				if (engine.timer > 50 && engine.curFood < 5 && engine.totalFood < 5 * engine.level)
				{
					addFood(&engine, foods, curFoodIndex);
					curFoodIndex++;
					engine.timer = 0;
				}

				//Check for collisions and if food is still on the screen
				int isEmpty = 1;
				for (int i = 0; i < 5 * engine.level; i++)
				{
					if (foods[i].isEaten == 0)
					{
						checkCollideFood(&engine, &player, &foods[i]);
						isEmpty = 0;
					}
				}

				//If no food is left, go to state 2
				if (isEmpty == 1)
				{
					engine.state = 2;
				}

				//Print score on screen
				sprintf(scoreBuffer, "Score: %d", engine.score);
				drawRect(151, 1 + 6 * 7, 8, 6 * 4, BGCOLOR);
				drawString(151, 1, scoreBuffer, BLACK);

				//Test controls
				if (KEY_DOWN_NOW(BUTTON_A))
					engine.state = 2;
				else if (KEY_DOWN_NOW(BUTTON_B))
					engine.state = 3;
			break;
			case 2: //Win screen
				drawImage3(0, 0, WIN_HEIGHT, WIN_WIDTH, win);

				if (KEY_DOWN_NOW(BUTTON_START))
				{
					startLevel(&engine, &player);
				}
			break;
			case 3: //Lose screen
				drawImage3(0, 0, LOSE_HEIGHT, LOSE_WIDTH, lose);
			break;
		}
	} // while gameloop
}
