// Copyright 2022 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

#define DEBUG_UNIT RTOS_UART
#define DEBUG_PRINT_ENABLE_RTOS_UART 1

#include "rtos_uart_tx.h"

__attribute__((fptrgroup("rtos_uart_tx_fptr_grp")))
static void uart_tx_local_send(
        rtos_uart_tx_t *ctx,
        uint8_t buff[],
        size_t n)
{
    rtos_osal_mutex_get(&ctx->lock, RTOS_OSAL_WAIT_FOREVER);


    for(int i = 0; i < n; i++){
        uart_tx(&ctx->ctx, buff[i]);
    }

    rtos_osal_mutex_put(&ctx->lock);
}


void rtos_uart_tx_start(
        rtos_uart_tx_t *uart_tx_ctx)
{
    rtos_osal_mutex_create(&uart_tx_ctx->lock, "uart_tx_lock", RTOS_OSAL_RECURSIVE);

    // if (i2c_master_ctx->rpc_config != NULL && i2c_master_ctx->rpc_config->rpc_host_start != NULL) {
    //     i2c_master_ctx->rpc_config->rpc_host_start(i2c_master_ctx->rpc_config);
    // }
}

void rtos_uart_tx_init(
        rtos_uart_tx_t *ctx,
        const port_t tx_port,
        const uint32_t baud_rate,
        const uint8_t num_data_bits,
        const uart_parity_t parity,
        const uint8_t stop_bits,
        hwtimer_t tmr){
    //uart init
    uart_tx_blocking_init(
            &ctx->ctx,
            tx_port,
            baud_rate,
            num_data_bits,
            parity,
            stop_bits,
            tmr);

    // i2c_master_ctx->rpc_config = NULL;
    ctx->send = uart_tx_local_send;
}
