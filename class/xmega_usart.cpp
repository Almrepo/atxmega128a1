// xmega_usart.cpp
#include "xmega_usart.h"
#include "usart.h"

XmegaUsart::XmegaUsart(USART_t* usart, PORT_t* port_name, uint8_t tx_pin_bm, uint8_t rx_pin_bm, uint32_t baud, uint32_t cpu_hz)
    : usart_(usart), port_name_(port_name), tx_pin_bm_(tx_pin_bm), rx_pin_bm_(rx_pin_bm), baud_(baud), cpu_hz_(cpu_hz) {}

void XmegaUsart::init() {
    // Initialize USART
    usart_set_baudrate(usart_, baud_, cpu_hz_);
    usart_format_set(usart_, USART_CHSIZE_8BIT_gc, USART_PMODE_DISABLED_gc, 0);
    usart_tx_enable(usart_);
    usart_rx_enable(usart_);
}

void XmegaUsart::putchar(uint8_t c) {
    while (usart_data_register_is_empty(usart_) == false) {}
    usart_->DATA = c;
}

uint8_t XmegaUsart::getchar() {
    return usart_getchar(usart_);
}

void XmegaUsart::setBaudrate(uint32_t baud, uint32_t cpu_hz) {
    baud_ = baud;
    cpu_hz_ = cpu_hz;
    usart_set_baudrate(usart_, baud_, cpu_hz_);
}

void XmegaUsart::setFormat(USART_CHSIZE_t charSize, USART_PMODE_t parityMode, bool twoStopBits) {
    usart_format_set(usart_, charSize, parityMode, twoStopBits);
}

void XmegaUsart::enableRx() {
    usart_rx_enable(usart_);
}

void XmegaUsart::disableRx() {
    usart_rx_disable(usart_);
}

void XmegaUsart::enableTx() {
    usart_tx_enable(usart_);
}

void XmegaUsart::disableTx() {
    usart_tx_disable(usart_);
}