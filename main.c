/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02.05.19 20:08:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  vovan (), volodumurkoval0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "main.h"

void Init(void)
{
	/* Led Port Init */
	LED_DDR |= (1 << LED);
	LED_PORT &= ~(1 << LED);
	/* Motor 1 Port Init */
	MOT1_DDR |= (1 << MOT1_IN1) | (1 << MOT1_IN2) | (1 << MOT1_EN) | (1 << MOT2_EN);
	MOT1_PORT &= ~((1 << MOT1_IN1) | (1 << MOT1_IN2) | (1 << MOT1_EN));
	/* Motor 2 Port Init */
	MOT2_DDR |= (1 << MOT2_IN1) | (1 << MOT2_IN2);
	MOT2_PORT &= ~((1 << MOT2_IN1) | (1 << MOT2_IN2));
}


void ListenUsart(void)
{
	uint8_t symbol;
	if (UsartGetRxCount()) {
		symbol = UsartGetChar();
		ParserParse(symbol);
	}
}

void Motor1Stop(void)
{
	MOT1_PORT &= ~((1 << MOT1_IN1) | (1 << MOT1_IN2));
	MOT1_PORT &= ~(1 << MOT1_EN);
}

void Motor2Stop(void)
{
	MOT2_PORT &= ~((1 << MOT2_IN1) | (1 << MOT2_IN2));
	MOT2_PORT &= ~(1 << MOT2_EN);
}

void Motro1Blocking(void)
{
	MOT1_PORT |= (1 << MOT1_IN1) | (1 << MOT1_IN2);
}

void Motro2Blocking(void)
{
	MOT2_PORT |= (1 << MOT2_IN1) | (1 << MOT2_IN2);
}

void Motor1Forward(void)
{
	MOT1_PORT |= (1 << MOT1_IN1);
	MOT1_PORT &= ~(1 << MOT1_IN2);
	MOT1_PORT |= (1 << MOT1_EN);
}

void Motor2Forward(void)
{
	MOT2_PORT |= (1 << MOT2_IN1);
	MOT2_PORT &= ~(1 << MOT2_IN2);
	MOT2_PORT |= (1 << MOT2_EN);
}

void Motor1Revers(void)
{
	MOT1_PORT &= ~(1 << MOT1_IN1);
	MOT1_PORT |= (1 << MOT1_IN2);
	MOT1_PORT |= (1 << MOT1_EN);
}

void Motor2Revers(void)
{
	MOT2_PORT &= ~(1 << MOT2_IN1);
	MOT2_PORT |= (1 << MOT2_IN2);
	MOT2_PORT |= (1 << MOT2_EN);
}

void ParserHandler(uint8_t argc, char *argv[])
{
	uint8_t resp = 'E';
	static uint8_t outPutCompare2 = 250;
	if(ParserEqualString(argv[0], "Stop1")) {
		resp = 's';
	}
	else if (ParserEqualString(argv[0], "Stop2")) 
	{
		resp = 'e';
	}
	else if (ParserEqualString(argv[0], "Forw")) 
	{
		resp = 'F';
	}
	else if (ParserEqualString(argv[0], "Rev")) 
	{
		resp = 'R';
	}
	else if (ParserEqualString(argv[0], "Fast")) 
	{
		resp = 'f';
	}
	else if (ParserEqualString(argv[0], "Slow")) 
	{
		resp = 'S';
	}
	switch (resp) 
	{
		case 's':
			Motor1Stop();
#ifdef _DEBUG
			UsartSendString("Stop1\r\n");
#endif
			break;
		case 'e':
			Motor2Stop();
#ifdef _DEBUG
			UsartSendString("Stop2\r\n");
#endif
			break;
		case 'F':
		Motor1Forward();
#ifdef _DEBUG
			UsartSendString("Forward\r\n");
#endif
			break;
		case 'R':
#ifdef _DEBUG
			UsartSendString("Revers\r\n");
			Motor1Revers();
#endif
			break;
		case 'f':
		outPutCompare2 += 25;
		if (outPutCompare2 < 25) outPutCompare2 = 250;
		OCR2B = outPutCompare2;
#ifdef _DEBUG
			UsartSendString("Fast\r\n");
#endif
			break;
		case 'S':
		outPutCompare2 -= 25;
		if (outPutCompare2 == 0) outPutCompare2 = 25;
		OCR2B = outPutCompare2;
#ifdef _DEBUG
			UsartSendString("Slow\r\n");
#endif
			break;
		default:
			UsartSendString("Error\r\n");
			break;
	}
}

int main(void)
{
	/* uint8_t tmp; */
	Init();
	Timer2Init();
	Timer0Init();
	UsartInit(MYUBRR);
	sei();
	UsartSendString("Hello to HC-06!\r\n");
	while (1) 
	{
		ListenUsart();
		_delay_ms(1);
	}
	return 0;
}
