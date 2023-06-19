/*
 * ATMega16_SPI_Slave.c
 *
 * Created: 2023-06-18 10:15:03 PM
 * Author : a_shi
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void SPI_Write(unsigned char data)
{
	SPDR = data;
	while (!(SPSR &(1<<SPIF)));
}

unsigned char SPI_Read()
{
	while (!(SPSR & (1<<SPIF)));
	return SPDR;
}

unsigned char data;

int main(void)
{
	DDRB &= (~(1<<DDB4)) & (~(1<<DDB5)) & (~(1<<DDB7));		//PB4,5,7 as Input {IN Slave configuration MOSI, SS, and SCK are Input}
	DDRB |= (1<<DDB6);							//PB6 as Output {And MISO is Output}
	DDRC |= (1<<DDC0);		// LED is output.
	SPCR |= (1<<SPE);
	
	while (1)
	{
		data = SPI_Read();
		if (data == 'A')
		{
			PORTC |= (1<<PC0);
		}
		if (data == 'B')
		{
			PORTC &= (~(1<<PC0));
		}
	}
}

