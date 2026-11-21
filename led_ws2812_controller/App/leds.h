#ifndef LEDS_H
#define LEDS_H

#include "stm32h7xx_hal.h"


#define NUM_LEDS    75

void UpdateLeds(void);

// Struct for the LEDs
typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Led_t;

// LED buffer default to off
extern Led_t LedBuffer[NUM_LEDS];

#endif /* LEDS_H */
