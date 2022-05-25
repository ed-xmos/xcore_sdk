// Copyright 2019-2022 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

/* System headers */
#include <platform.h>
#include <xs1.h>

/* FreeRTOS headers */
#include "FreeRTOS.h"
#include "queue.h"

/* Library headers */
#include "fs_support.h"

/* App headers */
#include "app_conf.h"
#include "platform/driver_instances.h"

// for uart_demo
#include "task.h"
#include "xcore/hwtimer.h"
#include "rtos_uart_tx.h"
#include "rtos_uart_rx.h"


/* This example requires that you loopback the XXXXX pins */

void uart_tx_demo(void)
{
    rtos_printf("uart_demo\n");


    rtos_uart_tx_start(uart_tx_ctx);
   
    for (;;) {
        uint8_t tx_buff[] = {0x00, 0xff, 0xaa};
        rtos_printf("uart send...\n");
        rtos_uart_tx_write(uart_tx_ctx, tx_buff, sizeof(tx_buff));

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

RTOS_UART_RX_CALLBACK_ATTR
void uart_rx_start_cb(rtos_uart_rx_t *uart_rx_ctx){
    rtos_printf("uart_rx_start_cb\n");
}

RTOS_UART_RX_CALLBACK_ATTR
void uart_rx_complete_cb(rtos_uart_rx_t *uart_rx_ctx){
    //Do nothing
}

RTOS_UART_RX_CALLBACK_ATTR
void uart_rx_error_cb(rtos_uart_rx_t *ctx, uint8_t err_flags){
    uart_callback_code_t cb_code = ctx->dev.cb_code;
    if(cb_code & START_BIT_ERR_CB_FLAG){
        rtos_printf("UART_START_BIT_ERROR\n");
    }
    if(cb_code & PARITY_ERR_CB_FLAG){
        rtos_printf("UART_PARITY_ERROR\n");
    }
    if(cb_code & FRAMING_ERR_CB_FLAG){
        rtos_printf("UART_FRAMING_ERROR\n");
    }
    if(cb_code & OVERRUN_ERR_CB_FLAG){
        rtos_printf("OVERRUN_ERR_CB_CODE\n");
    }

    if(cb_code & ~ RX_ERROR_FLAGS){
        rtos_printf("UNKNOWN ERROR FLAG SET: 0x%x (THIS SHOULD NEVER HAPPEN)\n", cb_code);
    }
}

void uart_rx_demo(void){
    void *app_data = NULL;

    rtos_uart_rx_start(
            uart_rx_ctx,
            app_data,
            uart_rx_start_cb,
            uart_rx_complete_cb,
            uart_rx_error_cb,
            (1 << appconfUART_RX_INTERRUPT_CORE),
            appconfUART_RX_TASK_PRIORITY,
            16);

    for (;;) {
        uint8_t rx_byte = 0;
        xStreamBufferReceive(   uart_rx_ctx->app_byte_buffer,
                                &rx_byte,
                                1,
                                portMAX_DELAY);
        rtos_printf("uart receive: 0x%x\n", rx_byte);


    }

}

void uart_demo_create(UBaseType_t priority)
{

    xTaskCreate((TaskFunction_t) uart_tx_demo,
                "uart_tx_demo",
                RTOS_THREAD_STACK_SIZE(uart_tx_demo),
                NULL,
                priority,
                NULL);

    xTaskCreate((TaskFunction_t) uart_rx_demo,
                "uart_rx_demo",
                RTOS_THREAD_STACK_SIZE(uart_rx_demo),
                NULL,
                priority,
                NULL);
}

