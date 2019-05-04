#ifndef  USART_INC
#define  USART_INC

#include <inttypes.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#define F_CPU					16000000UL
#define BAUD					9600
#define MYUBRR					F_CPU/16/BAUD-1

#define USART_TX_BUFFER_SIZE	20
#define USART_RX_BUFFER_SIZE	20


//Prototypes
void UsartInit				(uint16_t baudRate);
void UsartFlushTxBuffer		(void);
void UsartPutChar			(char ch);
void UsartSendString		(char *string);
void UsartSendStringFlash	(const char *string);
uint8_t UsartGetChar		(void);
uint8_t UsartGetRxCount		(void);

#endif   /* ----- #ifndef USART_INC  ----- */
