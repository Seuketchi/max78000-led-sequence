/******************************************************************************
 * LED Abstraction Module Header
 * Manages 3x3 LED matrix (9 LEDs) on MAX78000
 ******************************************************************************/

#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>
#include "mxc_device.h"

/***** Public Definitions *****/

#define NUM_LEDS 9

/**
 * LED layout (3×3):
 *
 *  [0] [1] [2]
 *  [3] [4] [5]
 *  [6] [7] [8]
 */

/***** Public Function Declarations *****/

/**
 * Initialize all LEDs as GPIO outputs (active HIGH).
 */
void led_init(void);

/**
 * Turn on LED at index i (0 to NUM_LEDS-1).
 */
void led_on(int i);

/**
 * Turn off LED at index i (0 to NUM_LEDS-1).
 */
void led_off(int i);

/**
 * Toggle LED at index i (0 to NUM_LEDS-1).
 */
void led_toggle(int i);

/**
 * Turn off all LEDs.
 */
void all_leds_off(void);

/**
 * Turn on all LEDs.
 */
void all_leds_on(void);

/**
 * Fade LED in or out using software PWM.
 * 
 * @param led    LED index (0 to NUM_LEDS-1)
 * @param fade_in 1 for fade-in, 0 for fade-out
 */
void fade_led(int led, int fade_in);

#endif // __LED_H__
