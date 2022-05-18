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


port_t tx_port = WIFI_WUP_RST_N;
port_t rx_port = WIFI_WIRQ;

void uart_tx_demo(void)
{
    uint32_t status;
    // TimerHandle_t volume_up_timer;

    rtos_printf("uart_demo\n");

    rtos_uart_tx_t ctx;
    hwtimer_t tmr = hwtimer_alloc();

    rtos_uart_tx_init(
            &ctx,
            tx_port,
            115200,
            8,
            UART_PARITY_NONE,
            1,
            tmr);

    rtos_uart_tx_start(&ctx);
   
    // rtos_printf("enable button isr\n");
    // rtos_gpio_isr_callback_set(gpio_ctx_t0, button_port, button_callback, xTaskGetCurrentTaskHandle());
    // rtos_gpio_interrupt_enable(gpio_ctx_t0, button_port);

    // rtos_printf("enable button timers\n");
    // volume_up_timer = xTimerCreate(
    //                         "vol_up",
    //                         pdMS_TO_TICKS(appconfGPIO_VOLUME_RAPID_FIRE_MS),
    //                         pdTRUE,
    //                         NULL,
    //                         vVolumeUpCallback );

    for (;;) {

        xTaskNotifyWait(
                0x00000000UL,    /* Don't clear notification bits on entry */
                0xFFFFFFFFUL,    /* Reset full notification value on exit */
                &status,         /* Pass out notification value into status */
                100 ); /* Wait indefinitely until next notification */
                // portMAX_DELAY ); /* Wait indefinitely until next notification */

        rtos_printf("uart_demo loop\n");

        uint8_t tx_buff[] = {0x00, 0xff, 0xaa};
        rtos_uart_tx(&ctx, tx_buff, sizeof(tx_buff));


        // buttons_val = rtos_gpio_port_in(gpio_ctx_t0, button_port);
        // buttonA = ( buttons_val >> 0 ) & 0x01;
        // buttonB = ( buttons_val >> 1 ) & 0x01;

        // /* Turn on LEDS based on buttons */
        // rtos_gpio_port_out(gpio_ctx_t0, led_port, buttons_val);

        //  Adjust volume based on LEDs 
        // if( buttonA == 0 )   /* Up */
        // {
        //     xTimerStart( volume_up_timer, 0 );
        //     volume_up();
        //     // rtos_printf("volume up start\n");
        // }
        // else
        // {
        //     xTimerStop( volume_up_timer, 0 );
        // }
    }
}

void uart_rx_start_cb(rtos_uart_rx_t *uart_rx_ctx, void *app_data){

}
void uart_rx_complete_cb(rtos_uart_rx_t *uart_rx_ctx, void *app_data){

}
void uart_rx_error_cb(rtos_uart_rx_t *uart_rx_ctx, void *app_data){

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
            appconfUART_RX_TASK_PRIORITY);

    for (;;) {
        
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


void uart_rx_pre_os_startup_init(void){

    hwtimer_t tmr = hwtimer_alloc();

    rtos_uart_rx_init(
            uart_rx_ctx,
             (1 << appconfUART_RX_IO_CORE),
            rx_port,
            115200,
            8,
            UART_PARITY_NONE,
            1,
            tmr);
}

