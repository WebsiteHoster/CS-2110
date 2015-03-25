#include "myLib.h"

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	while(1) // game loop
	{
		waitForVblank();
	
		//TODO: SET PIXEL (10,10) TO THE RIGHT COLOR
		
		//TODO: DRAW THE STRING IF A OR B is pressed
		drawString(10, 10, "this is an example!", RED);

	}
}

