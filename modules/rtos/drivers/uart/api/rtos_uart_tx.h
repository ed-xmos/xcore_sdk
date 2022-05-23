// Copyright 2022 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

#ifndef RTOS_UART_TX_H_
#define RTOS_UART_TX_H_

/**
 * This attribute must be specified on the RTOS UART tx call function
 * provided by the application to allow compiler stack calculation.
 */
#define RTOS_UART_TX_CALL_ATTR  __attribute__((fptrgroup("rtos_uart_tx_fptr_grp")))

/**
 * \addtogroup rtos_uart_tx_driver rtos_uart_tx_driver
 *
 * The public API for using the RTOS UART tx driver.
 * @{
 */

#include "uart.h"

#include "rtos_osal.h"

/**
 * Typedef to the RTOS UART tx driver instance struct.
 */
typedef struct rtos_uart_tx_struct rtos_uart_tx_t;

/**
 * Struct representing an RTOS UART tx driver instance.
 *
 * The members in this struct should not be accessed directly.
 */
struct rtos_uart_tx_struct {
    RTOS_UART_TX_CALL_ATTR void (*write)(rtos_uart_tx_t *, uint8_t buf[], size_t);
    uart_tx_t dev;
    rtos_osal_mutex_t lock;
};


/**
 * \addtogroup rtos_uart_tx_driver_core rtos_uart_tx_driver_core
 *
 * The core functions for using an RTOS UART tx driver instance after
 * it has been initialized and started. 
 * @{
 */

/**
 * Writes data to an UART instance.
 *
 * \param ctx             A pointer to the UART Tx driver instance to use.
 * \param buf             The buffer containing data to write.
 * \param n               The number of bytes to write.
 */
inline void rtos_uart_tx_write(
        rtos_uart_tx_t *ctx,
        uint8_t buf[],
        size_t n)
{
    ctx->write(ctx, buf, n);
}

/**
 * Initializes an RTOS I2C master driver instance.
 * This must only be called by the tile that owns the driver instance. It may be
 * called either before or after starting the RTOS, but must be called before calling
 * rtos_i2c_master_start() or any of the core I2C master driver functions with this instance.
 *
 * \param i2c_master_ctx      A pointer to the I2C master driver instance to initialize.
 * \param p_scl               The port containing SCL. This may be either the same as
 *                            or different than \p p_sda.
 * \param scl_bit_position    The bit number of the SCL line on the port \p p_scl.
 * \param scl_other_bits_mask A value that is ORed into the port value driven to \p p_scl
 *                            both when SCL is high and low. The bit representing SCL (as
 *                            well as SDA if they share the same port) must be set to 0.
 * \param p_sda               The port containing SDA. This may be either the same as
 *                            or different than \p p_scl.
 * \param sda_bit_position    The bit number of the SDA line on the port \p p_sda.
 * \param sda_other_bits_mask A value that is ORed into the port value driven to \p p_sda
 *                            both when SDA is high and low. The bit representing SDA (as
 *                            well as SCL if they share the same port) must be set to 0.
 * \param tmr                 This is unused and should be set to 0. This will be removed.
 * \param kbits_per_second    The speed of the I2C bus. The maximum value allowed is 400.
 */
void rtos_uart_tx_init(
        rtos_uart_tx_t *ctx,
        const port_t tx_port,
        const uint32_t baud_rate,
        const uint8_t num_data_bits,
        const uart_parity_t parity,
        const uint8_t stop_bits,
        hwtimer_t tmr);

/**
 * Starts an RTOS UART tx driver instance. This must only be called by the tile that
 * owns the driver instance. It may be called either before or after starting
 * the RTOS, but must be called before any of the core UART tx driver functions are
 * called with this instance.
 *
 * rtos_uart_tx_init() must be called on this UART tx driver instance prior to calling this.
 *
 * \param rtos_uart_tx_t A pointer to the UART tx driver instance to start.
 */
void rtos_uart_tx_start(
        rtos_uart_tx_t *ctx);


/**@}*/

#endif /* RTOS_I2C_MASTER_H_ */
