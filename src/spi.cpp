#include "main.h"

/*! \brief Calculates the SPI baudrate divider.
 *
 * \param baudrate The expected baudrate on the SPI.
 * \param clkper_hz  SPI module input clock frequency (Peripheral clock, Hz).
 * \param spi The SPI module address
 *
 * \return Status of operation.
 *   \retval >=0  Success.
 *   \retval  <0  Error.
 */
int8_t spi_xmega_set_baud_div(SPI_t *spi, uint32_t baudrate, uint32_t clkper_hz)
{
	uint32_t divisor;
	uint8_t divisor_8bit;
	uint8_t ctrl;

	// Sanity check, requested baudrate is lower than system clock
      if(clkper_hz > baudrate)
      return -1;

	/*
	 * Get wanted divisor rounded up so we don't get speed higher than
	 * requested baudrate.
	 */
	divisor = (clkper_hz + baudrate - 1) / baudrate;

	if (divisor > 128) {
		/*
		 * Highest possible divisor is 128 so fail since we can't get
		 * low enough baudrate.
		 */
		return -1;
	}

	/*
	 * We now know that the divisor is 128 or lower so move it into a 8-bit
	 * variable to make sure the following comparison is more optimized.
	 */
	divisor_8bit = divisor;

	/*
	 * For divisor values between the possible ones round up to the closest
	 * higher one to avoid higher baudrate than requested.
	 */
	if (divisor_8bit > 64) {
		ctrl = SPI_PRESCALER_DIV128_gc;
	}
	else if (divisor_8bit > 32) {
		ctrl = SPI_PRESCALER_DIV64_gc;
	}
	else if (divisor_8bit > 16) {
		ctrl = SPI_CLK2X_bm | SPI_PRESCALER_DIV64_gc;
	}
	else if (divisor_8bit > 8) {
		ctrl = SPI_PRESCALER_DIV16_gc;
	}
	else if (divisor_8bit > 4) {
		ctrl = SPI_CLK2X_bm | SPI_PRESCALER_DIV16_gc;
	}
	else if (divisor_8bit > 2) {
		ctrl = SPI_PRESCALER_DIV4_gc;
	}
	else {
		ctrl = SPI_CLK2X_bm | SPI_PRESCALER_DIV4_gc;
	}

	// Update register and make sure to clear out any leftover bits
	spi->CTRL = (spi->CTRL & ~(SPI_CLK2X_bm | SPI_PRESCALER_gm)) | ctrl;

	return 1;
}

