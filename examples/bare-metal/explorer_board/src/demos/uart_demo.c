// Copyright 2021 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

/* System headers */
#include <platform.h>
#include <xs1.h>

/* SDK headers */
#include "soc.h"
#include "xcore_utils.h"
#include "uart.h"

/* App headers */
#include "app_conf.h"
#include "app_demos.h"

void uart_rx_demo(uart_rx_t* uart_rx_ctx)
{
    return;
    uint8_t expected = 0;
    while(1) {
        uint8_t rx = uart_rx(uart_rx_ctx);
        if(rx != expected){
            // debug_printf("UART data error, expected %d got %d\n", expected, rx);
        }
        expected++;
    }
}

void uart_tx_demo(uart_tx_t* uart_tx_ctx)
{
    uint8_t tx_data = 0;
    while(1) {
        uart_tx(uart_tx_ctx, tx_data);
        // debug_printf("%d\n", tx_data);
        tx_data+=1;
        // delay_milliseconds(1);
    }   
}
