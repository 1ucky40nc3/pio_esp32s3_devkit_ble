#include <esp32-hal-rgb-led.h>

void turnLEDWhite()
{
    digitalWrite(RGB_BUILTIN, HIGH);
}

void turnLEDOff()
{
    digitalWrite(RGB_BUILTIN, LOW);
}

void turnLEDRed()
{
    neopixelWrite(RGB_BUILTIN, RGB_BRIGHTNESS, 0, 0);
}

void turnLEDGreen()
{
    neopixelWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0);
}

void turnLEDBlue()
{
    neopixelWrite(RGB_BUILTIN, 0, 0, RGB_BRIGHTNESS);
}
