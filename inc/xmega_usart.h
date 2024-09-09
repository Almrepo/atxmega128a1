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
  XmegaUsart(USART_t *usart, PORT_t *port_name, uint8_t tx_pin_bm, uint8_t rx_pin_bm, uint32_t baud, uint32_t cpu_hz);

  void xmega_usart_init();
  static inline void xmega_usart_rx_enable(USART_t *usart);
  static inline void xmega_usart_rx_disable(USART_t *usart);
  static inline void xmega_usart_tx_enable(USART_t *usart);
  static inline void xmega_usart_tx_disable(USART_t *usart);
  static inline void xmega_usart_set_rx_interrupt_level(USART_t *usart, xmega_usart_int_level_t level);
  static inline void xmega_usart_set_tx_interrupt_level(USART_t *usart, xmega_usart_int_level_t level);
  static inline void xmega_usart_set_dre_interrupt_level(USART_t *usart, xmega_usart_int_level_t level);
  static inline bool xmega_usart_data_register_is_empty(USART_t *usart);
  static inline bool xmega_usart_rx_is_complete(USART_t *usart);
  static inline bool xmega_usart_tx_is_complete(USART_t *usart);
  static inline void xmega_usart_clear_tx_complete(USART_t *usart);
  static inline void xmega_usart_clear_rx_complete(USART_t *usart);
  static inline void xmega_usart_put(USART_t *usart, uint8_t txdata);
  static inline uint8_t xmega_usart_get(USART_t *usart);
  static inline void xmega_usart_format_set(USART_t *usart, USART_CHSIZE_t charSize, USART_PMODE_t parityMode, bool twoStopBits);
  uint8_t xmega_usart_getchar(USART_t *usart);
  void xmega_usart_putchar(USART_t *usart, uint8_t c);
  void xmega_usart_set_bsel_bscale_value(USART_t *usart, uint16_t bsel, uint8_t bscale);
  bool xmega_usart_set_baudrate(USART_t *usart, uint32_t baud, uint32_t cpu_hz);
};

#endif // _XMEGA_USART_H_