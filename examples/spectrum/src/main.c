#include <stdio.h>
#include <xcore/parallel.h>
#include "platform_init.h"
#include "mic_array.h"
#include "mic_array_vanilla.h"
#include "hub75.h"

void clear_screen(void){
    memset(frame, 0, sizeof(frame));
}

void horiz_line(unsigned x_start, unsigned y, unsigned len){
    uint8_t *start_addr = &frame[0][y][x_start];
    uint8_t *end_addr = &frame[0][y][x_start + len];
    memset(start_addr, 1, end_addr - start_addr);
}

DECLARE_JOB(test, (chanend_t));
void test(chanend_t c_samp){
    frame[0][0][0] = 1;
    frame[1][31][0] = 1;
    frame[1][0][63] = 1;
    frame[2][31][63] = 1;

    // write_char('X', 10, 10);
    write_string("Hello wrld", 0, 2);



    while(1){
        int32_t samp = chan_in_word(c_samp);
        clear_screen();

        unsigned val = abs(samp) >> 13;
        int y = HUB75_COLUMN_HEIGHT - val - 1;
        if(y < 0){
            y = 0;
        }

        horiz_line(0, y, 5);
        printf("ma rx: %ld , y: %u\n", samp, y);
    }

}


void main_tile0(chanend_t c0, chanend_t c1, chanend_t c2, chanend_t c3){
    printf("Hellord 0\n");

    PAR_JOBS ( 
        PJOB(hub75_driver,()),
        PJOB(test, (c1))
        );
}

DECLARE_JOB(ma_servicer, (chanend_t, chanend_t));
void ma_servicer(chanend_t c_ma, chanend_t c_samp){
    int32_t ma_frame[appconfMIC_COUNT][appconfAUDIO_FRAME_LENGTH];
    while(1){
        ma_frame_rx((int32_t *) ma_frame, c_ma, appconfMIC_COUNT, appconfAUDIO_FRAME_LENGTH);
        chan_out_word(c_samp, ma_frame[0][0]);
    }
}


void main_tile1(chanend_t c0, chanend_t c1, chanend_t c2, chanend_t c3){
    printf("Hellord 1\n");
 
    channel_t c_ma = chan_alloc();

    app_pll_init();
    ma_vanilla_init();

    PAR_JOBS (
        PJOB(ma_vanilla_task, (c_ma.end_a)),
        PJOB(ma_servicer, (c_ma.end_b, c0))
        );
    printf("Exit 1\n");

 }