#ifndef _XMEGA_USART_H_
#define _XMEGA_USART_H_
#include "main.h"

class XmegaUsart
{
private:
  enum xmega_usart_int_level_t
  {
    USART_INT_LVL_OFF = 0x00,
    USART_INT_LVL_LO = 0x01,
    USART_INT_LVL_MED = 0x02,
    USART_INT_LVL_HI = 0x03,
  };
  USART_t *usart;
  PORT_t *port_name;
  uint8_t tx_pin_bm;
  uint8_t rx_pin_bm;
  uint32_t baud;
  uint32_t cpu_hz;

public:
  XmegaUsart(USART_t *usart_, PORT_t *port_name_, uint8_t tx_pin_bm_, uint8_t rx_pin_bm_, uint32_t baud_, uint32_t cpu_hz_);

  void xmega_usart_init();
  inline void xmega_usart_rx_enable();
  inline void xmega_usart_rx_disable();
  inline void xmega_usart_tx_enable();
  inline void xmega_usart_tx_disable();
  inline void xmega_usart_set_rx_interrupt_level(xmega_usart_int_level_t level);
  inline void xmega_usart_set_tx_interrupt_level(xmega_usart_int_level_t level);
  inline void xmega_usart_set_dre_interrupt_level(xmega_usart_int_level_t level);
  inline bool xmega_usart_data_register_is_empty();
  inline bool xmega_usart_rx_is_complete();
  inline bool xmega_usart_tx_is_complete();
  inline void xmega_usart_clear_tx_complete();
  inline void xmega_usart_clear_rx_complete();
  inline void xmega_usart_put(uint8_t txdata);
  inline uint8_t xmega_usart_get();
  inline void xmega_usart_format_set(USART_CHSIZE_t charSize, USART_PMODE_t parityMode, bool twoStopBits);
  uint8_t xmega_usart_getchar();
  void xmega_usart_putchar(uint8_t c);
  void xmega_usart_set_bsel_bscale_value(uint16_t bsel, uint8_t bscale);
  bool xmega_usart_set_baudrate(uint32_t baud, uint32_t cpu_hz);
};

#endif // _XMEGA_USART_H_