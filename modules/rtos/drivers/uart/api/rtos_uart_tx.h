// Copyright 2022 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

#ifndef RTOS_UART_TX_H_
#define RTOS_UART_TX_H_


#define RTOS_UART_TX_CALLBACK_ATTR  __attribute__((fptrgroup("rtos_uart_tx_fptr_grp")))

/**
 * \addtogroup rtos_i2c_master_driver rtos_i2c_master_driver
 *
 * The public API for using the RTOS I2C master driver.
 * @{
 */

#include "uart.h"

#include "rtos_osal.h"
// #include "rtos_driver_rpc.h"

/**
 * Typedef to the RTOS I2C master driver instance struct.
 */
typedef struct rtos_uart_tx_struct rtos_uart_tx_t;

/**
 * Struct representing an RTOS I2C master driver instance.
 *
 * The members in this struct should not be accessed directly.
 */
struct rtos_uart_tx_struct {
    // rtos_driver_rpc_t *rpc_config;
    
    RTOS_UART_TX_CALLBACK_ATTR void (*send)(rtos_uart_tx_t *, uint8_t buf[], size_t);

    uart_tx_t ctx;

    rtos_osal_mutex_t lock;
};

// #include "rtos_i2c_master_rpc.h"

/**
 * \addtogroup rtos_i2c_master_driver_core rtos_i2c_master_driver_core
 *
 * The core functions for using an RTOS I2C master driver instance after
 * it has been initialized and started. These functions may be used
 * by both the host and any client tiles that RPC has been enabled for.
 * @{
 */

/**
 * Writes data to an I2C bus as a master.
 *
 * \param ctx             A pointer to the I2C master driver instance to use.
 * \param device_addr     The address of the device to write to.
 * \param buf             The buffer containing data to write.
 * \param n               The number of bytes to write.
 * \param num_bytes_sent  The function will set this value to the
 *                        number of bytes actually sent. On success, this
 *                        will be equal to ``n`` but it will be less if the
 *                        slave sends an early NACK on the bus and the
 *                        transaction fails.
 * \param send_stop_bit   If this is non-zero then a stop bit
 *                        will be sent on the bus after the transaction.
 *                        This is usually required for normal operation. If
 *                        this parameter is zero then no stop bit will
 *                        be omitted. In this case, no other task can use
 *                        the component until a stop bit has been sent.
 *
 * \retval               ``I2C_ACK`` if the write was acknowledged by the device.
 * \retval               ``I2C_NACK``otherwise.
 */
inline void rtos_uart_tx(
        rtos_uart_tx_t *ctx,
        uint8_t buf[],
        size_t n)
{
    ctx->send(ctx, buf, n);
}


/**
 * Starts an RTOS I2C master driver instance. This must only be called by the tile that
 * owns the driver instance. It may be called either before or after starting
 * the RTOS, but must be called before any of the core I2C master driver functions are
 * called with this instance.
 *
 * rtos_i2c_master_init() must be called on this I2C master driver instance prior to calling this.
 *
 * \param i2c_master_ctx A pointer to the I2C master driver instance to start.
 */
void rtos_uart_tx_start(
        rtos_uart_tx_t *ctx);

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

/**@}*/

#endif /* RTOS_I2C_MASTER_H_ */
