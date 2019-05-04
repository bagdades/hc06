#ifndef  MAIN_INC
#define  MAIN_INC

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>
#include <util/delay.h>
#include "usart.h"
#include "parser.h"
#include "timer.h"

#define _DEBUG

#define LED_PORT		PORTB
#define LED_DDR			DDRB
#define LED				PB5
#define LED_PIN			PINB

#define MOT1_PORT		PORTD
#define MOT1_DDR		DDRD
#define MOT1_PIN		PIND
#define MOT1_IN1		PD4
#define MOT1_IN2		PD5
#define MOT1_EN			PD3

#define MOT2_PORT		PORTB
#define MOT2_DDR		DDRB
#define MOT2_PIN		PINB
#define MOT2_IN1		PB0
#define MOT2_IN2		PB1
#define MOT2_EN			PB2

#endif   /* ----- #ifndef MAIN_INC  ----- */
