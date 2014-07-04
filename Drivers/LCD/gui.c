/*
 * gui.c
 *
 *  Created on: Apr 6, 2013
 *      Author: Nate
 */

#include "gui.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

#define y_button_size 		20
#define Touch_Tolerance		5
static uint16_t Small_Button_Color = COLOR_16_RED;


/*
static Text_Button Leaded;
static Text_Button Pb_Free;
static Text_Button Settings;
static Text_Button Start;
static Text_Button Back;
*/


//static Small_Text_Button Set_Temp = {70,90,"Calibrate"};



//static bool mins_selected=false;

//static Pages Current_Page = Home_Page;




void Create_Button(Text_Button * button_handle,uint8_t x_start, uint8_t y_start, char * display_text)
{
	uint8_t i=0;
	button_handle->xstart=x_start;
	button_handle->ystart=y_start;

	while(display_text[i])
	{
		button_handle->text[i]=display_text[i];
		i++;
	}
	button_handle->text[i]=display_text[i];

	button_handle->xend =8*i + x_start;
	button_handle->yend =y_start + y_button_size;

}

uint8_t Check_Small_Touch(Small_Text_Button *button_handle, uint16_t xval, uint16_t yval)
{
	uint8_t xstart = (button_handle->xstart);
	uint8_t ystart = (button_handle->ystart);
	uint8_t xend = 8*strlen(button_handle->text) + xstart;
	uint8_t yend = ystart + y_button_size;

	if(yval+xval)
	{
		if(((xval+Touch_Tolerance)>xstart)&&((yval+Touch_Tolerance)>ystart)&&((xval-Touch_Tolerance)<xend)&&((yval-Touch_Tolerance)<yend))
				return 1;
			else
				return 0;
	}
	else
		return 0;
}


uint8_t Check_Touch(Text_Button *button_handle, uint16_t xval, uint16_t yval)
{
	uint8_t xstart = (button_handle->xstart);
	uint8_t ystart = (button_handle->ystart);
	uint8_t xend = (button_handle->xend);
	uint8_t yend = (button_handle->yend);

	if(yval+xval)
	{
		if(((xval+Touch_Tolerance)>xstart)&&((yval+Touch_Tolerance)>ystart)&&((xval-Touch_Tolerance)<xend)&&((yval-Touch_Tolerance)<yend))
				return 1;
			else
				return 0;
	}
	else
		return 0;
}

/*
void Create_Buttons()
{
	Create_Button(&Leaded,10,60,"Leaded");
	Create_Button(&Pb_Free,110,60,"Pb-Free");
	Create_Button(&Settings,140,150,"Settings");
	Create_Button(&Start,160,150,"Start");
	Create_Button(&Back,70,150,"Back");



}
*/

/*
void Draw_Button(Text_Button *button_handle)
{
	uint16_t bg_color =COLOR_16_RED;
	setColor16(bg_color);
	fillRect(button_handle->xstart, button_handle->ystart,button_handle->xend + 10, button_handle->yend);
	setColor16(COLOR_16_WHITE);
	setBackgroundColor16(bg_color);
	setColor16(COLOR_16_WHITE);
	drawString8_12(button_handle->xstart+5, button_handle->ystart + 5, button_handle->text );
	setBackgroundColor16(COLOR_16_BLACK);

}
*/

void Draw_Small_Button(Small_Text_Button *button_handle)
{
	uint8_t xend = 8*strlen(button_handle->text) + button_handle->xstart;
	uint8_t yend = button_handle->ystart + y_button_size;
	setColor16(Small_Button_Color);
	fillRect(button_handle->xstart, button_handle->ystart,xend + 10, yend);
	setColor16(COLOR_16_WHITE);
	setBackgroundColor16(Small_Button_Color);
	setColor16(COLOR_16_WHITE);
	drawString8_12(button_handle->xstart+5, button_handle->ystart + 5, (char *)(button_handle->text));
	setBackgroundColor16(COLOR_16_BLACK);
}


/*
void Check_Home_Page_Touch(Pages * page_return)
{
	uint16_t xval =0;
	uint16_t yval =0;
	TOUCH_VAL(&xval, &yval);

	if(Check_Touch(&Leaded, xval, yval))
	{
		set_profile_leaded();
		*page_return = Reflow_Page;
		return;
	}
	if(Check_Touch(&Pb_Free, xval, yval))
	{
		set_profile_pb_free();
		*page_return = Reflow_Page;
		return;
	}
	if(Check_Touch(&Settings, xval, yval))
	{

		*page_return = Settings_Page;
		return;
	}

	*page_return = Home_Page;

}
*/


void Setup_LCD()
{
	initILI9225B();
	TOUCH_SETUP();
}


/*
void Page_Event_Handler()
{
	Pages Page_Return;
	switch( Current_Page)
	{

		case Home_Page:
			Check_Home_Page_Touch(&Page_Return);

			if (Page_Return ==Home_Page)
				_delay_cycles(1);
			else if(Page_Return ==Reflow_Page)
			{
				Current_Page =Reflow_Page;
				Draw_Oven_Page();
				_delay_cycles(10000000);
			}
			else if(Page_Return ==Settings_Page)
			{
				Current_Page =Settings_Page;
				Draw_Settings_Page();
				_delay_cycles(10000000);
			}

			break;

		case Reflow_Page:
			Check_Reflow_Page_Touch(&Page_Return);

			if (Page_Return ==Reflow_Page)
				_delay_cycles(1);
			else if(Page_Return ==Home_Page)
			{
				Current_Page =Home_Page;
				Draw_Home_Page();
				_delay_cycles(10000000);
			}

			break;

		case Settings_Page:
			Check_Settings_Page(&Page_Return);
			if (Page_Return ==Home_Page)
			{
				Current_Page =Home_Page;
				Draw_Home_Page();
				_delay_cycles(10000000);
			}
			else if(Page_Return ==Calibration_Page)
			{
				Current_Page = Calibration_Page;
				Draw_Calibration_Page();
				_delay_cycles(10000000);
			}

			break;

		case Calibration_Page:
			Check_Calibration_Page(&Page_Return);
			if(Page_Return == Settings_Page)
			{
				Current_Page = Settings_Page;
				Draw_Settings_Page();
				_delay_cycles(10000000);
			}
			break;


	}

}

*/

