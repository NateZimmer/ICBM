

#include "touch.h"
#include "../usi.h"


static uint16_t x_touch_value =0;
static uint16_t y_touch_value =0;

void TOUCH_SETUP()
{
	_delay_cycles(1000000);
	////////////////////

	TOUCH_CS_SETUP |= TOUCH_CS;
	TOUCH_CS_PORT |= TOUCH_CS;
}

uint16_t TOUCH_X()
{
	uint16_t xval =0;
	writeReadByte(GET_X);
	xval = (writeReadByte(0x0)<<8);
	xval += writeReadByte(0x0);
	xval >>= 0x3;
	xval &=0xFFF;
	return xval;
}

uint16_t TOUCH_Y()
{
	uint16_t yval =0;
	writeReadByte(GET_Y);
	yval = (writeReadByte(0x0)<<8);
	yval += writeReadByte(0x0);
	yval >>= 0x3;
	yval &=0xFFF;


	return yval;
}

void run_touch_task()
{

	uint16_t yvals = 0;
	uint16_t xvals = 0;

	SLOW_SPI; // Down Clock

	TOUCH_CS_PORT &=~(TOUCH_CS);
	_delay_cycles(1000);
	yvals = TOUCH_Y();
	_delay_cycles(1000);
	xvals = TOUCH_X();

	TOUCH_CS_PORT |=(TOUCH_CS);


	if(!((xvals <500) || (yvals >4000)))
	{
		if(xvals>500)
			xvals -=500;
		else
			xvals=0;
		xvals /=17;
		if(yvals>400)
			yvals-=400;
		else
			yvals=0;
		yvals /=14;

		//*xval = yvals;
		//*yval = 176 - xvals;

		x_touch_value = yvals;
		y_touch_value = 176 - xvals;


	}
	else
	{
		x_touch_value =0;
		y_touch_value =0;
	}
	FAST_SPI; //Max

}

void TOUCH_VAL(uint16_t * xval, uint16_t * yval)
{
	*xval = x_touch_value;
	*yval = y_touch_value;
}



