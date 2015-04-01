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
#define MAX_BROCCOLI 4

/*Food foods[MAX_FOOD];
Broccoli broccolis[MAX_BROCCOLI];
int curFoodIndex;
int broccoliCount;*/

/**
 * Initializes/reinitializes the game to title screen
 */
/*void init(Engine *e)
{
	drawImage3(0, 0, TITLE_HEIGHT, TITLE_WIDTH, title);
	e->state = 0;
	e->level = 0;
	e->score = 0;
	e->timer = 0;
}*/

/*void startLevel(Engine *e, Player *p)
{
	fillScreen(BGCOLOR);

	e->state = 1;
	e->level++;
	e->totalFood = 0;
	e->curFood = 0;

	p->curRow = (SCREEN_HEIGHT / 2) - (RIGHT_HEIGHT / 2);
	p->curCol = (SCREEN_WIDTH / 2) - (RIGHT_WIDTH / 2);
	p->facing = 1;

	for (curFoodIndex = 0; curFoodIndex < 5; curFoodIndex++)
		addFood(e, p, foods, curFoodIndex, broccolis);

	if (e->level <= MAX_BROCCOLI)
		addBroccoli(e, p, broccolis);
	else
		addBroccoli(e, p, broccolis);

	drawImage3(p->curRow, p->curCol, RIGHT_HEIGHT, RIGHT_WIDTH, right);

	//e->timer = 0;
	while (e->timer < 300) //Wait 300 VBlanks before starting
	{
		WaitForVblank();
		e->timer++;
	}
	e->timer = 0;*/
//}

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	//Engine engine;
	//Player player;
	//char scoreBuffer[11];
	//init(&engine);

	while (1) //Game loop
	{
		WaitForVblank();

		//DELETE
		drawImagePart(100, 100, 45, 50, LEFT_HEIGHT, LEFT_WIDTH, left);
		/* DMA Flags
		DMA_SOURCE_INCREMENT and DMA_SOURCE_INCREMENT are default. They draw
		images normally.
		DMA_SOURCE_FIXED fixes the source so that all the drawn pixels are
		the same.
		DMA_DESTINATION_FIXED fixes the destination so that the same 
		destination pixels are repeatedly rewritten.
		DMA_SOURCE_DECREMENT and DMA_DESTINATION_DECREMENT horizontally 
		flips the image.
		*/
		/* DMA_32
		By default, DMA on the Gameboy does so in 16-bit increments. Using 
		the DMA_32 flag makes it copy in 32-bit increments, or twice as much.

		So basically, it's a matter of being able to optimize the DMA as it 
		copies the data? 
		Pretty much. It's also useful in some very specific
		situations like in the 3rd part of Monday's lab where you're copying 
		two pixel values at once. It is twice as fast as DMA_16 but keep in 
		mind it can (of course) only copy an even number of shorts in a copy, 
		so it's not always applicable to optimizing other DMAs.

		But then the 'count' or number of transfers, is actually the number 
		of 32-bit transfers? instead of 16 bit transfers? So the DMA needs to 
		do half the number of processes to accomplish the task?
		Yes.
		*/

		/*if (KEY_DOWN_NOW(BUTTON_SELECT))
		{
			init(&engine);
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

				//Check for Food collisions and if Food is still on the screen
				int isEmpty = 1;
				for (int i = 0; i < 5 * engine.level; i++)
				{
					if (foods[i].isEaten == 0)
					{
						checkCollidePF(&engine, &player, &foods[i]);

						//for (int j = 0; j < engine.level; j++)
						//	checkCollideFB(&engine, &foods[i], &broccolis[j]);

						isEmpty = 0;
					}
				}

				//If no food is left, go to state 2
				if (isEmpty == 1)
					engine.state = 2;

				//Broccoli movement and collisions
				for (int i = 0; i < engine.level; i++)
				{
					broccolis[i].oldRow = broccolis[i].curRow;
					broccolis[i].oldCol = broccolis[i].curCol;
					moveBroccoli(&broccolis[i]);

					if (checkCollidePB(&engine, &player, &broccolis[i]))
						engine.state = 3;

					checkCollideFB(&engine, foods, &broccolis[i]);
				}

				//Check for Broccoli-Broccoli collisions
				if (engine.level > 1)
					checkCollideBB(&engine, broccolis);
					

				//Periodically add more food if there are less than 5 on
				//screen and less than 5 * level have appeared in total
				if (engine.timer > 50 && engine.curFood < 5 && engine.totalFood < 5 * engine.level)
				{
					addFood(&engine, &player, foods, curFoodIndex, broccolis);
					curFoodIndex++;
					engine.timer = 0;
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
		}*/
	} // while gameloop
}
