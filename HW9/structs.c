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
 * Checks boundaries and moves player
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
			p->curRow--;
		break;
		case 1:
			p->curRow++;
		break;
		case 2:
			p->curCol--;
			p->facing = 0;
		break;
		case 3:
			p->curCol++;
			p->facing = 1;
		break;
	}

	boundsCheck(&p->curRow, SCREEN_HEIGHT - 11, 0, RIGHT_HEIGHT);
	boundsCheck(&p->curCol, SCREEN_WIDTH - 1, 0, RIGHT_WIDTH);

	drawRect(p->oldRow, p->oldCol, RIGHT_HEIGHT, RIGHT_WIDTH, BGCOLOR);

	if (p->facing == 0)
		drawImage3(p->curRow, p->curCol, LEFT_HEIGHT, LEFT_WIDTH, left);
	else if (p->facing == 1)
		drawImage3(p->curRow, p->curCol, RIGHT_HEIGHT, RIGHT_WIDTH, right);
}

void moveBroccoli(Broccoli *b)
{
	b->curRow += b->deltaRow;
	b->curCol += b->deltaCol;

	boundsCheck(&b->curRow, SCREEN_HEIGHT - 1, &b->deltaRow, BROCCOLI_HEIGHT);
	boundsCheck(&b->curCol, SCREEN_WIDTH - 1, &b->deltaCol, BROCCOLI_WIDTH);

	drawRect(b->oldRow, b->oldCol, BROCCOLI_HEIGHT, BROCCOLI_WIDTH, BGCOLOR);
	drawImage3(b->curRow, b->curCol, BROCCOLI_HEIGHT, BROCCOLI_WIDTH, broccoli);

	/*if (p->curRow < (f->row + fHeight) || (p->curCol + pWidth) > f->col
		(p->curRow + pHeight) > f->row) || p->curCol < (f->col + fWidth)
	{
		eatFood(*e, *f, fHeight, fWidth);
	}*/
}

/*void checkCollision(Collideable_t c1, Collideable_t c2)
{

}*/

void addFood(Engine *e, Food foods[], int i)
{
	Food_t foodTypes[5] = {BURGER, PIZZA, CHICKEN, CAKE, DONUT};

	foods[i].type = foodTypes[rand() % 5];
	foods[i].isEaten = 0;
	foods[i].row = rand() % 125;
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

	e->curFood++;
	e->totalFood++;
}

void checkCollideFood(Engine *e, Player *p, Food *f)
{
	Food_t type = f->type;
	int pHeight = RIGHT_HEIGHT;
	int pWidth = RIGHT_WIDTH;
	int fHeight, fWidth;

	switch (type)
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

	if (p->curRow < (f->row + fHeight) && (p->curCol + pWidth) > f->col &&
		(p->curRow + pHeight) > f->row && p->curCol < (f->col + fWidth))
	{
		eatFood(e, f, fHeight, fWidth);
	}
}

void eatFood(Engine *e, Food *f, int height, int width)
{
	e->curFood--;
	e->score++;
	f->isEaten = 1;
	drawRect(f->row, f->col, height, width, BGCOLOR);
}
