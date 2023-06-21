// Copyright 2022-2023 XMOS LIMITED.
// This Software is subject to the terms of the XCORE VocalFusion Licence.

// This file contains the implementations of the DAC configuration steps such as which registers to write with which values
// Note there are currently two implementations because in I2C slave we init the DAC pre-RTOS

/* FreeRTOS headers */
#include "FreeRTOS.h"

/* App headers */
#include "xcore/port.h"
#include "rtos_i2c_master.h" // Includes "i2c.h" too
#include "platform/driver_instances.h"
#include "dac3101.h"


void dac3101_wait(uint32_t wait_ms)
{
    vTaskDelay(pdMS_TO_TICKS(wait_ms));
}

int dac3101_reg_write(uint8_t reg, uint8_t val)
{
    i2c_regop_res_t ret = rtos_i2c_master_reg_write(i2c_master_ctx, DAC3101_I2C_DEVICE_ADDR, reg, val);

    if (ret == I2C_REGOP_SUCCESS) {
        return 0;
    } else {
        return -1;
    }
}


void dac3101_codec_reset(void * args)
{
    // device_control_t *device_control_gpio_ctx = args;

    // write_gpo_pin(device_control_gpio_ctx, GPO_DAC_RST_N_PIN, 0);
    dac3101_wait(1);  /* From DS - The hardware reset pin (RESET) must be pulled low for at least 10ns */
    // write_gpo_pin(device_control_gpio_ctx, GPO_DAC_RST_N_PIN, 1);
    dac3101_wait(1); /* From DS - This initialization takes place within 1 ms after pulling the RESET signal high */
}
