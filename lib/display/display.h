#ifndef display_h
#define display_h

#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>

class Display : public U8G2 {
    private:
        void drawImage(const unsigned char * image);
    public:
        Display(const u8g2_cb_t *rotation, uint8_t cs, uint8_t dc, uint8_t reset = U8X8_PIN_NONE) : U8G2() {
            u8g2_Setup_ssd1306_128x64_noname_2(&u8g2, rotation, u8x8_byte_arduino_hw_spi, u8x8_gpio_and_delay_arduino);
            u8x8_SetPin_4Wire_HW_SPI(getU8x8(), cs, dc, reset);
        }

        void drawBPMScreen();
        void drawO2Screen();
        void drawBPMValue(int value);
        void drawO2Value(int value);
        void startAnimation();
};

#endif