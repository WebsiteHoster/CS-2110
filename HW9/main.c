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

/*#define NUMOBJS 7

typedef struct {

	int row;
	int col;
	int rd;
	int cd;
	int size;
	u16 color;
} MOVOBJ;*/

/*int state;
int curRow;
int curCol;
int oldRow, oldCol;
int facing;*/

/**
 * Initializes/reinitializes the game to title screen
 */
void init(Engine *e, Player *p)
{
	drawImage3(0, 0, TITLE_HEIGHT, TITLE_WIDTH, title);
	e->state = 0;
	e->timer = 0;
	e->foodCount = 0;

	p->curRow = (SCREEN_HEIGHT / 2) - (RIGHT_HEIGHT / 2);
	p->curCol = (SCREEN_WIDTH / 2) - (RIGHT_WIDTH / 2);
	p->facing = 1;
}

/**
 * Checks boundaries and moves player
 *
 * @param dir Direction the player is facing
 *				0: up
 *				1: down
 *				2: left
 *				3: right
 */
/*void move(int dir)
{
	switch (dir) //Change row/col position
	{
		case 0:
			curRow--;
		break;
		case 1:
			curRow++;
		break;
		case 2:
			curCol--;
			facing = 0;
		break;
		case 3:
			curCol++;
			facing = 1;
		break;
	}

	boundsCheck(&curRow, SCREEN_HEIGHT - 1, 0, RIGHT_HEIGHT);
	boundsCheck(&curCol, SCREEN_WIDTH - 1, 0, RIGHT_WIDTH);

	drawRect(oldRow, oldCol, RIGHT_HEIGHT, RIGHT_WIDTH, BGCOLOR);

	if (facing == 0)
		drawImage3(curRow, curCol, LEFT_HEIGHT, LEFT_WIDTH, left);
	else if (facing == 1)
		drawImage3(curRow, curCol, RIGHT_HEIGHT, RIGHT_WIDTH, right);
}*/

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
				if (KEY_DOWN_NOW(BUTTON_START))
				{
					fillScreen(BGCOLOR);

					//curRow = (SCREEN_HEIGHT / 2) - (RIGHT_HEIGHT / 2);
					//curCol = (SCREEN_WIDTH / 2) - (RIGHT_WIDTH / 2);

					drawImage3(player.curRow, player.curCol, RIGHT_HEIGHT, RIGHT_WIDTH, right);
					//facing = 1;
					engine.state = 1;

					drawImage3(0, 0, BURGER_HEIGHT, BURGER_WIDTH, burger);
					drawImage3(0, 25, PIZZA_HEIGHT, PIZZA_WIDTH, pizza);
					drawImage3(0, 50, CHICKEN_HEIGHT, CHICKEN_WIDTH, chicken);
					drawImage3(0, 75, CAKE_HEIGHT, CAKE_WIDTH, cake);
					drawImage3(0, 100, DONUT_HEIGHT, DONUT_WIDTH, donut);
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
