// xmega_usart.h
#ifndef _XMEGA_USART_H_
#define _XMEGA_USART_H_

#include <avr/io.h>

class XmegaUsart {
public:
    XmegaUsart(USART_t* usart, PORT_t* port_name, uint8_t tx_pin_bm, uint8_t rx_pin_bm, uint32_t baud, uint32_t cpu_hz);
    void init();
    void putchar(uint8_t c);
    uint8_t getchar();
    void setBaudrate(uint32_t baud, uint32_t cpu_hz);
    void setFormat(USART_CHSIZE_t charSize, USART_PMODE_t parityMode, bool twoStopBits);
    void enableRx();
    void disableRx();
    void enableTx();
    void disableTx();

private:
    USART_t* usart_;
    PORT_t* port_name_;
    uint8_t tx_pin_bm_;
    uint8_t rx_pin_bm_;
    uint32_t baud_;
    uint32_t cpu_hz_;
};

#endif  // _XMEGA_USART_H_