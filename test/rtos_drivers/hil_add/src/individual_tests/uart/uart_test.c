// Copyright 2022 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

/* System headers */
#include <platform.h>
#include <xs1.h>
#include <string.h>

/* FreeRTOS headers */
#include "FreeRTOS.h"

/* Library headers */
#include "rtos_uart_tx.h"
#include "rtos_uart_rx.h"

/* App headers */
#include "app_conf.h"
#include "individual_tests/uart/uart_test.h"


RTOS_UART_RX_CALLBACK_ATTR
void uart_rx_start_cb(rtos_uart_rx_t *uart_rx_ctx, void *app_data){

}

RTOS_UART_RX_CALLBACK_ATTR
void uart_rx_complete_cb(rtos_uart_rx_t *uart_rx_ctx, void *app_data){

}

RTOS_UART_RX_CALLBACK_ATTR
void uart_rx_error_cb(rtos_uart_rx_t *uart_rx_ctx, void *app_data){

}

static int run_uart_tests(uart_test_ctx_t *test_ctx)
{
    int retval = 0;

    do
    {
        uint8_t tx_buff[] = {0xed, 0x00, 0x77, 0xed, 0x00, 0x77, 0xed, 0x00, 0x55, 0x55, 0x55, 0x55};
        rtos_uart_tx_write(test_ctx->rtos_uart_tx_ctx, tx_buff, sizeof(tx_buff));
    
        uint8_t rx_buff[sizeof(tx_buff)] = {0};
        size_t num_rx = xStreamBufferReceive(   test_ctx->rtos_uart_rx_ctx->byte_buffer,
                                                rx_buff,
                                                sizeof(tx_buff),
                                                portMAX_DELAY);
        int length_same = (num_rx == sizeof(tx_buff));        
        int array_different = memcmp(tx_buff, rx_buff, sizeof(tx_buff));
        uart_printf("uart loopback result len: %s, contents: %s", array_different ? "FAIL" : "PASS", length_same ? "PASS" : "FAIL");

        if (!length_same || array_different){
            retval = -1;
        }
    } while (++test_ctx->cur_test < test_ctx->test_cnt);

    return retval;
}

static void start_uart_devices(uart_test_ctx_t *test_ctx)
{
#if ON_TILE(1)
    void *app_data = NULL;

    uart_printf("RX start");
    rtos_uart_rx_start(
        test_ctx->rtos_uart_rx_ctx,
        app_data,
        uart_rx_start_cb,
        uart_rx_complete_cb,
        uart_rx_error_cb,
        (1 << UART_RX_ISR_CORE),
        appconfSTARTUP_TASK_PRIORITY);

    uart_printf("TX start");
    rtos_uart_tx_start(test_ctx->rtos_uart_tx_ctx);
#endif

    uart_printf("Devices setup done");
}

static void register_uart_tests(uart_test_ctx_t *test_ctx)
{
    // register_single_transaction_test(test_ctx);
    // register_multiple_transaction_test(test_ctx);

    // register_rpc_single_transaction_test(test_ctx);
    // register_rpc_multiple_transaction_test(test_ctx);
}

static void uart_init_tests(uart_test_ctx_t *test_ctx, rtos_uart_tx_t *rtos_uart_tx_ctx, rtos_uart_rx_t *rtos_uart_rx_ctx)
{
    memset(test_ctx, 0, sizeof(uart_test_ctx_t));
    test_ctx->rtos_uart_tx_ctx = rtos_uart_tx_ctx;
    test_ctx->rtos_uart_rx_ctx = rtos_uart_rx_ctx;

    test_ctx->cur_test = 0;
    test_ctx->test_cnt = UART_MAX_TESTS;

    register_uart_tests(test_ctx);
    configASSERT(test_ctx->test_cnt <= UART_MAX_TESTS);
}



int uart_device_tests(rtos_uart_tx_t *rtos_uart_tx_ctx, rtos_uart_rx_t *rtos_uart_rx_ctx)
{
    uart_test_ctx_t test_ctx;
    int res = 0;

    uart_printf("Init test context");
    uart_init_tests(&test_ctx, rtos_uart_tx_ctx, rtos_uart_rx_ctx);
    uart_printf("Test context init");

    uart_printf("Start devices");
    start_uart_devices(&test_ctx);
    uart_printf("Devices started");

    uart_printf("Start tests");
    res = run_uart_tests(&test_ctx);

    return res;
}
