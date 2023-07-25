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

#define HUB75_OE            (1 << 7)

typedef uint8_t frame_t[3][HUB75_COLUMN_HEIGHT][HUB75_LINE_LENGTH];

typedef enum colour_t{
    RED=0,
    GRN=1,
    BLUE=2
} colour_t;


DECLARE_JOB(hub75_driver, (void));
void hub75_driver(void);

void clear_screen(frame_t *frame);
void horiz_line(frame_t *frame, unsigned x_start, unsigned y, unsigned len, colour_t colour);
void vert_line(frame_t *frame, unsigned x, unsigned y_start, unsigned len, colour_t colour);
void write_char(frame_t *frame, char c, int x, int y);
void write_string(frame_t *frame, char str[], int x, int y);
void flip(frame_t *new_frame);
