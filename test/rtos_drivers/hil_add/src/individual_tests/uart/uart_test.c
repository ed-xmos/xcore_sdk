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
void rtos_uart_rx_started(rtos_uart_rx_t *ctx){
    uart_printf("rtos_uart_rx_started_cb_t\n");
}


RTOS_UART_RX_CALLBACK_ATTR
void rtos_uart_rx_error(rtos_uart_rx_t *ctx, uint8_t err_flags){
    uart_printf("rtos_uart_rx_error\n");
    uart_callback_code_t cb_code = ctx->dev.cb_code;
    if(cb_code & UR_START_BIT_ERR_CB_FLAG){
        uart_printf("UART_START_BIT_ERROR\n");
    }
    if(cb_code & UR_PARITY_ERR_CB_FLAG){
        uart_printf("UART_PARITY_ERROR\n");
    }
    if(cb_code & UR_FRAMING_ERR_CB_FLAG){
        uart_printf("UART_FRAMING_ERROR\n");
    }
    if(cb_code & UR_OVERRUN_ERR_CB_FLAG){
        uart_printf("UR_OVERRUN_ERR_CB_CODE\n");
    }

    if(cb_code & ~ RX_ERROR_FLAGS){
        uart_printf("UNKNOWN ERROR FLAG SET: 0x%x (THIS SHOULD NEVER HAPPEN)\n", cb_code);
    }
}

RTOS_UART_RX_CALLBACK_ATTR
void rtos_uart_rx_complete(rtos_uart_rx_t *ctx){
    // uart_printf("UART_RX_COMPLETE\n");
   
}

static int run_uart_tests(uart_test_ctx_t *test_ctx)
{
    int retval = 0;

    do
    {
        uint8_t tx_buff[] = {0xed, 0x00, 0x77, 0xed, 0x00, 0x77, 0xed, 0x00, 0x55, 0x55, 0x55, 0x55};
        rtos_uart_tx_write(test_ctx->rtos_uart_tx_ctx, tx_buff, sizeof(tx_buff));
    
        //Tx will not return until the last stop bit has finished

        uint8_t rx_buff[sizeof(tx_buff)] = {0};
        memset(rx_buff, 0x11, sizeof(rx_buff));

        size_t num_read_tot = 0;
        size_t num_timeouts = 0;
        while(num_read_tot < sizeof(rx_buff) && num_timeouts == 0){
            size_t num_rx = xStreamBufferReceive(test_ctx->rtos_uart_rx_ctx->app_byte_buffer,
                                                &rx_buff[num_read_tot],
                                                sizeof(rx_buff),
                                                pdMS_TO_TICKS(100));
            num_read_tot += num_rx;
            num_timeouts += (num_rx == 0);
        }

        int length_same = (num_read_tot == sizeof(tx_buff));        
        int array_different = memcmp(tx_buff, rx_buff, sizeof(tx_buff));
        uart_printf("uart loopback result len: %s, contents: %s", length_same ? "PASS" : "FAIL", array_different ? "FAIL" : "PASS");
        if(!length_same){
            uart_printf("len expected: %d, actual: %d", sizeof(tx_buff), num_read_tot);
            retval = -1;
        }
        if(array_different){
            for(int i = 0; i < sizeof(tx_buff); i++){
                uart_printf("Rx byte %d: 0x%x (0x%x)", i, rx_buff[i], tx_buff[i]);    
            }
            retval = -1;
        }

    } while (test_ctx->cur_test++ < test_ctx->test_cnt);

    return retval;
}

static void start_uart_devices(uart_test_ctx_t *test_ctx)
{
    void *app_data = NULL;

    uart_printf("RX start");
    rtos_uart_rx_start(
        test_ctx->rtos_uart_rx_ctx,
        app_data,
        rtos_uart_rx_started,
        rtos_uart_rx_complete,
        rtos_uart_rx_error,
        (1 << UART_RX_ISR_CORE),
        appconfSTARTUP_TASK_PRIORITY,
        128 // Big enough to hold tx_buff[]
        );

    uart_printf("TX start");
    rtos_uart_tx_start(test_ctx->rtos_uart_tx_ctx);

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
