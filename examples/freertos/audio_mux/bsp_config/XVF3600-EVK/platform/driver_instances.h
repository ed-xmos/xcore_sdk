// Copyright 2022 XMOS LIMITED.
// This Software is subject to the terms of the XCORE VocalFusion Licence.


#ifndef DRIVER_INSTANCES_H_
#define DRIVER_INSTANCES_H_

#include "rtos_intertile.h"
#include "rtos_i2c_master.h"
#include "rtos_i2c_slave.h"
#include "rtos_spi_slave.h"
#include "rtos_gpio.h"

/* Driver instances */
extern rtos_intertile_t *intertile_ctx;
extern rtos_i2c_master_t *i2c_master_ctx;
extern rtos_i2c_slave_t *i2c_slave_ctx;
extern rtos_spi_slave_t *spi_slave_ctx;
extern rtos_gpio_t *gpio_ctx_t0;
extern rtos_gpio_t *gpio_ctx_t1;


#endif /* DRIVER_INSTANCES_H_ */
