/*
 * pwm.h
 *
 *  Created on: Jun 8, 2014
 *      Author: Nate
 */

#ifndef PWM_H_
#define PWM_H_

#include "msp430g2553.h"
#include "stdint.h"
#include "stdbool.h"

typedef enum
{
	TIMER0,
	TIMER1
}TIMER_SELECT;


typedef enum
{
	TACLK,
	ACLK,
	SMCLK,
	INCLK
//#define TASSEL_0               (0*0x100u)     /* Timer A clock source select: 0 - TACLK */
//#define TASSEL_1               (1*0x100u)     /* Timer A clock source select: 1 - ACLK  */
//#define TASSEL_2               (2*0x100u)     /* Timer A clock source select: 2 - SMCLK */
//#define TASSEL_3               (3*0x100u)     /* Timer A clock source select: 3 - INCLK */
}PWM_CLK_SELECT;

typedef enum
{
//#define MC_0                   (0*0x10u)      /* Timer A mode control: 0 - Stop */
//#define MC_1                   (1*0x10u)      /* Timer A mode control: 1 - Up to CCR0 */
//#define MC_2                   (2*0x10u)      /* Timer A mode control: 2 - Continous up */
//#define MC_3                   (3*0x10u)      /* Timer A mode control: 3 - Up/Down */
	STOP,
	UP_TO_CCR0,
	CONTINOUS_UP,
	UP_DOWN
}PWM_COUNT_MODE;

typedef enum
{
//#define ID_0                   (0*0x40u)      /* Timer A input divider: 0 - /1 */
//#define ID_1                   (1*0x40u)      /* Timer A input divider: 1 - /2 */
//#define ID_2                   (2*0x40u)      /* Timer A input divider: 2 - /4 */
//#define ID_3                   (3*0x40u)      /* Timer A input divider: 3 - /8 */
	ONE_DIVIDER = 0,
	TWO_DIVIDER = 1,
	FOUR_DIVIDER = 2,
	EIGHT_DIVIDER = 3
}PWM_DIVIDER;

typedef enum
{
	P1x2_TA0x1 = 0,
	P1x6_TA0x1 = 1,
	P2x1_TA1x1 = 2,
	P2x2_TA1x1 = 3,
	P2x4_TA1x2 = 4,
	P2x5_TA1x2 = 5
}PWM_PINS;

void timerSetup(TIMER_SELECT TIMER, uint16_t timerValue,PWM_CLK_SELECT PWM_CLK,PWM_COUNT_MODE PWM_MODE, PWM_DIVIDER PWM_DIVIDE, bool ISR_ENABLED );
void channelPwmSetup(PWM_PINS PWM_PIN,uint16_t timerValue);


//AT+PWM,[PIN],[Freq/CCR0],[Duty],[Divider]
//AT+PWM,1,60000,60000,1

#endif /* PWM_H_ */
