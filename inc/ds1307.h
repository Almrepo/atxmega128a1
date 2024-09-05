#ifndef _DS1307_H_
#define _DS1307_H_

#include "main.h"

#define TWI_READ_BIT 1
#define SECONDS_REGISTER   0x00
#define MINUTES_REGISTER   0x01
#define HOURS_REGISTER     0x02
#define DAYOFWK_REGISTER   0x03
#define DAYS_REGISTER      0x04
#define MONTHS_REGISTER    0x05
#define YEARS_REGISTER     0x06

 bool ds1307_baud_set(TWI_t *twi);
 void ds1307_init(TWI_t*twi);
 uint8_t twi_send_msg(TWI_t * twi, uint8_t address, uint8_t *data, uint16_t msg_length);
 uint8_t twi_read_msg(TWI_t * twi, uint8_t address, uint8_t register_address, uint8_t * data, uint16_t msg_length);



#endif