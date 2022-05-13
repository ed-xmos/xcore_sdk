// Copyright 2019-2022 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

/* System headers */
#include <platform.h>
#include <xs1.h>

/* FreeRTOS headers */
#include "FreeRTOS.h"
#include "queue.h"

/* Library headers */
#include "fs_support.h"

/* App headers */
#include "app_conf.h"
#include "platform/platform_init.h"
#include "platform/driver_instances.h"
#include "mem_analysis/mem_analysis.h"
#include "example_pipeline/example_pipeline.h"
#include "filesystem/filesystem_demo.h"
#include "gpio_ctrl/gpio_ctrl.h"

// for uart_demo
#include "task.h"
// #include "rtos_uart_tx.h"


void uart_demo(void)
{
    uint32_t status;
    // TimerHandle_t volume_up_timer;

    rtos_printf("uart_demo\n");

   
    // const rtos_gpio_port_id_t button_port = rtos_gpio_port(PORT_BUTTONS);
   
    // rtos_printf("enable led port %d\n", button_port);
    // rtos_gpio_port_enable(gpio_ctx_t0, led_port);
 
    // rtos_printf("enable button isr\n");
    // rtos_gpio_isr_callback_set(gpio_ctx_t0, button_port, button_callback, xTaskGetCurrentTaskHandle());
    // rtos_gpio_interrupt_enable(gpio_ctx_t0, button_port);

    // rtos_printf("enable button timers\n");
    // volume_up_timer = xTimerCreate(
    //                         "vol_up",
    //                         pdMS_TO_TICKS(appconfGPIO_VOLUME_RAPID_FIRE_MS),
    //                         pdTRUE,
    //                         NULL,
    //                         vVolumeUpCallback );

    for (;;) {

        xTaskNotifyWait(
                0x00000000UL,    /* Don't clear notification bits on entry */
                0xFFFFFFFFUL,    /* Reset full notification value on exit */
                &status,         /* Pass out notification value into status */
                1000 ); /* Wait indefinitely until next notification */
                // portMAX_DELAY ); /* Wait indefinitely until next notification */

        rtos_printf("uart_demo loop\n");


        // buttons_val = rtos_gpio_port_in(gpio_ctx_t0, button_port);
        // buttonA = ( buttons_val >> 0 ) & 0x01;
        // buttonB = ( buttons_val >> 1 ) & 0x01;

        // /* Turn on LEDS based on buttons */
        // rtos_gpio_port_out(gpio_ctx_t0, led_port, buttons_val);

        //  Adjust volume based on LEDs 
        // if( buttonA == 0 )   /* Up */
        // {
        //     xTimerStart( volume_up_timer, 0 );
        //     volume_up();
        //     // rtos_printf("volume up start\n");
        // }
        // else
        // {
        //     xTimerStop( volume_up_timer, 0 );
        // }
    }
}

void uart_demo_create(UBaseType_t priority)
{
    xTaskCreate((TaskFunction_t) uart_demo,
                "uart_demo",
                RTOS_THREAD_STACK_SIZE(uart_demo),
                NULL,
                priority,
                NULL);
}



void vApplicationMallocFailedHook( void )
{
    rtos_printf("Malloc Failed on tile %d!\n", THIS_XCORE_TILE);
    for(;;);
}

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
    rtos_printf("\nStack Overflow!!! %d %s!\n", THIS_XCORE_TILE, pcTaskName);
    configASSERT(0);
}

void startup_task(void *arg)
{
    rtos_printf("Startup task running from tile %d on core %d\n", THIS_XCORE_TILE, portGET_CORE_ID());

    platform_start();

#if ON_TILE(0)
    /* Initialize filesystem  */
    rtos_fatfs_init(qspi_flash_ctx);

    /* Create the filesystem demol task */
    filesystem_demo_create(appconfFILESYSTEM_DEMO_TASK_PRIORITY);

    uart_demo_create(appconfFILESYSTEM_DEMO_TASK_PRIORITY);
#endif

#if ON_TILE(1)
    /* Create the gpio control task */
    gpio_ctrl_create(appconfGPIO_TASK_PRIORITY);

    /* Create audio pipeline */
    example_pipeline_init(appconfAUDIO_PIPELINE_TASK_PRIORITY);
#endif

	for (;;) {
		rtos_printf("Tile[%d]:\n\tMinimum heap free: %d\n\tCurrent heap free: %d\n", THIS_XCORE_TILE, xPortGetMinimumEverFreeHeapSize(), xPortGetFreeHeapSize());
		vTaskDelay(pdMS_TO_TICKS(5000));
	}
}

static void tile_common_init(chanend_t c)
{
    platform_init(c);
    chanend_free(c);

    xTaskCreate((TaskFunction_t) startup_task,
                "startup_task",
                RTOS_THREAD_STACK_SIZE(startup_task),
                NULL,
                appconfSTARTUP_TASK_PRIORITY,
                NULL);

    rtos_printf("start scheduler on tile %d\n", THIS_XCORE_TILE);
    vTaskStartScheduler();
}

#if ON_TILE(0)
void main_tile0(chanend_t c0, chanend_t c1, chanend_t c2, chanend_t c3) {
    (void)c0;
    (void)c2;
    (void)c3;

    tile_common_init(c1);
}
#endif

#if ON_TILE(1)
void main_tile1(chanend_t c0, chanend_t c1, chanend_t c2, chanend_t c3) {
    (void)c1;
    (void)c2;
    (void)c3;

    tile_common_init(c0);
}
#endif
