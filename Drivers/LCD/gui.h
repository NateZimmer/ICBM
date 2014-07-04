/*
 * gui.h
 *
 *  Created on: Apr 6, 2013
 *      Author: Nate
 */

#ifndef GUI_H_
#define GUI_H_

#include "stdint.h"
#include "colorLCD.h"
#include "touch.h"

typedef struct
{
	uint8_t		xstart;
	uint8_t		ystart;
	uint8_t		yend;
	uint8_t		xend;
	char	 	text[10];
} Text_Button;

typedef struct
{
	uint8_t		xstart;
	uint8_t		ystart;
	char	 	text[10];
} Small_Text_Button;


void Setup_LCD();

typedef enum
{
	Home_Page,
	Reflow_Page,
	Settings_Page,
	Calibration_Page

} Pages;

void Page_Event_Handler();
void update_graph();
void print_oven_data();
void check_timeout();
void Draw_Small_Button(Small_Text_Button *button_handle);
uint8_t Check_Small_Touch(Small_Text_Button *button_handle, uint16_t xval, uint16_t yval);


#endif /* GUI_H_ */
