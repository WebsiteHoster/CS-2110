#include "myLib.h"
#include "text.h"
#include <stdio.h>
#include <stdlib.h>

#include "title.h"
#include "player.h"
/*#include "up.h"
#include "down.h"
#include "left.h"
#include "right.h"*/

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

void init()
{
	drawImage3(0, 0, TITLE_HEIGHT, TITLE_WIDTH, title);
	state = 0;
	curRow = (SCREEN_HEIGHT / 2) - (UP_HEIGHT / 2);
	curCol = (SCREEN_WIDTH / 2) - (UP_WIDTH / 2);
}

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	init();

	while (1) // Game Loop
	{
		WaitForVblank();

		if (KEY_DOWN_NOW(BUTTON_SELECT))
		{
			init();
		}

		switch (state)
		{
			case 0:
				if (KEY_DOWN_NOW(BUTTON_START))
				{
					fillScreen(BGCOLOR);
					state = 1;
				}
			break;
			case 1:
				oldRow = curRow;
				oldCol = curCol;

				if (KEY_DOWN_NOW(BUTTON_UP))
				{
					curRow--;
				}
				else if (KEY_DOWN_NOW(BUTTON_DOWN))
				{
					curRow++;
				}
				else if (KEY_DOWN_NOW(BUTTON_LEFT))
				{
					curCol--;
				}
				else if (KEY_DOWN_NOW(BUTTON_RIGHT))
				{
					curCol++;
				}
				
				boundsCheck(&curRow, SCREEN_HEIGHT - 1, 0, UP_HEIGHT);
				boundsCheck(&curCol, SCREEN_WIDTH - 1, 0, UP_WIDTH);

				//drawRect(oldRow, oldCol, 10, 10, BLACK);
				//drawRect(curRow, curCol, 10, 10, RED);
				
				if (KEY_DOWN_NOW(BUTTON_UP))
				{
					drawRect(oldRow, oldCol, UP_HEIGHT, UP_WIDTH, BGCOLOR);
					drawImage3(curRow, curCol, UP_HEIGHT, UP_WIDTH, up);
				}
				else if (KEY_DOWN_NOW(BUTTON_DOWN))
				{
					drawRect(oldRow, oldCol, UP_HEIGHT, UP_WIDTH, BGCOLOR);
					drawImage3(curRow, curCol, DOWN_HEIGHT, DOWN_WIDTH, down);
				}
				else if (KEY_DOWN_NOW(BUTTON_LEFT))
				{
					drawRect(oldRow, oldCol, UP_HEIGHT, UP_WIDTH, BGCOLOR);
					drawImage3(curRow, curCol, LEFT_HEIGHT, LEFT_WIDTH, left);
				}
				else if (KEY_DOWN_NOW(BUTTON_RIGHT))
				{
					drawRect(oldRow, oldCol, UP_HEIGHT, UP_WIDTH, BGCOLOR);
					drawImage3(curRow, curCol, RIGHT_HEIGHT, RIGHT_WIDTH, right);
				}

			break;
		}
	} // while gameloop
}
