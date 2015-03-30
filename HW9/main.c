#include "myLib.h"
#include "text.h"
#include <stdio.h>
#include <stdlib.h>

//Include images
#include "title.h"
#include "win.h"
#include "lose.h"
#include "player.h"
#include "burger.h"
#include "pizza.h"
#include "chicken.h"
#include "cake.h"
#include "donut.h"

/*#define NUMOBJS 7

typedef struct {

	int row;
	int col;
	int rd;
	int cd;
	int size;
	u16 color;
} MOVOBJ;*/

int state;
int curRow;
int curCol;
int oldRow, oldCol;

/**
 * Initializes/reinitializes the game to title screen
 */
void init()
{
	drawImage3(0, 0, TITLE_HEIGHT, TITLE_WIDTH, title);
	state = 0;
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
void move(int dir)
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
		break;
		case 3:
			curCol++;
		break;
	}

	boundsCheck(&curRow, SCREEN_HEIGHT - 1, 0, DOWN_HEIGHT);
	boundsCheck(&curCol, SCREEN_WIDTH - 1, 0, DOWN_WIDTH);

	drawRect(oldRow, oldCol, DOWN_HEIGHT, DOWN_WIDTH, BGCOLOR);

	switch (dir) //Move/redraw player
	{
		case 0:
			drawImage3(curRow, curCol, UP_HEIGHT, UP_WIDTH, up);
		break;
		case 1:
			drawImage3(curRow, curCol, DOWN_HEIGHT, DOWN_WIDTH, down);
		break;
		case 2:
			drawImage3(curRow, curCol, LEFT_HEIGHT, LEFT_WIDTH, left);
		break;
		case 3:
			drawImage3(curRow, curCol, RIGHT_HEIGHT, RIGHT_WIDTH, right);
		break;
	}
}

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	init();

	while (1) //Game loop
	{
		WaitForVblank();

		if (KEY_DOWN_NOW(BUTTON_SELECT))
		{
			init();
		}

		switch (state) //Determine game state
		{
			case 0: //Title screen
				if (KEY_DOWN_NOW(BUTTON_START))
				{
					fillScreen(BGCOLOR);

					curRow = (SCREEN_HEIGHT / 2) - (DOWN_HEIGHT / 2);
					curCol = (SCREEN_WIDTH / 2) - (DOWN_WIDTH / 2);

					drawImage3(curRow, curCol, DOWN_HEIGHT, DOWN_WIDTH, down);
					state = 1;

					drawImage3(0, 0, BURGER_HEIGHT, BURGER_WIDTH, burger);
					drawImage3(0, 25, PIZZA_HEIGHT, PIZZA_WIDTH, pizza);
					drawImage3(0, 50, CHICKEN_HEIGHT, CHICKEN_WIDTH, chicken);
					drawImage3(0, 75, CAKE_HEIGHT, CAKE_WIDTH, cake);
					drawImage3(0, 100, DONUT_HEIGHT, DONUT_WIDTH, donut);
				}
			break;
			case 1: //Main gameplay
				oldRow = curRow;
				oldCol = curCol;

				if (KEY_DOWN_NOW(BUTTON_UP))
				{
					//setDir(0);
					move(0);
				}
				else if (KEY_DOWN_NOW(BUTTON_DOWN))
				{
					//setDir(1);
					move(1);
				}
				else if (KEY_DOWN_NOW(BUTTON_LEFT))
				{
					//setDir(2);
					move(2);
				}
				else if (KEY_DOWN_NOW(BUTTON_RIGHT))
				{
					//setDir(3);
					move(3);
				}

				if (KEY_DOWN_NOW(BUTTON_A))
				{
					state = 2;
				}
				else if (KEY_DOWN_NOW(BUTTON_B))
				{
					state = 3;
				}
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
