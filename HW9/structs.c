/**
 * Jesse Chen
 */

#include "structs.h"
#include "myLib.h"
#include <stdlib.h>

#include "player.h"
#include "food.h"
#include "broccoli.h"

/**
 * Adds a random Food to the foods[] array at a random location.
 *
 * @param *e 			The game Engine
 * @param *p 			The Player
 * @param foods[] 		Food array containing all the game's Food
 * @param i 			Index of foods[] at which to add new Food
 * @param broccolis[] 	Broccoli array containing all the game's Broccoli
 */
void addFood(Engine *e, Player *p, Food foods[], int i, Broccoli broccolis[])
{
	Food_t foodTypes[5] = {BURGER, PIZZA, CHICKEN, CAKE, DONUT};

	foods[i].type = foodTypes[rand() % 5];
	foods[i].isEaten = 0;

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

	//do
	//{
		foods[i].row = (BROCCOLI_HEIGHT + 1) + rand() % (SCREEN_HEIGHT - 2 * (BROCCOLI_HEIGHT + 1) - height);
		foods[i].col = (BROCCOLI_WIDTH + 1) + rand() % (SCREEN_WIDTH - 2 * (BROCCOLI_WIDTH + 1) - width);
	//} while (checkCollidePF() && checkCollideFB());
	

	drawImage3(foods[i].row, foods[i].col, height, width, image);

	e->curFood++;
	e->totalFood++;
}

/**
 * Add up to 4 Broccoli depending on current level. One per level up to level 4.
 *
 * @param *e 			The game Engine
 * @param *p 			The Player
 * @param broccolis[] 	Broccoli array containing all the game's Broccoli
 */
void addBroccoli(Engine *e, Player *p, Broccoli broccolis[])
{
	if (e->level >= 4)
	{
		broccolis[3].curRow = SCREEN_HEIGHT - BROCCOLI_HEIGHT;
		broccolis[3].curCol = 0;
		broccolis[3].deltaRow = -1;
		broccolis[3].deltaCol = 1;
		drawImage3(broccolis[3].curRow, broccolis[3].curCol, 
			BROCCOLI_HEIGHT, BROCCOLI_WIDTH, broccoli);
	}
	if (e->level >= 3)
	{
		broccolis[2].curRow = SCREEN_HEIGHT - BROCCOLI_HEIGHT;
		broccolis[2].curCol = SCREEN_WIDTH - BROCCOLI_WIDTH;
		broccolis[2].deltaRow = -1;
		broccolis[2].deltaCol = -1;
		drawImage3(broccolis[2].curRow, broccolis[2].curCol, 
			BROCCOLI_HEIGHT, BROCCOLI_WIDTH, broccoli);
	}
	if (e->level >= 2)
	{
		broccolis[1].curRow = 0;
		broccolis[1].curCol = SCREEN_WIDTH - BROCCOLI_WIDTH;
		broccolis[1].deltaRow = 1;
		broccolis[1].deltaCol = -1;
		drawImage3(broccolis[1].curRow, broccolis[1].curCol, 
			BROCCOLI_HEIGHT, BROCCOLI_WIDTH, broccoli);
	}
	if (e->level >= 1)
	{
		broccolis[0].curRow = 0;
		broccolis[0].curCol = 0;
		broccolis[0].deltaRow = 1;
		broccolis[0].deltaCol = 1;
		drawImage3(broccolis[0].curRow, broccolis[0].curCol, 
			BROCCOLI_HEIGHT, BROCCOLI_WIDTH, broccoli);
	}
}

/**
 * Checks boundaries and moves player.
 *
 * @param dir Direction the player is facing
 *				0: up
 *				1: down
 *				2: left
 *				3: right
 */
void movePlayer(Player *p, int dir)
{
	switch (dir) //Change row/col position
	{
		case 0:
			p->curRow -= 2;
		break;
		case 1:
			p->curRow += 2;
		break;
		case 2:
			p->curCol -= 2;
			p->facing = 0;
		break;
		case 3:
			p->curCol += 2;
			p->facing = 1;
		break;
	}

	boundsCheck(&p->curRow, SCREEN_HEIGHT - 1, 0, RIGHT_HEIGHT);
	boundsCheck(&p->curCol, SCREEN_WIDTH - 1, 0, RIGHT_WIDTH);

	drawRect(p->oldRow, p->oldCol, RIGHT_HEIGHT, RIGHT_WIDTH, BGCOLOR);

	if (p->facing == 0)
		drawImage3(p->curRow, p->curCol, LEFT_HEIGHT, LEFT_WIDTH, left);
	else if (p->facing == 1)
		drawImage3(p->curRow, p->curCol, RIGHT_HEIGHT, RIGHT_WIDTH, right);
}

/**
 * Moves a Broccoli.
 *
 * @param *b The Broccoli to be moved
 */
void moveBroccoli(Broccoli *b)
{
	b->curRow += b->deltaRow;
	b->curCol += b->deltaCol;

	boundsCheck(&b->curRow, SCREEN_HEIGHT - 1, &b->deltaRow, BROCCOLI_HEIGHT);
	boundsCheck(&b->curCol, SCREEN_WIDTH - 1, &b->deltaCol, BROCCOLI_WIDTH);

	drawRect(b->oldRow, b->oldCol, BROCCOLI_HEIGHT, BROCCOLI_WIDTH, BGCOLOR);
	drawImage3(b->curRow, b->curCol, BROCCOLI_HEIGHT, BROCCOLI_WIDTH, broccoli);
}

/**
 * Checks for collisions between two arbitrary Collideable game objects.
 *
 * @param c1 Object 1
 * @param c2 Object 2
 * @return 1 (true) if collision detected, or 0 (false) if no collision detected
 */
int checkCollision(Collideable c1, Collideable c2)
{
	if (c1.row < (c2.row + c2.height) && (c1.col + c1.width) > c2.col &&
		(c1.row + c1.height) > c2.row && c1.col < (c2.col + c2.width))
		return 1;
	else
		return 0;
}

/**
 * Checks collisions between the Player and a Food. If collision detected, also
 * eat the Food.
 *
 * @param *e The game Engine
 * @param *p The Player
 * @param *f The Food
 * @return 1 (true) if collision detected, or 0 (false) if no collision detected
 */
int checkCollidePF(Engine *e, Player *p, Food *f)
{
	Food_t type = f->type;
	int fHeight, fWidth;

	switch (type) //Determine Food type
	{
		case BURGER:
			fHeight = BURGER_HEIGHT;
			fWidth = BURGER_WIDTH;
		break;
		case PIZZA:
			fHeight = PIZZA_HEIGHT;
			fWidth = PIZZA_WIDTH;
		break;
		case CHICKEN:
			fHeight = CHICKEN_HEIGHT;
			fWidth = CHICKEN_WIDTH;
		break;
		case CAKE:
			fHeight = CAKE_HEIGHT;
			fWidth = CAKE_WIDTH;
		break;
		case DONUT:
			fHeight = DONUT_HEIGHT;
			fWidth = DONUT_WIDTH;
		break;
		default:
			fHeight = 25;
			fWidth = 25;
		break;
	}
	
	Collideable player, food; //Make Food and Broccoli comparable

	player.row = p->curRow;
	player.col = p->curCol;
	player.height = RIGHT_HEIGHT;
	player.width = RIGHT_WIDTH;

	food.row = f->row;
	food.col = f->col;
	food.height = fHeight;
	food.width = fWidth;
	
	if(checkCollision(player, food)) //Check if current Food and Broccoli collide
	{
		eatFood(e, f, fHeight, fWidth);
		return 1;
	}
	else
		return 0;
}

/**
 * Checks collisions between the Player and a Broccoli.
 *
 * @param *e The game Engine
 * @param *p The Player
 * @param *b The Broccoli
 * @return 1 (true) if collision detected, or 0 (false) if no collision detected
 */
int checkCollidePB(Engine *e, Player *p, Broccoli *b)
{
	Collideable player, broccoli; //Make Food and Broccoli comparable

	player.row = p->curRow;
	player.col = p->curCol;
	player.height = RIGHT_HEIGHT;
	player.width = RIGHT_WIDTH;

	broccoli.row = b->curRow;
	broccoli.col = b->curCol;
	broccoli.height = BROCCOLI_HEIGHT;
	broccoli.width = BROCCOLI_WIDTH;

	if(checkCollision(player, broccoli)) //Check if Player and Broccoli collide
		return 1;
	else
		return 0;
}

/**
 * Checks collisions between all Food and a Broccoli. 
 *
 * @param *e 		The game Engine
 * @param foods[] 	Food array containing all the game's Food
 * @param *b 		The Broccoli
 * @return 			1 (true) if any collisions detected, or 0 (false) if no
 *					collisions detected
 */
int checkCollideFB(Engine *e, Food foods[], Broccoli *b)
{
	int flag = 0; //Return flag for result
	
	for (int i = 0; i < e->totalFood; i++) //Iterate through all existing Food
	{
		if (foods[i].isEaten == 0) //If Food is not eaten
		{
			Food_t type = foods[i].type;
			int fHeight, fWidth;

			switch (type) //Determine Food type
			{
				case BURGER:
					fHeight = BURGER_HEIGHT;
					fWidth = BURGER_WIDTH;
				break;
				case PIZZA:
					fHeight = PIZZA_HEIGHT;
					fWidth = PIZZA_WIDTH;
				break;
				case CHICKEN:
					fHeight = CHICKEN_HEIGHT;
					fWidth = CHICKEN_WIDTH;
				break;
				case CAKE:
					fHeight = CAKE_HEIGHT;
					fWidth = CAKE_WIDTH;
				break;
				case DONUT:
					fHeight = DONUT_HEIGHT;
					fWidth = DONUT_WIDTH;
				break;
				default:
					fHeight = 25;
					fWidth = 25;
				break;
			}

			Collideable food, broccoli; //Make Food and Broccoli comparable

			food.row = foods[i].row;
			food.col = foods[i].col;
			food.height = fHeight;
			food.width = fWidth;

			broccoli.row = b->curRow;
			broccoli.col = b->curCol;
			broccoli.height = BROCCOLI_HEIGHT;
			broccoli.width = BROCCOLI_WIDTH;

			if(checkCollision(food, broccoli)) //Check if current Food and Broccoli collide
			{
				b->deltaRow *= -1;
				b->deltaCol *= -1;

				flag = 1; //If there is at least one collision, then this Broccoli has collided 
			}
		}
	}

	return flag;
}

/**
 * Checks collisions between all indistinct pairs of Broccoli.
 *
 * @param *e 			The game Engine
 * @param broccolis[] 	Broccoli array containing all the game's Broccoli
 * @return 				1 (true) if any collisions detected, or 0 (false) if no
 *						collisions detected
 */
int checkCollideBB(Engine *e, Broccoli broccolis[])
{
	Collideable b1, b2; //Make Broccolis comparable
	int flag = 0; //Return flag for result
	int n = e->level; //Set number of Broccolis equal to current level

	//Iterate through all indistinct pairs of Broccoli
	if (n >= 4) //(0, 3), (1, 3), (2, 3)
	{
		//(0, 3)
		b1.row = broccolis[0].curRow;
		b1.col = broccolis[0].curCol;
		b1.height = BROCCOLI_HEIGHT;
		b1.width = BROCCOLI_WIDTH;

		b2.row = broccolis[3].curRow;
		b2.col = broccolis[3].curCol;
		b2.height = BROCCOLI_HEIGHT;
		b2.width = BROCCOLI_WIDTH;

		if(checkCollision(b1, b2)) //Check if Broccolis collide
		{
			broccolis[0].deltaRow *= -1;
			broccolis[0].deltaCol *= -1;
			broccolis[3].deltaRow *= -1;
			broccolis[3].deltaCol *= -1;

			flag = 1; //If there is at least one collision, then this Broccoli has collided
		}

		//(1, 3)
		b1.row = broccolis[1].curRow;
		b1.col = broccolis[1].curCol;
		b1.height = BROCCOLI_HEIGHT;
		b1.width = BROCCOLI_WIDTH;

		b2.row = broccolis[3].curRow;
		b2.col = broccolis[3].curCol;
		b2.height = BROCCOLI_HEIGHT;
		b2.width = BROCCOLI_WIDTH;

		if(checkCollision(b1, b2))
		{
			broccolis[1].deltaRow *= -1;
			broccolis[1].deltaCol *= -1;
			broccolis[3].deltaRow *= -1;
			broccolis[3].deltaCol *= -1;

			flag = 1;
		}

		//(2, 3)
		b1.row = broccolis[2].curRow;
		b1.col = broccolis[2].curCol;
		b1.height = BROCCOLI_HEIGHT;
		b1.width = BROCCOLI_WIDTH;

		b2.row = broccolis[3].curRow;
		b2.col = broccolis[3].curCol;
		b2.height = BROCCOLI_HEIGHT;
		b2.width = BROCCOLI_WIDTH;

		if(checkCollision(b1, b2))
		{
			broccolis[2].deltaRow *= -1;
			broccolis[2].deltaCol *= -1;
			broccolis[3].deltaRow *= -1;
			broccolis[3].deltaCol *= -1;

			flag = 1;
		}
	}
	if (n >= 3) //(0, 2), (1, 2)
	{
		//(0, 2)
		b1.row = broccolis[0].curRow;
		b1.col = broccolis[0].curCol;
		b1.height = BROCCOLI_HEIGHT;
		b1.width = BROCCOLI_WIDTH;

		b2.row = broccolis[2].curRow;
		b2.col = broccolis[2].curCol;
		b2.height = BROCCOLI_HEIGHT;
		b2.width = BROCCOLI_WIDTH;

		if(checkCollision(b1, b2))
		{
			broccolis[0].deltaRow *= -1;
			broccolis[0].deltaCol *= -1;
			broccolis[2].deltaRow *= -1;
			broccolis[2].deltaCol *= -1;

			flag = 1;
		}

		//(1, 2)
		b1.row = broccolis[1].curRow;
		b1.col = broccolis[1].curCol;
		b1.height = BROCCOLI_HEIGHT;
		b1.width = BROCCOLI_WIDTH;

		b2.row = broccolis[2].curRow;
		b2.col = broccolis[2].curCol;
		b2.height = BROCCOLI_HEIGHT;
		b2.width = BROCCOLI_WIDTH;

		if(checkCollision(b1, b2))
		{
			broccolis[1].deltaRow *= -1;
			broccolis[1].deltaCol *= -1;
			broccolis[2].deltaRow *= -1;
			broccolis[2].deltaCol *= -1;

			flag = 1;
		}
	}
	if (n >= 2) //(0, 1)
	{
		b1.row = broccolis[0].curRow;
		b1.col = broccolis[0].curCol;
		b1.height = BROCCOLI_HEIGHT;
		b1.width = BROCCOLI_WIDTH;

		b2.row = broccolis[1].curRow;
		b2.col = broccolis[1].curCol;
		b2.height = BROCCOLI_HEIGHT;
		b2.width = BROCCOLI_WIDTH;

		if(checkCollision(b1, b2))
		{
			broccolis[0].deltaRow *= -1;
			broccolis[0].deltaCol *= -1;
			broccolis[1].deltaRow *= -1;
			broccolis[1].deltaCol *= -1;

			flag = 1;
		}
	}

	return flag;
}

/**
 * Eats a Food.
 *
 * @param *e 		The game Engine
 * @param *f 		The Food
 * @param height 	The image height of *f
 * @param width 	The image width of *f
 */
void eatFood(Engine *e, Food *f, int height, int width)
{
	e->curFood--;
	e->score++;
	f->isEaten = 1;
	drawRect(f->row, f->col, height, width, BGCOLOR);
}
