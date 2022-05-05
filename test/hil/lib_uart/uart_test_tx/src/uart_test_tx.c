// Copyright 2022 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.
#include <xs1.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <xcore/parallel.h>
#include <xcore/port.h>
#include <xcore/hwtimer.h>
#include <xcore/triggerable.h>
#include <xcore/interrupt.h>
#include <xcore/interrupt_wrappers.h>
#include "uart.h"

#define SETSR(c) asm volatile("setsr %0" : : "n"(c));

port_t p_uart_tx = XS1_PORT_1A;

DECLARE_JOB(test, (void));

void test() {
    uart_tx_t uart;
    hwtimer_t tmr = hwtimer_alloc();

    uart_tx_blocking_init(&uart, p_uart_tx, 921600, 8, UART_PARITY_NONE, 1, tmr);

    for(char b = 0x00; b <= 0x7f; b++){
        uart_tx(&uart, b);
    }

    uart_tx_deinit(&uart);

    hwtimer_free(tmr);
    exit(0);
}

DECLARE_JOB(burn, (void));

void burn(void) {
    SETSR(XS1_SR_QUEUE_MASK | XS1_SR_FAST_MASK);
    for(;;);
}

int main(void) {
    PAR_JOBS (
        PJOB(test, ()),
        PJOB(burn, ()),
        PJOB(burn, ()),
        PJOB(burn, ()),
        PJOB(burn, ()),
        PJOB(burn, ()),
        PJOB(burn, ()),
        PJOB(burn, ())
    );
    return 0;
}