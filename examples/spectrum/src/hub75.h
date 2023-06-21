#include <stdio.h>
#include <stdint.h>
#include <xcore/port.h>
#include <xcore/hwtimer.h>
#include <xcore/parallel.h>
#include <xs1.h>
#include <string.h>

#define HUB75_LINE_LENGTH   64
#define HUB75_COLUMN_HEIGHT 32
#define HUB75_DELAY         0
#define HUB75_OE_DELAY      (10 * 4000)

#define HUB75_OE    (1 << 7)

extern uint8_t frame[3][HUB75_COLUMN_HEIGHT][HUB75_LINE_LENGTH];

DECLARE_JOB(hub75_driver, (void));
void hub75_driver(void);

void write_char(char c, int x, int y);

void write_string(char str[], int x, int y);