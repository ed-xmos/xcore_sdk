// Copyright 2022 XMOS LIMITED.
// This Software is subject to the terms of the XCORE VocalFusion Licence.


#ifndef PLATFORM_CONF_H_
#define PLATFORM_CONF_H_

/*
 * Board support package for XVF3600EVK
 */

#if __has_include("app_conf.h")
#include "app_conf.h"
#endif /* __has_include("app_conf.h") */

/*****************************************/
/* Intertile Communication Configuration */
/*****************************************/

/*****************************************/
/*  I/O and interrupt cores for Tile 0   */
/*****************************************/

#define I2C_TILE_NO     0

// Assuming we only ever have I2C or SPI, not both.
// #define appconfI2C_IO_CORE                      1 /* Must be kept off core 0 with the RTOS tick ISR */
// #define appconfSPI_IO_CORE                     appconfI2C_IO_CORE /* Must be kept off core 0 with the RTOS tick ISR. Must be kept off appconfI2C_IO_CORE since i2c hil task is non preemptable */

// #define appconfI2C_ISR_CORE                     2 /* Must be kept off core 0 with the RTOS tick ISR. Must be kept off appconfI2C_IO_CORE since i2c hil task is non preemptable */
// #define appconfSPI_ISR_CORE                     appconfI2C_ISR_CORE /* Must be kept off core 0 with the RTOS tick ISR. Must be kept off appconfI2C_IO_CORE since i2c hil task is non preemptable */
// #define GPO_PWM_ISR_CORE                        appconfI2C_ISR_CORE

#define I2C_SLAVE_ADDR       0x2C

#define SPI_TILE_NO 0
#define SPI_SLAVE_CPOL 0
#define SPI_SLAVE_CPHA 0

#ifndef appconfI2C_MASTER_RPC_PORT
#define appconfI2C_MASTER_RPC_PORT 10
#endif /* appconfI2C_MASTER_RPC_PORT */

#ifndef appconfI2C_MASTER_RPC_PRIORITY
#define appconfI2C_MASTER_RPC_PRIORITY (configMAX_PRIORITIES/2)
#endif /* appconfI2C_MASTER_RPC_PRIORITY */

#ifndef appconfGPIO_T0_RPC_PORT
#define appconfGPIO_T0_RPC_PORT 11
#endif /* appconfGPIO_T0_RPC_PORT */

#ifndef appconfGPIO_T1_RPC_PORT
#define appconfGPIO_T1_RPC_PORT 12
#endif /* appconfGPIO_T1_RPC_PORT */

#ifndef appconfGPIO_RPC_PRIORITY
#define appconfGPIO_RPC_PRIORITY (configMAX_PRIORITIES/2)
#endif /* appconfGPIO_RPC_PRIORITY */


#ifndef appconfQSPI_FLASH_TASK_PRIORITY
#define appconfQSPI_FLASH_TASK_PRIORITY          ( configMAX_PRIORITIES - 1 )
#endif /* appconfQSPI_FLASH_TASK_PRIORITY */

/*****************************************/
/*  I/O and interrupt cores for Tile 1   */
/*****************************************/

/*****************************************/
/*  I/O Task Priorities                  */
/*****************************************/

#endif /* PLATFORM_CONF_H_ */
