/******************************************************************************
 * @file    gpio.c
 * @brief   Pure GPIO control library implementation
 * @details Simple GPIO wrapper functions
 ******************************************************************************/

#include "gpio.h"
#include "mxc_device.h"
#include "gpio.h"

/***** Functions *****/

int gpio_init_output(mxc_gpio_regs_t *port, uint32_t pin)
{
    mxc_gpio_cfg_t gpio_cfg;
    
    gpio_cfg.port = port;
    gpio_cfg.mask = pin;
    gpio_cfg.pad = MXC_GPIO_PAD_NONE;
    gpio_cfg.func = MXC_GPIO_FUNC_OUT;
    gpio_cfg.vssel = MXC_GPIO_VSSEL_VDDIO;
    gpio_cfg.drvstr = MXC_GPIO_DRVSTR_0;
    
    return MXC_GPIO_Config(&gpio_cfg);
}

int gpio_init_input(mxc_gpio_regs_t *port, uint32_t pin)
{
    mxc_gpio_cfg_t gpio_cfg;
    
    gpio_cfg.port = port;
    gpio_cfg.mask = pin;
    gpio_cfg.pad = MXC_GPIO_PAD_NONE;
    gpio_cfg.func = MXC_GPIO_FUNC_IN;
    gpio_cfg.vssel = MXC_GPIO_VSSEL_VDDIO;
    gpio_cfg.drvstr = MXC_GPIO_DRVSTR_0;
    
    return MXC_GPIO_Config(&gpio_cfg);
}

void gpio_set(mxc_gpio_regs_t *port, uint32_t pin)
{
    MXC_GPIO_OutSet(port, pin);
}

void gpio_clear(mxc_gpio_regs_t *port, uint32_t pin)
{
    MXC_GPIO_OutClr(port, pin);
}

void gpio_toggle(mxc_gpio_regs_t *port, uint32_t pin)
{
    MXC_GPIO_OutToggle(port, pin);
}

void gpio_write(mxc_gpio_regs_t *port, uint32_t pin, gpio_state_t state)
{
    if (state == HIGH) {
        MXC_GPIO_OutSet(port, pin);
    } else {
        MXC_GPIO_OutClr(port, pin);
    }
}

gpio_state_t gpio_read(mxc_gpio_regs_t *port, uint32_t pin)
{
    return (MXC_GPIO_InGet(port, pin)) ? HIGH : LOW;
}