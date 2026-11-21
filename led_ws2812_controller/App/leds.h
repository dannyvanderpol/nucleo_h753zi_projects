/* LEDs header file */

#ifndef LEDS_H
#define LEDS_H

#include "stm32h7xx_hal.h"


#define NUM_LEDS    75

void LEDS_Update(void);

// Struct for the LEDs
typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} LEDS_t;

// LED buffer default to off
extern LEDS_t LEDS_Buffer[NUM_LEDS];

#endif /* LEDS_H */
