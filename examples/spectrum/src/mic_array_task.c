// Copyright 2022-2023 XMOS LIMITED.
// This Software is subject to the terms of the XCORE VocalFusion Licence.


// This file conatins the mic_array task

#include "mic_array_task.h"
#include "mic_array.h"
#include "app_conf.h"

#include <xcore/channel.h>


void mic_array_task(chanend_t c_mic_to_audio){

    ma_init();
    /*
     * ma_task() itself uses interrupts, and does re-enable them. However,
     * it appears to assume that KEDI is not set, therefore it is cleared here in
     * case this module is compiled with dual issue.
     */
    CLEAR_KEDI()


    /* Start endless loop */
    ma_task(c_mic_to_audio);
}
