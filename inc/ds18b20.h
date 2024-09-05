#ifndef _DS18B20_H_
#define _DS18B20_H_

#include "main.h"

#define THERM_DECIMAL_STEPS_12BIT 625 //.0625
#define THERM_DECIMAL_STEPS_9BIT 500 //.500
#define THERM_CMD_CONVERTTEMP 0x44
#define THERM_CMD_RSCRATCHPAD 0xbe
#define THERM_CMD_WSCRATCHPAD 0x4e
#define THERM_CMD_CPYSCRATCHPAD 0x48
#define THERM_CMD_RECEEPROM 0xb8
#define THERM_CMD_RPWRSUPPLY 0xb4
#define THERM_CMD_SEARCHROM 0xf0
#define THERM_CMD_READROM 0x33
#define THERM_CMD_MATCHROM 0x55
#define THERM_CMD_SKIPROM 0xcc
#define THERM_CMD_ALARMSEARCH 0xec
 
 
 void ds18b20_reset(void);
 void ds18b20_write(uint8_t bit);
 uint8_t ds18b20_read(void);
 void ds18b20_write_byte(uint8_t data);
 uint8_t ds18b20_read_byte(void);
 uint16_t ds18b20_read_temp(void);
 void ts_to_string(uint16_t ts, char *s);
 
 
 
#endif /* DS18B20_H_ */