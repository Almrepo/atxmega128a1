#ifndef _SPI_H_
#define _SPI_H_
#include "main.h"


/*! \brief Calculates the SPI baudrate divider.
 *
 * \param baudrate The expected baudrate on the SPI.
 * \param clkper_hz  SPI module input clock frequency (Peripheral clock, Hz).
 * \param spi The SPI module address
 *
 * \return Divider or error code.
 *   \retval >=0  Success.
 *   \retval  <0  Error.
 */
int8_t spi_xmega_set_baud_div(SPI_t *spi, uint32_t baudrate, uint32_t clkper_hz);

/*! \brief Enables the SPI.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_enable(SPI_t *spi)
{
	spi->CTRL |= SPI_ENABLE_bm;
}

/*! \brief Disables the SPI.
 *
 * Ensures that nothing is transferred while setting up buffers.
 *
 * \param spi Base address of the SPI instance.
 *
 * \warning This may cause data loss if used on a slave SPI.
 */
static inline void spi_disable(SPI_t *spi)
{
	spi->CTRL &= ~SPI_ENABLE_bm;
}

/*! \brief Tests if the SPI is enabled.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI is enabled, otherwise \c 0.
 */
static inline bool spi_is_enabled(SPI_t *spi)
{
	return spi->CTRL & SPI_ENABLE_bm ? true : false;
}

/*! \brief Put one data byte to a SPI peripheral.
 *
 * \param spi Base address of the SPI instance.
 * \param data The data byte to be loaded
 *
 */
static inline void spi_put(SPI_t *spi, uint8_t data)
{
	spi->DATA = data;
}

/*! \brief Get one data byte to a SPI peripheral.
 *
 * \param spi Base address of the SPI instance.
 * \return The data byte
 *
 */
static inline uint8_t spi_get(SPI_t *spi)
{
	return spi->DATA;
}

/*! \brief Tests if the SPI contains a received character.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI Receive Holding Register is full, otherwise \c 0.
 */
static inline bool spi_is_tx_ok(SPI_t *spi)
{
	return spi->STATUS & SPI_IF_bm ? true : false;
}

/*! \brief Activate SPI master mode of a SPI peripheral
 *
 * \param spi Base address of the SPI instance.
 *
 * \warning This may cause data loss if used on a slave SPI.
 */
static inline void spi_enable_master_mode(SPI_t *spi)
{
	spi->CTRL |= SPI_MASTER_bm;
}


#endif  // _SPI_H_
