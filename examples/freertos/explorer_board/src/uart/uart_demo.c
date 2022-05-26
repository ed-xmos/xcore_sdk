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

#define MAX_TEST_VECT_SIZE  128

/* This example requires that you loopback the X1D12 and X1D39 pins */

void uart_tx_demo(void *arg){
    QueueHandle_t loopback_queue = arg;
    
    rtos_printf("uart_demo tx STARTED\n");
    rtos_uart_tx_start(uart_tx_ctx);
    uint8_t tx_buff[MAX_TEST_VECT_SIZE];
    for(int i = 0; i < MAX_TEST_VECT_SIZE; i++){
        tx_buff[i] = (i * 7) & 0xff;
    }

    vTaskDelay(pdMS_TO_TICKS(1000));

    for (;;) {
        BaseType_t success = xQueueSend(loopback_queue, (void *)tx_buff, (TickType_t)0);
        if(success != pdPASS){
            rtos_printf("Problem sending loopback data reference to rx task\n");
        }

        rtos_uart_tx_write(uart_tx_ctx, tx_buff, sizeof(tx_buff));

        vTaskDelay(pdMS_TO_TICKS(1000));
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
    if(err_flags & START_BIT_ERR_CB_FLAG){
        rtos_printf("UART_START_BIT_ERROR\n");
    }
    if(err_flags & PARITY_ERR_CB_FLAG){
        rtos_printf("UART_PARITY_ERROR\n");
    }
    if(err_flags & FRAMING_ERR_CB_FLAG){
        rtos_printf("UART_FRAMING_ERROR\n");
    }
    if(err_flags & OVERRUN_ERR_CB_FLAG){
        rtos_printf("OVERRUN_ERR_CB_CODE\n");
    }

    if(err_flags & ~RX_ERROR_FLAGS){
        rtos_printf("UNKNOWN ERROR FLAG SET: 0x%x (THIS SHOULD NEVER HAPPEN)\n", err_flags);
        rtos_printf("~RX_ERROR_FLAGS: 0x%x\n", ~RX_ERROR_FLAGS);

    }
}

void uart_rx_demo(void *arg){
    QueueHandle_t loopback_queue = arg;

    void *app_data = NULL;
    rtos_uart_rx_start(
            uart_rx_ctx,
            app_data,
            uart_rx_start_cb,
            uart_rx_complete_cb,
            uart_rx_error_cb,
            appconfUART_RX_INTERRUPT_CORE,
            appconfUART_RX_TASK_PRIORITY,
            MAX_TEST_VECT_SIZE);

    rtos_printf("uart_demo rx STARTED\n");

    int printed_once = 0;
    for (;;) {
        uint8_t rx_buf[MAX_TEST_VECT_SIZE] = {0};
        uint8_t tx_buf[MAX_TEST_VECT_SIZE] = {0};

        /* This will receive the test vector and sych rx with tx */
        BaseType_t success = xQueueReceive( loopback_queue,
                                            tx_buf,
                                            portMAX_DELAY);

        if(success != pdPASS){
            rtos_printf("Problem receiving loopback data reference from tx task - timeout\n");
        }


        for(int i = 0; i < MAX_TEST_VECT_SIZE; i++){
            int timeout_ms = 100;
            size_t num_bytes = xStreamBufferReceive(uart_rx_ctx->app_byte_buffer,
                                                    &rx_buf[i],
                                                    1,
                                                    pdMS_TO_TICKS(timeout_ms));
            if(num_bytes != 1){
                rtos_printf("Rx byte timed out after %d ms\n", timeout_ms);
            }
        }


        int data_different = memcmp(rx_buf, tx_buf, sizeof(tx_buf));

        if(data_different){
            rtos_printf("UART ERROR - mismatch of received data\n");
            for(int i = 0; i < MAX_TEST_VECT_SIZE; i++){
                if(tx_buf[i] != rx_buf[i]){
                    rtos_printf("index: %d expected: 0x%x got: 0x%x\n", i, tx_buf[i], rx_buf[i]);
                }
            }
        } else {
            if(!printed_once){
                rtos_printf("UART Loopback data (%d bytes) received correctly.\n", MAX_TEST_VECT_SIZE);
                rtos_printf("Further successful received packets will NOT be printed. Errors will be printed.\n");
                printed_once = 1; 
            }
        }

    }

}

void uart_demo_create(UBaseType_t priority)
{
    QueueHandle_t loopback_queue = xQueueCreate(2, MAX_TEST_VECT_SIZE);

    xTaskCreate((TaskFunction_t) uart_tx_demo,
                "uart_tx_demo",
                RTOS_THREAD_STACK_SIZE(uart_tx_demo),
                loopback_queue,
                priority,
                NULL);

    xTaskCreate((TaskFunction_t) uart_rx_demo,
                "uart_rx_demo",
                RTOS_THREAD_STACK_SIZE(uart_rx_demo),
                loopback_queue,
                priority,
                NULL);
}

