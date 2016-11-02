/**
 * Copyright (c) 2016. SAN team. All rights reserved.
 *
 * @file main.c
 *
 * @brief initialization project for nrf51822 module on waveshare motherboard.
 *
 * @author Ivan Pavic
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "sdk_common.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_error.h"
#include "boards.h"

#define NRF_LOG_MODULE_NAME "NRF_INIT"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

/**
 * Function starts clocks.
 */
void clocks_start(void)
{
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_HFCLKSTART = 1;

    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);
}

/**
 * Function initializes LEDs based on chosen board support.
 */
void gpio_init(void)
{
    LEDS_CONFIGURE(LEDS_MASK);
}

int main(void)
{
    uint32_t err_code;

    gpio_init();

    err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    clocks_start();

    NRF_LOG_INFO("nrf51822_xxaa dev-board running.\r\n");
    NRF_LOG_FLUSH();

    nrf_gpio_pin_write(LED_1, 1);

    while (1367)
    {
        nrf_gpio_pin_write(LED_1, 1);
        nrf_delay_ms(500);
        nrf_gpio_pin_write(LED_1, 0);
        nrf_delay_ms(500);
    }
}
