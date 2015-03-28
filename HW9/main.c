#include "myLib.h"
#include "text.h"
#include <stdio.h>
#include <stdlib.h>

#define NUMOBJS 7

typedef struct {

	int row;
	int col;
	int rd;
	int cd;
	int size;
	u16 color;
} MOVOBJ;

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	char buffer[41];
	int i;
	int dels[] = {-3, -2, -1, 1, 2, 3};
	int numdels = sizeof(dels)/sizeof(dels[0]);
	u16 colors[] = {RED, GREEN, BLUE, MAGENTA, CYAN, YELLOW, WHITE};
	int numcolors = sizeof(colors)/sizeof(colors[0]);
	MOVOBJ objs[NUMOBJS];
	MOVOBJ oldobjs[NUMOBJS];
	MOVOBJ *cur;
	for(i=0; i<NUMOBJS; i++)
	{
		objs[i].row = 70 +  rand()% 20;
		objs[i].col = 110 + rand()%20;
		objs[i].rd = dels[rand()%numdels];
		objs[i].cd = dels[rand()%numdels];
		objs[i].color = colors[i%numcolors];
		oldobjs[i] = objs[i];
	}
	int size = 5;
	int oldsize = size;
	int score = 0;
	/*
	int r,c;
	int ch = 0;
	for(r=0; r<16;r++)
	{
		for(c=0; c<16; c++)
		{
			drawChar(r*9, c*9, ch++, YELLOW);
		}
	}
	while(1);
	*/
	u16 bgcolor = LTGRAY;
	DMA[3].src = &bgcolor;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 38400 | DMA_ON | DMA_SOURCE_FIXED;
	
	while(1) // Game Loop
	{
		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			size++;
			if(size>150)
				size=150;
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			size--;
			if(size<3)
				size=3;
		}
		for(i=0; i<NUMOBJS; i++)
		{
			//cur = &objs[i];
			cur = objs + i;

			cur->row = cur->row + cur->rd;
			cur->col = cur->col + cur->cd;
			
			if(boundsCheck(&cur->row, 149, &cur->rd, size))
			{
				score++;
			}
			boundsCheck(&cur->col, 239, &cur->cd, size);
			sprintf(buffer, "Score: %d", score);
		} // for
			WaitForVblank();
		for(i=0; i<NUMOBJS; i++)
		{
		
			drawRect(oldobjs[i].row, oldobjs[i].col, oldsize, oldsize, bgcolor);
		}
		for(i=0; i<NUMOBJS;i++)
		{
			cur = objs + i;
			drawRect(cur->row, cur->col, size, size, cur->color);
			oldobjs[i] = objs[i];
			drawRect(150, 41, 10, 36, bgcolor);
			drawString(150, 5, buffer, YELLOW);
		} // for
		oldsize = size;
	} // while gameloop
}
