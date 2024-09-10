
#include "clock.h"
void setInternalClockTo32MHz()
{
   // CCP = CCP_IOREG_gc; // disable register security for oscillator update
   OSC.CTRL = OSC_RC32MEN_bm; // enable 32MHz oscillator
   while (!(OSC.STATUS & OSC_RC32MRDY_bm))
      ;                             // wait for oscillator to be ready
   CCP = CCP_IOREG_gc;              // disable register security for clock update
   CLK.CTRL = CLK_SCLKSEL_RC32M_gc; // switch to 32MHz clock
}

void setInternalClockTo2MHz()
{
   // CCP = CCP_IOREG_gc;
   OSC.CTRL = OSC_RC2MEN_bm; // enable 2 MHz oscillator
   while (!(OSC.STATUS & OSC_RC2MRDY_bm))
      ;
   CCP = CCP_IOREG_gc;
   CLK.CTRL = CLK_SCLKSEL_RC2M_gc;
}

// настройка внешнего тактового генератора 16MHz
void setExternalClockTo16MHz()
{
   OSC_XOSCCTRL = OSC_FRQRANGE_12TO16_gc | OSC_XOSCSEL_XTAL_256CLK_gc; // параметры кварца
   OSC_CTRL = OSC_XOSCEN_bm;                                           // разрешаем работу внешнего кварца
   while (!(OSC_STATUS & OSC_XOSCRDY_bm))
      ;                            // Ожидание готовности тактового генератора
   CCP = CCP_IOREG_gc;             // Разрешение записи в защищённый регистр
   CLK_CTRL = CLK_SCLKSEL_XOSC_gc; // Подключение к тактовому генератору
}
