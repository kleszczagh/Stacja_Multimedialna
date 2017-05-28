/*
 * main.c
 *
 *  Created on: 13 maj 2017
 *      Author: lenovo
 */

#include <avr/io.h>
#include <avr/delay.h>

#include "MK_OLED/mk_ssd1306.h"
#include "MK_USART/mkuart.h"
#include "icons.h"
#include <avr/interrupt.h>


char bufor[100];	// bufor na potrzeby odebranych danych z UART

// rejestracja w³asnej funkcji do analizowania danych odebranych przez UART
void parse_uart_data( char * pBuf );




int main(){

	mk_ssd1306_init( SSD1306_SWITCHCAPVCC, REFRESH_MAX, 0);
	mk_ssd1306_contrast(128);
	mk_ssdD1306_cls();

	sei();
	USART_Init(__UBRR);
	register_uart_str_rx_event_callback( parse_uart_data );





//	mk_ssd1306_fillRect( 30,30, 20,30,1);

	mk_ssd1306_puts(0,0, "LONDYNNN", 2, 1, 0 );




	mk_ssd1306_puts(56,16, "Temp: 30,2 C", 1, 1, 0 );
	mk_ssd1306_puts(56,24, "Wilg: 42%", 1, 1, 0 );
	mk_ssd1306_puts(56,32, "Opad: brak", 1, 1, 0 );
	mk_ssd1306_puts(56,40, "Wiatr:10km/h", 1, 1, 0 );


	mk_ssd1306_display();

	while(1){


		UART_RX_STR_EVENT(bufor);	// zdarzenie odbiorcze UART

	}

}


void parse_uart_data( char * pBuf ) {



	mk_ssd1306_puts(56,48, pBuf, 1, 1, 0 );
	mk_ssd1306_display();

	return;
}
