/*
 * =====================================================================================
 *
 *       Filename:  timer.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03.05.19 23:28:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  vovan (), volodumurkoval0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "timer.h"

void Timer2Init(void)
{
	TCCR2A |= (1 << COM2B1); /* Clear OC0B on Compare Match, set OC0B at BOTTOM */
	TCCR2A |= (1 << WGM21) | (1 << WGM20); /* Fast PWM Mode */
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); /* clkio/1024 */
	OCR2B = 25;
}

void Timer0Init(void)
{
	TCCR0A |= (1 << COM0B1); /* Clear OC0B on Compare Match, set OC0B at BOTTOM */
	TCCR0A |= (1 << WGM01) | (1 << WGM00); /* Fast PWM Mode */
	TCCR0B |= (1 << CS02) | (1 << CS01) | (1 << CS00); /* clkio/1024 */
	OCR0B = 25;
}
