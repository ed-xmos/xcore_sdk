// Copyright 2022 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.
#pragma once

/** \file
 *  \brief API for SPI I/O
 */

#include <stdlib.h> /* for size_t */
#include <stdint.h>
#include <xcore/port.h>
#include <xcore/triggerable.h>
#include <xcore/hwtimer.h>
#include <xcore/interrupt.h>

#include "uart_util.h"

/**
 * \addtogroup hil_spi_master hil_spi_master
 *
 * The public API for using the HIL SPI master.
 * @{
 */

/**
 * Enum type representing the different options
 * for the SPI master sample delay.
 */
typedef enum uart_parity_t {
  UART_PARITY_NONE = 0,
  UART_PARITY_EVEN,
  UART_PARITY_ODD
} uart_parity_t;


typedef enum {
    UART_IDLE = 0,
    UART_START,
    UART_DATA,
    UART_PARITY,
    UART_STOP
} uart_state_t;


typedef enum {
    UART_RX_COMPLETE = 0x00,
    UART_TX_EMPTY,
    UART_START_BIT_ERROR,
    UART_PARITY_ERROR,
    UART_FRAMING_ERROR,
    UART_OVERRUN_ERROR,
    UART_UNDERRUN_ERROR,
} uart_callback_t;



/**
 * This attribute must be specified on all SPI callback functions
 * provided by the application.
 */
#define UART_CALLBACK_ATTR __attribute__((fptrgroup("uart_callback")))


/**
 * Struct to hold a UART Tx context.
 *
 * The members in this struct should not be accessed directly.
 */
typedef struct {
    uart_state_t state;
    port_t tx_port;
    uint32_t bit_time_ticks;
    uint32_t next_event_time_ticks;
    uart_parity_t parity;
    uint8_t num_data_bits; //These are ordered to be better packed
    uint8_t current_data_bit;
    uint8_t uart_data;
    uint8_t stop_bits;
    uint8_t current_stop_bit;
    UART_CALLBACK_ATTR void(*uart_callback_fptr)(uart_callback_t callback_info);
    hwtimer_t tmr;
    uart_buffer_t buffer;
} uart_tx_t;


typedef struct {
    uart_state_t state;
    port_t rx_port;
    uint32_t bit_time_ticks;
    uint32_t next_event_time_ticks;
    uart_parity_t parity;
    uint8_t num_data_bits; //These are ordered to be better packed
    uint8_t current_data_bit;
    uint8_t uart_data;
    uint8_t stop_bits;
    uint8_t current_stop_bit;
    UART_CALLBACK_ATTR void(*uart_callback_fptr)(uart_callback_t callback_info);
    hwtimer_t tmr;
    uart_buffer_t buffer;
} uart_rx_t;

/**
 * Initializes a SPI master I/O interface.
 *
 * \param spi         The spi_master_t context to initialize.
 * \param clock_block The clock block to use for the SPI master interface.
 * \param cs_port     The SPI interface's chip select port. This may be a multi-bit port.
 * \param sclk_port   The SPI interface's SCLK port. Must be a 1-bit port.
 * \param mosi_port   The SPI interface's MOSI port. Must be a 1-bit port.
 * \param miso_port   The SPI interface's MISO port. Must be a 1-bit port.
 */
void uart_tx_init(
        uart_tx_t *uart,
        port_t tx_port,
        uint32_t baud_rate,
        uint8_t data_bits,
        uart_parity_t parity,
        uint8_t stop_bits,

        hwtimer_t tmr,
        uint8_t *tx_buff,
        size_t buffer_size,
        void(*uart_callback_fptr)(uart_callback_t callback_info)
        );



void uart_tx_blocking_init(
        uart_tx_t *uart_cfg,
        port_t tx_port,
        uint32_t baud_rate,
        uint8_t num_data_bits,
        uart_parity_t parity,
        uint8_t stop_bits,
        hwtimer_t tmr);


/**
 * Transfers data to/from the specified SPI device. This may be called
 * multiple times during a single transaction.
 *
 * \param dev      The SPI device with which to transfer data.
 * \param data_out Buffer containing the data to send to the device.
 *                 May be NULL if no data needs to be sent.
 * \param data_in  Buffer to save the data received from the device.
 *                 May be NULL if the data received is not needed.
 * \param len      The length in bytes of the data to transfer. Both
 *                 buffers must be at least this large if not NULL.
 */
// void spi_master_transfer(
//         spi_master_device_t *dev,
//         uint8_t *data_out,
//         uint8_t *data_in,
//         size_t len);


void uart_tx(
        uart_tx_t *uart,
        uint8_t data);

/**
 * Enforces a minimum delay between the time this is called and
 * the next transfer. It must be called during a transaction.
 * It returns immediately.
 *
 * \param dev         The active SPI device.
 * \param delay_ticks The number of reference clock ticks to delay.
 */
// inline void spi_master_delay_before_next_transfer(
//         spi_master_device_t *dev,
//         uint32_t delay_ticks)
// {
//     spi_master_t *spi = dev->spi_master_ctx;

//     spi->delay_before_transfer = 1;

//     port_clear_trigger_time(spi->cs_port);

//     /* Assert CS now */
//     port_out(spi->cs_port, dev->cs_assert_val);
//     port_sync(spi->cs_port);

//     /*
//      * Assert CS again, scheduled for earliest time the
//      * next transfer is allowed to start.
//      */
//     if (delay_ticks >= SPI_MASTER_MINIMUM_DELAY) {
//         port_out_at_time(spi->cs_port, port_get_trigger_time(spi->cs_port) + delay_ticks, dev->cs_assert_val);
//     }
// }

/**
 * De-initializes the specified SPI master interface. This disables the
 * ports and clock block.
 *
 * \param spi The spi_master_t context to de-initialize.
 */
void uart_tx_deinit(
        uart_tx_t *uart);



void uart_rx_blocking_init(
        uart_rx_t *uart,
        port_t rx_port,
        uint32_t baud_rate,
        uint8_t data_bits,
        uart_parity_t parity,
        uint8_t stop_bits,

        hwtimer_t tmr,
        void(*uart_callback_fptr)(uart_callback_t callback_info)
        );



void uart_rx_init(
        uart_rx_t *uart,
        port_t rx_port,
        uint32_t baud_rate,
        uint8_t data_bits,
        uart_parity_t parity,
        uint8_t stop_bits,

        hwtimer_t tmr,
        uint8_t *rx_buff,
        size_t buffer_size,
        void(*uart_callback_fptr)(uart_callback_t callback_info)
        );

uint8_t uart_rx(uart_rx_t *uart);

void uart_rx_deinit(uart_rx_t *uart);



/**
 * Callback group representing callback events that can occur during the
 * operation of the SPI slave task. Must be initialized by the application
 * prior to passing it to one of the SPI slaves.
 */
#if 0
typedef struct {
    /** Pointer to the application's slave_transaction_started_t function to be called by the SPI device */
    SPI_CALLBACK_ATTR slave_transaction_started_t slave_transaction_started;

    /** Pointer to the application's slave_transaction_ended_t function to be called by the SPI device
     *  Note: The time spent in this callback must be less than the minimum CS deassertion to reassertion
     *  time.  If this is violated the first word of the proceeding transaction will be lost.
     */
    SPI_CALLBACK_ATTR slave_transaction_ended_t slave_transaction_ended;

    /** Pointer to application specific data which is passed to each callback. */
    void *app_data;
} spi_slave_callback_group_t;
#endif


/**@}*/ // END: addtogroup hil_spi_slave
