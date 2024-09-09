#include "usart.h"
// Number tx/rx pin's for out and in
// #define PIN_TX         PIN3_bm
// #define PIN_RX         PIN2_bm
// #define PORTUART       PORTC
// init xmega usart:name and number USART,name PORT,number tx pin,number rx pin, speed,F_CPU

// Load number USART, speed and CPU_HZ
// Edit before using (format_set ,enable/disable tx/rx)
//   void usart_init(USART_t *usart,uint32_t baud, uint32_t cpu_hz)
//  {

// PORTC_DIRSET=PIN_TX;  //PORTC.PIN out for tx
// PORTC_OUTSET=PIN_TX;  //PORTC.PIN3 high for tx
// PORTC_DIRCLR=PIN_RX;  //PORTC.PIN2 in  for rx

// usart_set_baudrate(usart,baud,cpu_hz);
// usart_format_set(usart,USART_CHSIZE_8BIT_gc,USART_PMODE_DISABLED_gc,0);
// usart_tx_enable(usart);
// usart_rx_enable(usart);

// }
void usart_init(USART_t *usart, PORT_t *port_name, uint8_t tx_pin_bm, uint8_t rx_pin_bm, uint32_t baud, uint32_t cpu_hz)
{
	port_name->DIRSET = tx_pin_bm;
	port_name->OUTSET = tx_pin_bm;
	port_name->DIRCLR = rx_pin_bm;
	usart_set_baudrate(usart, baud, cpu_hz);
	usart_format_set(usart, USART_CHSIZE_8BIT_gc, USART_PMODE_DISABLED_gc, 0);
	usart_tx_enable(usart);
	usart_rx_enable(usart);
}
/**
 *  Configure the USART frame format.
 *
 *  Sets the frame format, Frame Size, parity mode and number of stop bits.
 *
 *  \param usart Pointer to the USART module
 *  \param charSize The character size. Use USART_CHSIZE_t type.
 *  \param parityMode The parity Mode. Use USART_PMODE_t type.
 *  \param twoStopBits Enable two stop bit mode. Use bool type.(1- enable 2 bit; 0-enable 1 bit)
 */
static inline void usart_format_set(USART_t *usart, USART_CHSIZE_t charSize, USART_PMODE_t parityMode, bool twoStopBits)
{
	(usart)->CTRLC = (uint8_t)charSize | parityMode | (twoStopBits ? USART_SBMODE_bm : 0);
}
// Enable USART receiver.

static inline void usart_rx_enable(USART_t *usart)
{

	(usart)->CTRLB |= USART_RXEN_bm;
}

// Disable USART receiver.

static inline void usart_rx_disable(USART_t *usart)
{
	(usart)->CTRLB &= ~USART_RXEN_bm;
}

// Enable USART transmitter.

static inline void usart_tx_enable(USART_t *usart)
{

	(usart)->CTRLB |= USART_TXEN_bm;
}

// Disable USART transmitter.

static inline void usart_tx_disable(USART_t *usart)
{
	(usart)->CTRLB &= ~USART_TXEN_bm;
}

// Set USART RXD interrupt level.
// Sets the interrupt level on RX Complete interrupt.
// param level Interrupt level of the RXD interrupt.

static inline void usart_set_rx_interrupt_level(USART_t *usart,
												enum usart_int_level_t level)
{
	(usart)->CTRLA = ((usart)->CTRLA & ~USART_RXCINTLVL_gm) |
					 (level << USART_RXCINTLVL_gp);
}

// Set USART TXD interrupt level.
// Sets the interrupt level on TX Complete interrupt.
// param level Interrupt level of the TXD interrupt.

static inline void usart_set_tx_interrupt_level(USART_t *usart,
												enum usart_int_level_t level)
{
	(usart)->CTRLA = ((usart)->CTRLA & ~USART_TXCINTLVL_gm) |
					 (level << USART_TXCINTLVL_gp);
}

// Set USART DRE interrupt level.
// Sets the interrupt level on Data Register interrupt.
// param level Interrupt level of the DRE interrupt.
//              Use USART_DREINTLVL_t type.

static inline void usart_set_dre_interrupt_level(USART_t *usart,
												 enum usart_int_level_t level)
{
	(usart)->CTRLA = ((usart)->CTRLA & ~USART_DREINTLVL_gm) |
					 (level << USART_DREINTLVL_gp);
}

// Check if data register empty flag is set.

static inline bool usart_data_register_is_empty(USART_t *usart)
{
	return (usart)->STATUS & USART_DREIF_bm;
}

// Checks if the RX complete interrupt flag is set.
// Checks if the RX complete interrupt flag is set.

static inline bool usart_rx_is_complete(USART_t *usart)
{
	return (usart)->STATUS & USART_RXCIF_bm;
}

// Checks if the TX complete interrupt flag is set.
// Checks if the TX complete interrupt flag is set.

static inline bool usart_tx_is_complete(USART_t *usart)
{
	return (usart)->STATUS & USART_TXCIF_bm;
}

// Clear TX complete interrupt flag.

static inline void usart_clear_tx_complete(USART_t *usart)
{
	(usart)->STATUS = USART_TXCIF_bm;
}

// Clear RX complete interrupt flag.

static inline void usart_clear_rx_complete(USART_t *usart)
{
	(usart)->STATUS = USART_RXCIF_bm;
}

// Write a data to the USART data register.
// param txdata The data to be transmitted.

static inline void usart_put(USART_t *usart, uint8_t txdata)
{
	(usart)->DATA = txdata;
}

// Read a data to the USART data register.
// return The received data

static inline uint8_t usart_get(USART_t *usart)
{
	return (usart)->DATA;
}

uint8_t usart_getchar(USART_t *usart)
{
	while (usart_rx_is_complete(usart) == false)
	{
	}

	return ((uint8_t)(usart)->DATA);
}
void usart_putchar(USART_t *usart, uint8_t c)
{
	while (usart_data_register_is_empty(usart) == false)
	{
	}

	(usart)->DATA = c;
}

/**
 * \brief Set the baudrate by setting the BSEL and BSCALE values in the USART
 *
 * This function sets the selected BSEL and BSCALE value in the BAUDCTRL
 * registers with BSCALE 0. For calculation options, see table 21-1 in XMEGA A
 * manual.
 *
 * \param usart  The USART module.
 * \param bsel   Calculated BSEL value.
 * \param bscale Calculated BSEL value.
 *
 */
void usart_set_bsel_bscale_value(USART_t *usart, uint16_t bsel, uint8_t bscale)
{
	(usart)->BAUDCTRLA = (uint8_t)(bsel);
	(usart)->BAUDCTRLB = (uint8_t)(((bsel >> 8) & 0X0F) | (bscale << 4));
}

/**
 * \brief Set the baudrate using precalculated BAUDCTRL values from PROGMEM
 *
 * \note This function only works for cpu_hz 2Mhz or 32Mhz and baudrate values
 * 1200, 2400, 4800, 9600, 19200, 38400 and 57600.
 *
 * \param usart  The USART module.
 * \param baud   The baudrate.
 * \param cpu_hz The CPU frequency.
 *
 */

// void usart_set_baudrate_precalculated(USART_t *usart, uint32_t baud,
// 		uint32_t cpu_hz)
// {
// 	uint8_t baud_offset;
// 	uint16_t baudctrl = 0;

// 	baud_offset = usart_get_baud_offset(baud);

// 	if (cpu_hz == 2000000UL) {
// 		baudctrl = PROGMEM_READ_WORD(baudctrl_2mhz + baud_offset);
// 	} else if (cpu_hz == 32000000UL) {
// 		baudctrl = PROGMEM_READ_WORD(baudctrl_32mhz + baud_offset);
// 	} else {
// 		/* Error, system clock speed or USART baud rate is not supported
// 		 * by the look-up table */
// 		Assert(false);
// 	}

// 	if (baud_offset != USART_BAUD_UNDEFINED) {
// 		(usart)->BAUDCTRLB = (uint8_t)((uint16_t)baudctrl);
// 		(usart)->BAUDCTRLA = (uint8_t)((uint16_t)baudctrl >> 8);
// 	}
// }

/**
 * \brief Set the baudrate value in the USART module
 *
 * This function sets the baudrate register with scaling regarding the CPU
 * frequency and makes sure the baud rate is supported by the hardware.
 * The function can be used if you don't want to calculate the settings
 * yourself or changes to baudrate at runtime is required.
 *
 * \param usart The USART module.
 * \param baud The baudrate.
 * \param cpu_hz The CPU frequency.
 *
 * \retval true if the hardware supports the baud rate
 * \retval false if the hardware does not support the baud rate (i.e. it's
 *               either too high or too low.)
 */
bool usart_set_baudrate(USART_t *usart, uint32_t baud, uint32_t cpu_hz)
{
	int8_t exp;
	uint32_t div;
	uint32_t limit;
	uint32_t ratio;
	uint32_t min_rate;
	uint32_t max_rate;

	/*
	 * Check if the hardware supports the given baud rate
	 */
	/* 8 = (2^0) * 8 * (2^0) = (2^BSCALE_MIN) * 8 * (BSEL_MIN) */
	max_rate = cpu_hz / 8;
	/* 4194304 = (2^7) * 8 * (2^12) = (2^BSCALE_MAX) * 8 * (BSEL_MAX+1) */
	min_rate = cpu_hz / 4194304;

	if (!((usart)->CTRLB & USART_CLK2X_bm))
	{
		max_rate /= 2;
		min_rate /= 2;
	}

	if ((baud > max_rate) || (baud < min_rate))
	{
		return false;
	}

	/* Check if double speed is enabled. */
	if (!((usart)->CTRLB & USART_CLK2X_bm))
	{
		baud *= 2;
	}

	/* Find the lowest possible exponent. */
	limit = 0xfffU >> 4;
	ratio = cpu_hz / baud;

	for (exp = -7; exp < 7; exp++)
	{
		if (ratio < limit)
		{
			break;
		}

		limit <<= 1;

		if (exp < -3)
		{
			limit |= 1;
		}
	}

	/*
	 * Depending on the value of exp, scale either the input frequency or
	 * the target baud rate. By always scaling upwards, we never introduce
	 * any additional inaccuracy.
	 *
	 * We are including the final divide-by-8 (aka. right-shift-by-3) in
	 * this operation as it ensures that we never exceeed 2**32 at any
	 * point.
	 *
	 * The formula for calculating BSEL is slightly different when exp is
	 * negative than it is when exp is positive.
	 */
	if (exp < 0)
	{
		/* We are supposed to subtract 1, then apply BSCALE. We want to
		 * apply BSCALE first, so we need to turn everything inside the
		 * parenthesis into a single fractional expression.
		 */
		cpu_hz -= 8 * baud;

		/* If we end up with a left-shift after taking the final
		 * divide-by-8 into account, do the shift before the divide.
		 * Otherwise, left-shift the denominator instead (effectively
		 * resulting in an overall right shift.)
		 */
		if (exp <= -3)
		{
			div = ((cpu_hz << (-exp - 3)) + baud / 2) / baud;
		}
		else
		{
			baud <<= exp + 3;
			div = (cpu_hz + baud / 2) / baud;
		}
	}
	else
	{
		/* We will always do a right shift in this case, but we need to
		 * shift three extra positions because of the divide-by-8.
		 */
		baud <<= exp + 3;
		div = (cpu_hz + baud / 2) / baud - 1;
	}

	(usart)->BAUDCTRLB = (uint8_t)(((div >> 8) & 0X0F) | (exp << 4));
	(usart)->BAUDCTRLA = (uint8_t)div;

	return true;
}

//////////////////EXAMPLE////////////////////////////
// #include "main.h"
// #define F_CPU 32000000UL

// int main(){

// uint8_t tx_buf[] = "Hello AVR world !";
// uint8_t tx_length = 17;
// uint8_t received_byte;
// uint8_t i;
// setEnternalClockTo32MHz();
// usart_init(&USARTC0,115200,32000000UL);

// //Output at startup
//    for (i = 0; i < tx_length; i++) {
// 		usart_putchar(&USARTC0, tx_buf[i]);
// 	}
// 	// Get and echo a character forever, specific 'q' processing.
// 	while (true) {
// 		received_byte = usart_getchar(&USARTC0);
// 		if (received_byte == 'q') {
// 			for (i = 0; i < tx_length; i++) {
// 				usart_putchar(&USARTC0, tx_buf[i]);
// 			}
// 		} else
// 			usart_putchar(&USARTC0, received_byte);
// 	}
//     return 0;
// }
/////////// example transmit///////////////////////////////////////
// uint8_t tx_buf[] = "Hello AVR world !";
// uint8_t tx_length = 17;
// uint8_t i;
// for (i = 0; i < tx_length; i++) {
//		usart_putchar(&USARTC0, tx_buf[i]);
// }
///////////////////////////////////////////////////////////////////