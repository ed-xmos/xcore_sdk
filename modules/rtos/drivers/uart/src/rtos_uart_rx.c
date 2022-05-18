// Copyright 2022 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

#define DEBUG_UNIT RTOS_UART_RX
#define DEBUG_PRINT_ENABLE_RTOS_UART_RX 1

#include <xcore/triggerable.h>
#include <string.h>

#include "rtos_interrupt.h"
#include "rtos_uart_rx.h"
#include "task.h"


#define COMPLETE_CB_CODE       0
#define STARTED_CB_CODE        1
#define ERROR_CB_CODE          2

#define COMPLETE_CB_FLAG        (1 << COMPLETE_CB_CODE)
#define STARTED_CB_FLAG         (1 << STARTED_CB_CODE)
#define ERROR_CB_FLAG           (1 << ERROR_CB_CODE)

#define ALL_FLAGS (COMPLETE_CB_FLAG | STARTED_CB_FLAG | ERROR_CB_FLAG)


DEFINE_RTOS_INTERRUPT_CALLBACK(rtos_uart_rx_isr, arg)
{
    rtos_uart_rx_t *ctx = (rtos_uart_rx_t*)arg;
    int isr_action;

    isr_action = s_chan_in_byte(ctx->c.end_b);

    rtos_osal_event_group_set_bits(&ctx->events, 1 << isr_action);
    if(isr_action == COMPLETE_CB_CODE){
        uint8_t byte = s_chan_in_byte(ctx->c.end_b);
        BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
        size_t xBytesSent = xStreamBufferSendFromISR(ctx->byte_buffer, &byte, 1, &pxHigherPriorityTaskWoken);
        if(xBytesSent != 1){
            rtos_printf("ISR push buff full\n");
        }
        // taskYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
        //TODO is this available in xcore port?
    }
}



// static int i2c_shutdown(rtos_i2c_slave_t *ctx) {
//     return 0;
// }

static void uart_rx_hil_thread(rtos_uart_rx_t *ctx)
{
    // consume token (synch with RTOS driver)
    (void) s_chan_in_byte(ctx->c.end_a);

    rtos_printf("UART Rx HIL on tile %d core %d\n", THIS_XCORE_TILE, rtos_core_id_get());

    for (;;) {
        uint8_t byte = uart_rx(&ctx->ctx);
        //Now store byte and make notification
        // rtos_printf("UART Rx HIL received: 0x%x\n", byte);
        s_chan_out_byte(ctx->c.end_a, COMPLETE_CB_CODE);
        s_chan_out_byte(ctx->c.end_a, byte);
    }
}

static void uart_rx_app_thread(rtos_uart_rx_t *ctx)
{
    uint32_t flags = 0;

    if (ctx->rx_start_cb != NULL) {
        ctx->rx_start_cb(ctx, ctx->app_data);
    }

    // send token (synch with HIL logical core)
    s_chan_out_byte(ctx->c.end_b, 0);

    for (;;) {
        rtos_osal_event_group_get_bits(
                &ctx->events,
                ALL_FLAGS,
                RTOS_OSAL_OR_CLEAR,
                &flags,
                RTOS_OSAL_WAIT_FOREVER);

        if (flags & COMPLETE_CB_FLAG) {
            // rtos_printf("COMPLETE_CB_FLAG!!\n");

        } else {
            rtos_printf("Other OSAL event: 0x%x\n", flags);
        }
        //.....other callbacks here TODO
    }
}


UART_CALLBACK_ATTR void uart_rx_callback(uart_callback_t callback_info){
    switch(callback_info){
        case UART_TX_EMPTY:
            printstrln("UART_TX_EMPTY\n");
            break;
        case UART_START_BIT_ERROR:
            printstrln("UART_START_BIT_ERROR\n");
            break;
        case UART_PARITY_ERROR:
            printstrln("UART_PARITY_ERROR\n");
            break;
        case UART_FRAMING_ERROR:
            printstrln("UART_FRAMING_ERROR\n");
            break;
        case UART_OVERRUN_ERROR:
            printstrln("UART_OVERRUN_ERROR\n");
            break;
        case UART_UNDERRUN_ERROR:
            printstrln("UART_UNDERRUN_ERROR\n");
            break;
        case UART_RX_COMPLETE:
            printstrln("UART_RX_COMPLETE\n");
            break;
    }
}


void rtos_uart_rx_init(
        rtos_uart_rx_t *uart_rx_ctx,
        uint32_t io_core_mask,

        port_t rx_port,
        uint32_t baud_rate,
        uint8_t data_bits,
        uart_parity_t parity,
        uint8_t stop_bits,
        hwtimer_t tmr)
{
    memset(uart_rx_ctx, 0, sizeof(rtos_uart_rx_t));

    rtos_printf("rtos_uart_rx_init\n");

    uart_rx_init(
        &uart_rx_ctx->ctx,
        rx_port,
        baud_rate,
        data_bits,
        parity,
        stop_bits,
        tmr,
        NULL,
        0,
        uart_rx_callback
        );
 

    uart_rx_ctx->c = s_chan_alloc();

    triggerable_setup_interrupt_callback(uart_rx_ctx->c.end_b, uart_rx_ctx, RTOS_INTERRUPT_CALLBACK(rtos_uart_rx_isr));

    rtos_osal_thread_create(
            &uart_rx_ctx->hil_thread,
            "uart_rx_hil_thread",
            (rtos_osal_entry_function_t) uart_rx_hil_thread,
            uart_rx_ctx,
            RTOS_THREAD_STACK_SIZE(uart_rx_hil_thread),
            RTOS_OSAL_HIGHEST_PRIORITY);

    /* Ensure the UART thread is never preempted - effectively give whole logical core*/
    rtos_osal_thread_preemption_disable(&uart_rx_ctx->hil_thread);
    /* And ensure it only runs on one of the specified cores */
    rtos_osal_thread_core_exclusion_set(&uart_rx_ctx->hil_thread, ~io_core_mask);
}

void rtos_uart_rx_start(
        rtos_uart_rx_t *uart_rx_ctx,
        void *app_data,
        rtos_uart_rx_start_cb_t rx_start,
        rtos_uart_rx_complete_cb_t rx_complete_cb,
        rtos_uart_rx_error_t rx_error,
        unsigned interrupt_core_id,
        unsigned priority){
    
    /* Init callbacks & args */
    uart_rx_ctx->app_data = app_data;
    uart_rx_ctx->rx_start_cb = rx_start;
    uart_rx_ctx->rx_complete_cb = rx_complete_cb;
    uart_rx_ctx->rx_error_cb = rx_error;


    // void (*read)(rtos_uart_rx_t *, uint8_t buf[], size_t *num_bytes);


    rtos_osal_event_group_create(&uart_rx_ctx->events, "uart_rx_events");

    /* Ensure that the UART interrupt is enabled on the requested core */
    uint32_t core_exclude_map = 0;
    rtos_osal_thread_core_exclusion_get(NULL, &core_exclude_map);
    rtos_osal_thread_core_exclusion_set(NULL, ~(1 << interrupt_core_id));

    triggerable_enable_trigger(uart_rx_ctx->c.end_b);

    /* Restore the core exclusion map for the calling thread */
    rtos_osal_thread_core_exclusion_set(NULL, core_exclude_map);

    /* Setup buffer between ISR and receiving thread and set to trigger on single byte */
    uart_rx_ctx->byte_buffer = xStreamBufferCreate(RTOS_UART_RX_BUF_LEN, 1);

    rtos_osal_thread_create(
            &uart_rx_ctx->app_thread,
            "uart_rx_app_thread",
            (rtos_osal_entry_function_t) uart_rx_app_thread,
            uart_rx_ctx,
            RTOS_THREAD_STACK_SIZE(uart_rx_app_thread),
            priority);

}
