
#include "main.h"
#define F_CPU 32000000UL
#define READ_BIT 1
#define WRITE_BIT 0

// Функция для передачи данных по TWI

// void TWI_MasterWrite(TWI_t*twi,uint8_t address, uint8_t* data, uint8_t bytes_to_send) {
//     // Настройка TWI для передачи данных
//     twi->MASTER.ADDR = address | WRITE_BIT;

//     for (uint8_t i = 0; i < bytes_to_send;) {
//         twi->MASTER.DATA = data[i];
//         i++;
//         while (!(twi->MASTER.STATUS & TWI_MASTER_WIF_bm));
//     }

//     // Завершение передачи
//     twi->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc;
// }

// // Функция для приема данных по TWI
// void TWI_MasterRead(TWI_t*twi,uint8_t address, uint8_t* data, uint8_t bytes_to_receive) {
//     // Настройка TWI для приема данных
//     twi->MASTER.ADDR = address | READ_BIT;

//     for (uint8_t i = 0; i < bytes_to_receive; i++) {
//         while (!(twi->MASTER.STATUS & TWI_MASTER_RIF_bm));
//         data[i] = twi->MASTER.DATA;
//     }

//     // Завершение приема
//     twi->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc;
// }

int main()
{
   uint8_t t_rtc[7];

   uint8_t tx_buf[7] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
   uint8_t tx_length[7];
   uint8_t data[2];

   setInternalClockTo32MHz();
   // xmega_usart_init(&USARTC0,&PORTC,PIN3_bm,PIN2_bm,9600,32000000);
   // usart_init(&USARTC0,9600,32000000UL);
   XmegaUsart usartc0(&USARTC0, &PORTC, PIN3_bm, PIN2_bm, 9600, 32000000);
   ds1307_init(&TWIE);
   usartc0.xmega_usart_putchar(&USARTC0, tx_buf[2]);
   // twi_send_msg(&TWIE,0xd0,tx_buf,6);

   while (1)
   {

      for (uint8_t i = 0; i < 7; i++)

         usartc0.xmega_usart_putchar(&USARTC0, tx_buf[i]);
      // twi_read_msg(&TWIE,0xd0,0x01,tx_length,1);
      _delay_ms(500);

      // unsigned char chas = ((tx_length[2]>>4)*10+(0x0f&tx_length[2]));
      // uint8_t min = ((tx_length[1]>>4)*10+(0x0f&tx_length[1]));
      // unsigned char sec = ((tx_length[0]>>4)*10+(0x0f&tx_length[0]));
      // usart_putchar(&USARTC0,chas);
      // usart_putchar(&USARTC0,min);
      // usart_putchar(&USARTC0,sec);

      // twi_send_msg(&TWIE,0xd0,tx_buf,7);

      // twi_read_msg(&TWIE,0xd0,0x00,t_data,7);

      // usart_putchar(&USARTC0,tx_buf[7]);
   }
   return 0;
}
