// Copyright 2022 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

#ifndef RTOS_UART_RX_H_
#define RTOS_UART_RX_H_

/**
 * \addtogroup rtos_uart_rx_driver rtos_uart_rx_driver
 *
 * The public API for using the RTOS UART rx driver.
 * @{
 */

#include <xcore/channel_streaming.h>
#include "uart.h"

#include "rtos_osal.h"
#include "stream_buffer.h"

/**
 * The callback code bit positions and flag masks available for RTOS UART Rx.
 */
#define COMPLETE_CB_CODE       0
#define STARTED_CB_CODE        1
#define START_BIT_ERR_CB_CODE  2
#define PARITY_ERR_CB_CODE     3
#define FRAMING_ERR_CB_CODE    4
#define OVERRUN_ERR_CB_CODE    5

#define COMPLETE_CB_FLAG        (1 << COMPLETE_CB_CODE)
#define STARTED_CB_FLAG         (1 << STARTED_CB_CODE)
#define START_BIT_ERR_CB_FLAG   (1 << START_BIT_ERR_CB_CODE)
#define PARITY_ERR_CB_FLAG      (1 << PARITY_ERR_CB_CODE)
#define FRAMING_ERR_CB_FLAG     (1 << FRAMING_ERR_CB_CODE)
#define OVERRUN_ERR_CB_FLAG     (1 << OVERRUN_ERR_CB_CODE)

#if (START_BIT_ERR_CB_CODE != UART_START_BIT_ERROR_VAL)
#error Please align the HIL uart_callback_code_t with CB codes in rtos_uart_rx.c
#endif

#define RX_ALL_FLAGS (COMPLETE_CB_FLAG | STARTED_CB_FLAG | START_BIT_ERR_CB_FLAG | PARITY_ERR_CB_FLAG | FRAMING_ERR_CB_FLAG)
#define RX_ERROR_FLAGS (START_BIT_ERR_CB_FLAG | PARITY_ERR_CB_FLAG | FRAMING_ERR_CB_FLAG)


/**
 * The maximum number of bytes that a the RTOS UART rx driver can receive from a master
 * in a single write transaction before being read/emptied. This is not the same as 
 * app_byte_buffer_size which can be any size.
 */
#ifndef RTOS_UART_RX_BUF_LEN
#define RTOS_UART_RX_BUF_LEN 8
#endif

/**
 * This attribute must be specified on all RTOS UART rx callback functions
 * provided by the application to allow compiler stack calculation.
 */
#define RTOS_UART_RX_CALLBACK_ATTR __attribute__((fptrgroup("rtos_uart_rx_callback_fptr_grp")))

/**
 * This attribute must be specified on all RTOS UART rx callback functions
 * provided by the application to allow compiler stack calculation.
 */
#define RTOS_UART_RX_CALL_ATTR __attribute__((fptrgroup("rtos_uart_rx_call_fptr_grp")))

/**
 * Typedef to the RTOS UART rx driver instance struct.
 */
typedef struct rtos_uart_rx_struct rtos_uart_rx_t;

/**
 * Function pointer type for application provided RTOS UART rx start callback functions.
 *
 * This callback function is optionally (may be NULL) called by an UART rx driver's thread when it is first
 * started. This gives the application a chance to perform startup initialization from within the
 * driver's thread.
 *
 * \param ctx           A pointer to the associated UART rx driver instance.
 */

typedef void (*rtos_uart_rx_started_cb_t)(rtos_uart_rx_t *ctx);

/**
 * Function pointer type for application provided RTOS UART rx receive callback function.
 *
 * This callback functions are called when an UART rx driver instance has received data to a specified
 * depth. Please use the xStreamBufferReceive(rtos_uart_rx_ctx->isr_byte_buffer, ... to read the bytes.
 *
 * \param ctx           A pointer to the associated UART rx driver instance.
 */
typedef void (*rtos_uart_rx_complete_cb_t)(rtos_uart_rx_t *ctx);



/**
 * Function pointer type for application provided RTOS UART rx error callback functions.
 *
 * This callback function is optionally (may be NULL_ called when an UART rx driver instance experiences an error 
 * in reception. These error types are defined in uart.h of the underlying HIL driver but can be of the following
 * types for the RTOS rx:  UART_START_BIT_ERROR, UART_PARITY_ERROR, UART_FRAMING_ERROR, UART_OVERRUN_ERROR.
 * 
 *
 * \param ctx           A pointer to the associated UART rx driver instance.
 * \param err_flags     An 8b word containing error flags set during reception of last frame. 
 *                      See rtos_uart_rx.h for the bit field definitions.
 */
typedef void (*rtos_uart_rx_error_t)(rtos_uart_rx_t *ctx, uint8_t err_flags);

/**
 * Struct representing an RTOS UART rx driver instance.
 *
 * The members in this struct should not be accessed directly.
 */


struct rtos_uart_rx_struct {
    uart_rx_t dev;

    RTOS_UART_RX_CALL_ATTR void (*read)(rtos_uart_rx_t *, uint8_t buf[], size_t *num_bytes);

    void *app_data;

    RTOS_UART_RX_CALLBACK_ATTR rtos_uart_rx_started_cb_t rx_start_cb;
    RTOS_UART_RX_CALLBACK_ATTR rtos_uart_rx_complete_cb_t rx_complete_cb;
    RTOS_UART_RX_CALLBACK_ATTR rtos_uart_rx_error_t rx_error_cb;

    streaming_channel_t c;

    StreamBufferHandle_t isr_byte_buffer;
    StreamBufferHandle_t app_byte_buffer;
    size_t app_byte_buffer_size;
    size_t app_byte_buffer_fill_trigger;

    uint8_t cb_flags;
    rtos_osal_event_group_t events;
    rtos_osal_thread_t hil_thread;
    rtos_osal_thread_t app_thread;
};

/**
 * Initializes an RTOS UART slave driver instance.
 * This must only be called by the tile that owns the driver instance. It should be
 * called before starting the RTOS, and must be called before calling rtos_uart_rx_start().
 *
 * \param uart_rx_ctx A pointer to the UART rx driver instance to initialize.
 * \param io_core_mask  A bitmask representing the cores on which the low level I2C I/O thread
 *                      created by the driver is allowed to run. Bit 0 is core 0, bit 1 is core 1,
 *                      etc.
 * \param p_scl         The port containing SCL. This must be a 1-bit port and
 *                      different than \p p_sda.
 * \param p_sda         The port containing SDA. This must be a 1-bit port and
 *                      different than \p p_scl.
 * \param device_addr   The 7-bit address of the slave device.
 */
 
void rtos_uart_rx_init(
        rtos_uart_rx_t *uart_rx_ctx,
        uint32_t io_core_mask,
       
        port_t rx_port,
        uint32_t baud_rate,
        uint8_t data_bits,
        uart_parity_t parity,
        uint8_t stop_bits,
        hwtimer_t tmr
        );

/**
 * Starts an RTOS UART rx driver instance. This must only be called by the tile that
 * owns the driver instance. It must be called after starting the RTOS from an RTOS thread.
 *
 * rtos_uart_rx_init() must be called on this UART rx driver instance prior to calling this.
 *
 * \param uart_rx_ctx       A pointer to the UART rx driver instance to start.
 * \param app_data          A pointer to application specific data to pass to
 *                          the callback functions.
 * \param start             The callback function that is called when the driver's
 *                          thread starts. This is optional and may be NULL.
 * \param rx                The callback function to receive data from the bus master.
 * \param tx_start          The callback function to transmit data to the bus master.
 * \param tx_done           The callback function that is notified when transmits are
 *                          complete. This is optional and may be NULL.
 * \param interrupt_core_id The ID of the core on which to enable the I2C interrupt.
 * \param priority          The priority of the task that gets created by the driver to
 *                          call the callback functions.
 */
void rtos_uart_rx_start(
        rtos_uart_rx_t *uart_rx_ctx,
        void *app_data,
        rtos_uart_rx_started_cb_t start,
        rtos_uart_rx_complete_cb_t rx_complete,
        rtos_uart_rx_error_t error,
        unsigned interrupt_core_id,
        unsigned priority,

        size_t app_byte_buffer_size,
        size_t app_byte_buffer_fill_trigger);




/**@}*/

#endif /* RTOS_I2C_SLAVE_H_ */
