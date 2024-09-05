#include "ds18b20.h"
#include <string.h>
#define PORT_NAME PORTK
#define PIN_NUM PIN1_bm
#define PIN_NUM_CTRL PIN1CTRL
 
static void ds18b20_reset(void){
 
 PORT_NAME.PIN_NUM_CTRL = PORT_OPC_WIREDANDPULL_gc ;
 PORT_NAME.OUTCLR = PIN_NUM;
 PORT_NAME.DIRSET = PIN_NUM;
	_delay_us(480);
 PORT_NAME.DIRCLR = PIN_NUM;
	_delay_us(480);
 
}
 
static void ds18b20_write(uint8_t bit)
{
	PORT_NAME.PIN_NUM_CTRL = PORT_OPC_WIREDANDPULL_gc ;
	PORT_NAME.OUTCLR = PIN_NUM;
    PORT_NAME.DIRSET = PIN_NUM;
	_delay_us(15);
 	if (bit)
    PORT_NAME.DIRCLR = PIN_NUM;
	_delay_us(45);
	PORT_NAME.DIRCLR = PIN_NUM;
	_delay_us(10);
	
}
 
static uint8_t ds18b20_read(void)
{

	uint8_t tmp = 0;
 PORT_NAME.PIN_NUM_CTRL = PORT_OPC_WIREDANDPULL_gc ;
 PORT_NAME.OUTCLR = PIN_NUM;
 PORT_NAME.DIRSET = PIN_NUM;
	_delay_us(5);
 PORT_NAME.DIRCLR = PIN_NUM;
	_delay_us(15);

	if (PORT_NAME.IN & PIN_NUM) tmp = 1;
	_delay_us(50);
	return tmp;
}
 
static void ds18b20_write_byte(uint8_t data)
{
	uint8_t temp;
	uint8_t i;
 
	for (i = 0; i < 8; i++)
	{
 temp = data & 0x01;
		if (temp)
		ds18b20_write(1);
		else
		ds18b20_write(0);
 data >>= 1;
		_delay_us(10);
 
	}
}
 
 
static uint8_t ds18b20_read_byte(void){
	uint8_t i=8, n=0;
	while(i--){
		//Shift one position right and store read value
 n>>=1;
 n|=(ds18b20_read()<<7);
	}
	return n;
}
 
 
static uint16_t ds18b20_read_temp(void)
{
 
	uint8_t temperatura[2];
 
	ds18b20_reset();
	ds18b20_write_byte(THERM_CMD_SKIPROM);
	ds18b20_write_byte(THERM_CMD_CONVERTTEMP);
 
	_delay_us(1000);
 	 
	ds18b20_reset();
 
	ds18b20_write_byte(THERM_CMD_SKIPROM);
	ds18b20_write_byte(THERM_CMD_RSCRATCHPAD);
 
 temperatura[0] = ds18b20_read_byte();
 temperatura[1] = ds18b20_read_byte();
 
 
	return temperatura[0] + temperatura[1] * 0xFF;
}
 
 
 
static void reverse_string(char *s)
{
	char *p, c;
 
	for (p = s + strlen(s) - 1; s <= p; ++s, --p) {
 c = *p;
 *p = *s;
 *s = c;
	}
}
 
static void ts_to_string(uint16_t ts, char *s)
{
	int8_t t, neg;
	char *p = s;
 
	// integer part processing
	//
 t = (int8_t)(ts >> 4);
 neg = t & 0x80;
	if (neg)
 t = ~t;
	do {
 *p++ = t % 10 + '0';
 } while ((t /= 10) > 0);
 
 
 *p++ = neg ? '-' : '+';
 
 *p = '\0';
	reverse_string(s);
 
	// fractional part processing
	//
 *p++ = '.';
 t = (int8_t)ts & 0xf;
	if (neg)
 t = (-t) & 0xf;
 t = ((int16_t)t * 100) >> 4; // shift on 2 dec. digit, then mul 0.0625
	if ((t % 10) >= 5) // round
 t += 10;
 t /= 10; // shift on 1 decimal digit
 *p++ = (char)t + '0';
 
	*p = '\0';
}


 /////////////EXAMPLE//////////////////////////
// #include "main.h"
// #define F_CPU 32000000UL

// int main(){
// 
// uint16_t temp;
// uint16_t f=0;
// char buff[5];
// setEnternalClockTo32MHz();
// usart_init(&USARTC0,115200,32000000UL);

// while(1)
// {
// _delay_us(500);
// temp=ds18b20_read_temp();
// _delay_us(500);

// ts_to_string(temp,buff);
// for(f;f<5;f++)
// {
// usart_putchar(&USARTC0,buff[f]);
// }
// f=0;
// _delay_ms(1000);
// }

//     return 0;
// }
