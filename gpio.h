/******************************************************************************
 * @file    gpio.h
 * @brief   Pure GPIO control library for MAX78000
 * @details Simple wrapper for GPIO operations - no assumptions about usage
 ******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "mxc_device.h"

/***** Type Definitions *****/

// GPIO state
typedef enum {
    LOW = 0,
    HIGH = 1
} gpio_state_t;

/***** Function Prototypes *****/

/**
 * @brief Initialize a GPIO pin as output
 * @param port GPIO port (MXC_GPIO0, MXC_GPIO1, MXC_GPIO2, MXC_GPIO3)
 * @param pin Pin mask (MXC_GPIO_PIN_0 through MXC_GPIO_PIN_31)
 * @return 0 on success, negative on error
 */
int gpio_init_output(mxc_gpio_regs_t *port, uint32_t pin);

/**
 * @brief Initialize a GPIO pin as input
 * @param port GPIO port
 * @param pin Pin mask
 * @return 0 on success, negative on error
 */
int gpio_init_input(mxc_gpio_regs_t *port, uint32_t pin);

/**
 * @brief Set GPIO pin HIGH (3.3V)
 * @param port GPIO port
 * @param pin Pin mask
 */
void gpio_set(mxc_gpio_regs_t *port, uint32_t pin);

/**
 * @brief Set GPIO pin LOW (0V)
 * @param port GPIO port
 * @param pin Pin mask
 */
void gpio_clear(mxc_gpio_regs_t *port, uint32_t pin);

/**
 * @brief Toggle GPIO pin state
 * @param port GPIO port
 * @param pin Pin mask
 */
void gpio_toggle(mxc_gpio_regs_t *port, uint32_t pin);

/**
 * @brief Write specific state to GPIO pin
 * @param port GPIO port
 * @param pin Pin mask
 * @param state HIGH or LOW
 */
void gpio_write(mxc_gpio_regs_t *port, uint32_t pin, gpio_state_t state);

/**
 * @brief Read current state of GPIO pin
 * @param port GPIO port
 * @param pin Pin mask
 * @return HIGH (1) or LOW (0)
 */
gpio_state_t gpio_read(mxc_gpio_regs_t *port, uint32_t pin);

#endif /* GPIO_H_ */