// Copyright 2022 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

#define DEBUG_UNIT RTOS_I2C

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

// __attribute__((fptrgroup("rtos_i2c_master_read_fptr_grp")))
// static i2c_res_t i2c_master_local_read(
//         rtos_i2c_master_t *ctx,
//         uint8_t device_addr,
//         uint8_t buf[],
//         size_t n,
//         int send_stop_bit)
// {
//     i2c_res_t res;

//     rtos_osal_mutex_get(&ctx->lock, RTOS_OSAL_WAIT_FOREVER);

//     res = i2c_master_read(
//                           &ctx->ctx,
//                           device_addr,
//                           buf,
//                           n,
//                           send_stop_bit);

//     rtos_osal_mutex_put(&ctx->lock);

//     return res;
// }

// __attribute__((fptrgroup("rtos_i2c_master_stop_bit_send_fptr_grp")))
// static void i2c_master_local_stop_bit_send(
//         rtos_i2c_master_t *ctx)
// {
//     rtos_osal_mutex_get(&ctx->lock, RTOS_OSAL_WAIT_FOREVER);
//     i2c_master_stop_bit_send(&ctx->ctx);
//     rtos_osal_mutex_put(&ctx->lock);
// }

// __attribute__((fptrgroup("rtos_i2c_master_reg_write_fptr_grp")))
// static i2c_regop_res_t i2c_master_local_reg_write(
//         rtos_i2c_master_t *ctx,
//         uint8_t device_addr,
//         uint8_t reg_addr,
//         uint8_t data)
// {
//     i2c_regop_res_t reg_res;
//     i2c_res_t res;
//     size_t num_bytes_sent = 0;
//     uint8_t buf[2];

//     buf[0] = reg_addr;
//     buf[1] = data;

//     res = i2c_master_local_write(ctx, device_addr, buf, 2, &num_bytes_sent, 1);

//     if (res == I2C_ACK) {
//         if (num_bytes_sent == 0) {
//             reg_res = I2C_REGOP_DEVICE_NACK;
//         } else if (num_bytes_sent < 2) {
//             reg_res = I2C_REGOP_INCOMPLETE;
//         } else {
//             reg_res = I2C_REGOP_SUCCESS;
//         }
//     } else {
//         reg_res = I2C_REGOP_DEVICE_NACK;
//     }

//     return reg_res;
// }

// __attribute__((fptrgroup("rtos_i2c_master_reg_read_fptr_grp")))
// static i2c_regop_res_t  i2c_master_local_reg_read(
//         rtos_i2c_master_t *ctx,
//         uint8_t device_addr,
//         uint8_t reg_addr,
//         uint8_t *data)
// {
//     i2c_regop_res_t reg_res;
//     i2c_res_t res;
//     size_t num_bytes_sent = 0;

//     rtos_osal_mutex_get(&ctx->lock, RTOS_OSAL_WAIT_FOREVER);

//     res = i2c_master_local_write(ctx, device_addr, &reg_addr, 1, &num_bytes_sent, 0);

//     if (res == I2C_ACK) {
//         if (num_bytes_sent == 0) {
//             reg_res = I2C_REGOP_DEVICE_NACK;
//         } else {
//             reg_res = I2C_REGOP_SUCCESS;
//         }
//     } else {
//         reg_res = I2C_REGOP_DEVICE_NACK;
//     }

//     if (reg_res == I2C_REGOP_SUCCESS) {
//         res = i2c_master_local_read(ctx, device_addr, data, 1, 1);

//         if (res == I2C_ACK) {
//             reg_res = I2C_REGOP_SUCCESS;
//         } else {
//             reg_res = I2C_REGOP_DEVICE_NACK;
//         }
//     }

//     rtos_osal_mutex_put(&ctx->lock);

//     return reg_res;
// }

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
