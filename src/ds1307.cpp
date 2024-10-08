#include "ds1307.h"
#define TWI_NAME TWIE
#define TWI_HZ  100000UL
#define WRITE 0
#define READ 1

//частота работы twi для ds1307 (100000)
 bool ds1307_baud_set(TWI_t *twi)
{
uint32_t div;
div = (F_CPU/(2*TWI_HZ))-5;
(twi)->MASTER.BAUD=div;
return 0;

}

 void ds1307_init(TWI_t*twi)
{
ds1307_baud_set(twi);
(twi)->MASTER.CTRLA=TWI_MASTER_ENABLE_bm;
(twi)->MASTER.STATUS= TWI_MASTER_BUSSTATE_IDLE_gc;

}
 uint8_t twi_send_msg(TWI_t * twi, uint8_t address, uint8_t *data, uint16_t msg_length)
{
	// Check bus state before doing anything, not idle -> exit with code 1
	// Проверяйте состояние шины, прежде чем что-либо делать, не в режиме ожидания -> выход с кодом 1
	if((twi->MASTER.STATUS & TWI_MASTER_BUSSTATE_gm) != TWI_MASTER_BUSSTATE_IDLE_gc)
		return 1;
	// Send slave address
	// Отправить адрес ведомого устройства
 twi->MASTER.ADDR =address | WRITE;
	while((twi->MASTER.STATUS & TWI_MASTER_WIF_bm) == 0) ; // loop until transaction is complete // цикл до завершения транзакции
	if(twi->MASTER.STATUS & TWI_MASTER_RXACK_bm) // No ACK from slave -> STOP ans exit with code 2// Нет подтверждения от slave -> ОСТАНОВИТЬ и завершить с кодом 2
	{
twi->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc; // release the bus with a stop condition// отпустите шину с условием остановки
		return 2;
	}
	// Send data// Отправить данные
	for(uint16_t i = 0; i < msg_length; i++)
	{
twi->MASTER.DATA = *(data + i);
		while((twi->MASTER.STATUS & TWI_MASTER_WIF_bm) == 0) ; // loop until transaction is complete
		if(twi->MASTER.STATUS & TWI_MASTER_RXACK_bm) // No ACK from slave -> STOP ans exit with code 2
		{
twi->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc; // release the bus with a stop condition
			return (3 + i);
		}
	}
	// Send stop and exit with code 0 (no error)
twi->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc; // release the bus with a stop condition
	return 0;
}

 uint8_t twi_read_msg(TWI_t *twi, uint8_t address, uint8_t register_address, uint8_t * data, uint16_t msg_length)
{
	// Check bus state before doing anything, not idle -> exit with code 1// Проверяйте состояние шины, прежде чем что-либо делать, не в режиме ожидания -> выход с кодом 1
	if((twi->MASTER.STATUS & TWI_MASTER_BUSSTATE_gm) != TWI_MASTER_BUSSTATE_IDLE_gc)
		return 1;
	// Send slave address
twi->MASTER.ADDR = address | WRITE;
	while((twi->MASTER.STATUS & TWI_MASTER_WIF_bm) == 0) ; // loop until transaction is complete
	if(twi->MASTER.STATUS & TWI_MASTER_RXACK_bm) // No ACK from slave -> STOP ans exit with code 2
	{
twi->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc; // release the bus with a stop condition
		return 2;
	}
	// Send register_address
twi->MASTER.DATA = register_address;
	while((twi->MASTER.STATUS & TWI_MASTER_WIF_bm) == 0) ; // loop until transaction is complete
	if(twi->MASTER.STATUS & TWI_MASTER_RXACK_bm) // No ACK from slave -> STOP ans exit with code 2
	{
twi->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc; // release the bus with a stop condition
		return 3;
	}
	// Restart
twi->MASTER.ADDR = address | READ;
	while((twi->MASTER.STATUS & TWI_MASTER_RIF_bm) == 0){} // loop until transaction is complete
	if(twi->MASTER.STATUS & TWI_MASTER_RXACK_bm) // No ACK from slave -> STOP ans exit with code 2
	{
twi->MASTER.CTRLC = TWI_MASTER_CMD_STOP_gc; // release the bus with a stop condition
		return 4;
	}
	// Read data + send ACK// Считывание данных + отправка подтверждения
	for(uint16_t i = 0; i < (msg_length - 1); i++)
	{
		while((twi->MASTER.STATUS & TWI_MASTER_RIF_bm) == 0){} // loop until transaction is complete
 *(data + i) =twi->MASTER.DATA;
twi->MASTER.CTRLC = TWI_MASTER_CMD_RECVTRANS_gc;
	}
	// Read last data + send NACK + STOP// Прочитать последние данные + отправить NACK + ОСТАНОВИТЬ
	while((twi->MASTER.STATUS & TWI_MASTER_RIF_bm) == 0){}	// loop until transaction is complete
 *(data + (msg_length - 1)) =twi->MASTER.DATA;
twi->MASTER.CTRLC = TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc;
	// Exit with code 0 (no error)
	return 0;
}

void TwoDigits(uint8_t data)
{
   uint8_t temp = data>>4;    // получить старшие 4 бита   
   data &= 0x0F;           // получить младшие 4 бита
          
}