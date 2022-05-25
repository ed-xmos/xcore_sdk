// Copyright 2021-2022 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

/* System headers */
#include <platform.h>
#include <xs1.h>

/* FreeRTOS headers */
#include "FreeRTOS.h"
#include "queue.h"

/* Library headers */
#include "rtos_gpio.h"
#include "rtos_spi_master.h"
#include "rtos_uart_tx.h"
#include "rtos_uart_rx.h"

/* App headers */
#include "app_conf.h"
#include "board_init.h"
#include "rtos_test/rtos_test_utils.h"
#include "individual_tests/individual_tests.h"

static rtos_intertile_t intertile_ctx_s;
static rtos_spi_master_t spi_master_ctx_s;
static rtos_spi_master_device_t spi_master_device_ctx_s;
static rtos_spi_slave_t spi_slave_ctx_s;

static rtos_intertile_t *intertile_ctx = &intertile_ctx_s;
static rtos_spi_master_t *spi_master_ctx = &spi_master_ctx_s;
static rtos_spi_master_device_t *test_spi_device_ctx = &spi_master_device_ctx_s;
static rtos_spi_slave_t *spi_slave_ctx = &spi_slave_ctx_s;

#if ON_TILE(1)
static rtos_uart_tx_t rtos_uart_tx_ctx_s;
static rtos_uart_rx_t rtos_uart_rx_ctx_s;
static rtos_uart_tx_t *rtos_uart_tx_ctx = &rtos_uart_tx_ctx_s;
static rtos_uart_rx_t *rtos_uart_rx_ctx = &rtos_uart_rx_ctx_s;
#endif

chanend_t other_tile_c;

#define kernel_printf( FMT, ... )    module_printf("KERNEL", FMT, ##__VA_ARGS__)

void vApplicationMallocFailedHook( void )
{
    kernel_printf("Malloc Failed!");
    configASSERT(0);
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char* pcTaskName )
{
    kernel_printf("Stack Overflow! %s", pcTaskName);
    configASSERT(0);
}

void vApplicationDaemonTaskStartup(void *arg)
{
    rtos_intertile_start(intertile_ctx);

#if ON_TILE(1)
    // if (RUN_UART_TESTS) {
    //     if (uart_device_tests(rtos_uart_tx_ctx, rtos_uart_rx_ctx) != 0)
    //     {
    //         test_printf("FAIL UART");
    //     } else {
    //         test_printf("PASS UART");
    //     }
    // } else {
    //     test_printf("SKIP UART");
    // }
#endif

    if (RUN_SPI_TESTS) {
        if (spi_device_tests(spi_master_ctx, test_spi_device_ctx, spi_slave_ctx, other_tile_c) != 0)
        {
            test_printf("FAIL SPI");
        } else {
            test_printf("PASS SPI");
        }
    } else {
        test_printf("SKIP SPI");
    }

    _Exit(0);

    chanend_free(other_tile_c);
    vTaskDelete(NULL);
}


void stream_test_tx(void *arg){
    StreamBufferHandle_t xStreamBuffer = arg;

    uint8_t test_packet1[] = {10, 11, 12, 13};
    uint8_t test_packet2[] = {14, 15, 16, 17};
    uint8_t test_packet3[] = {18, 19, 20, 21};

    size_t num_sent = 0;
    num_sent = xStreamBufferSend( xStreamBuffer, test_packet1, sizeof(test_packet1), portMAX_DELAY); 
    test_printf("SENT 1: (%d)\n", num_sent);

    vTaskDelay(pdMS_TO_TICKS(2000));

    num_sent = xStreamBufferSend( xStreamBuffer, test_packet2, sizeof(test_packet2), portMAX_DELAY);
    test_printf("SENT 2: (%d)\n", num_sent);

    vTaskDelay(pdMS_TO_TICKS(2000));


    num_sent = xStreamBufferSend( xStreamBuffer, test_packet3, sizeof(test_packet3), portMAX_DELAY); 
    test_printf("SENT 3: (%d)\n", num_sent);

    vTaskDelete(NULL);
}

void stream_test_rx(void *arg){
    StreamBufferHandle_t xStreamBuffer = arg;
    uint8_t rx_packet1[6] = {0};
    size_t num_got = 0;
    num_got = xStreamBufferReceive(xStreamBuffer, rx_packet1, sizeof(rx_packet1), portMAX_DELAY); 
    test_printf("RECEIVED 1:(%d)  %d %d %d %d %d %d\n", num_got, rx_packet1[0], rx_packet1[1], rx_packet1[2], rx_packet1[3], rx_packet1[4], rx_packet1[5]);

    test_printf("Bytes available: %d\n", xStreamBufferBytesAvailable(xStreamBuffer));

    uint8_t rx_packet2[6] = {0};
    num_got = xStreamBufferReceive(xStreamBuffer, rx_packet2, sizeof(rx_packet2), portMAX_DELAY); 
    test_printf("RECEIVED 2:(%d)  %d %d %d %d %d %d\n", num_got, rx_packet2[0], rx_packet2[1], rx_packet2[2], rx_packet2[3], rx_packet2[4], rx_packet2[5]);

    vTaskDelete(NULL);
}


#if ON_TILE(0)
void main_tile0(chanend_t c0, chanend_t c1, chanend_t c2, chanend_t c3)
{
    (void) c0;
    //Devices get init'd here
    board_tile0_init(c1,
                     intertile_ctx,
                     spi_master_ctx,
                     test_spi_device_ctx);
    (void) c2;
    (void) c3;

    other_tile_c = c1;

    xTaskCreate((TaskFunction_t) vApplicationDaemonTaskStartup,
                "vApplicationDaemonTaskStartup",
                RTOS_THREAD_STACK_SIZE(vApplicationDaemonTaskStartup),
                NULL,
                appconfSTARTUP_TASK_PRIORITY,
                NULL);


    StreamBufferHandle_t xStreamBuffer = xStreamBufferCreate(256, 6);
    xTaskCreate((TaskFunction_t) stream_test_tx,
                "stream_test_tx",
                RTOS_THREAD_STACK_SIZE(stream_test_tx),
                xStreamBuffer,
                configMAX_PRIORITIES / 2,
                NULL);
    xTaskCreate((TaskFunction_t) stream_test_rx,
                "stream_test_rx",
                RTOS_THREAD_STACK_SIZE(stream_test_rx),
                xStreamBuffer,
                configMAX_PRIORITIES / 2,
                NULL);


    kernel_printf("Start scheduler");
    vTaskStartScheduler();

    return;
}
#endif /* ON_TILE(0) */

#if ON_TILE(1)
void main_tile1(chanend_t c0, chanend_t c1, chanend_t c2, chanend_t c3)
{
    //Devices get init'd here
    board_tile1_init(c0,
                     intertile_ctx,
                     spi_master_ctx,
                     test_spi_device_ctx,
                     spi_slave_ctx,
                     rtos_uart_tx_ctx,
                     rtos_uart_rx_ctx);
    (void) c1;
    (void) c2;
    (void) c3;

    other_tile_c = c0;

    xTaskCreate((TaskFunction_t) vApplicationDaemonTaskStartup,
                "vApplicationDaemonTaskStartup",
                RTOS_THREAD_STACK_SIZE(vApplicationDaemonTaskStartup),
                NULL,
                appconfSTARTUP_TASK_PRIORITY,
                NULL);

    kernel_printf("Start scheduler");
    vTaskStartScheduler();

    return;
}
#endif /* ON_TILE(1) */
