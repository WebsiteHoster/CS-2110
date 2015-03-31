/**
 * Jesse Chen
 */

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct
{
	int state;
	int timer;
	int foodCount;
} Engine;

typedef struct
{
 	int curRow;
 	int curCol;
 	int oldRow;
 	int oldCol;
 	int facing;
} Player;

typedef enum { BURGER, PIZZA, CHICKEN, CAKE, DONUT } Food_t;
//typedef enum { BURGER, PIZZA, CHICKEN, CAKE, DONUT, PLAYER, BROCCOLI } Collideable_t;

typedef struct
{
	Food_t type;
	int isEaten;
	int row;
 	int col;
} Food;

typedef struct
{
	int curRow;
 	int curCol;
 	int oldRow;
 	int oldCol;
 	int deltaRow;
 	int deltaCol;
} Broccoli;

void movePlayer(Player *p, int dir);
void moveBroccoli(Broccoli *b);
//void checkCollision(Collideable_t c1, Collideable_t c2);
void addFood(Engine *e);
void checkEat(Engine *e, Player *p, Food *f);
void eatFood(Engine *e, Food *f, int height, int width);

#endif
