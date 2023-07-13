#include <stdio.h>
#include <stdlib.h>
#include <xcore/parallel.h>
#include <xcore/hwtimer.h>
#include "platform_init.h"
#include "mic_array.h"
// #include "mic_array_vanilla.h"
#include "hub75.h"
#include "vnr_features_api.h"
#include "app_conf.h"
#include "mic_array_task.h"

#if VNR_FRAME_ADVANCE != appconfAUDIO_FRAME_LENGTH
#error VNR_FRAME_ADVANCE != appconfAUDIO_FRAME_LENGTH
#endif

#if VNR_MEL_FILTERS != HUB75_LINE_LENGTH
#error VNR_MEL_FILTERS != HUB75_LINE_LENGTH
#endif



void clear_screen(frame_t *frame){
    memset(frame, 0, sizeof(frame_t));
}

void horiz_line(frame_t *frame, unsigned x_start, unsigned y, unsigned len, colour_t colour){
    uint8_t *start_addr = &(*frame)[colour][y][x_start];
    uint8_t *end_addr = &(*frame)[colour][y][x_start + len];
    memset(start_addr, 1, end_addr - start_addr);
}

void vert_line(frame_t *frame, unsigned x, unsigned y_start, unsigned len, colour_t colour){
    uint8_t *start_addr = &(*frame)[colour][y_start][x];
    for(int i = 0; i < len; i++){
        *start_addr = 1;
        start_addr += HUB75_LINE_LENGTH;
    }
}

DECLARE_JOB(test, (chanend_t));
void test(chanend_t c_samp){
    // frame[0][0][0] = 1;
    // frame[1][31][0] = 1;
    // frame[1][0][63] = 1;
    // frame[2][31][63] = 1;

    frame_t frames[2] = {{{{0}}}};
    unsigned frame_idx = 0;

    // write_char('X', 10, 10);
    write_string(&frames[frame_idx], "Hello wrld", 0, 2);
    flip(&frames[frame_idx]);

    unsigned y_peaks[VNR_MEL_FILTERS];
    for(int i = 0; i < VNR_MEL_FILTERS; i++) y_peaks[i] = 0;

    // hwtimer_t t_timing = hwtimer_alloc();
    uint32_t t0 = get_reference_time();
    uint32_t counter = 0;

    while(1){
        frame_t *write_frame = &frames[frame_idx];

        int32_t features[VNR_MEL_FILTERS];

        chan_in_buf_word(c_samp, (uint32_t*)features, VNR_MEL_FILTERS);

        clear_screen(write_frame);

        for(int i = 0; i < HUB75_LINE_LENGTH; i++){
            int32_t samp = (features[HUB75_LINE_LENGTH - i - 1] >> 23) + 50;

            unsigned val = samp > 0 ? samp : 0;
            int y = val;
            if(y > HUB75_COLUMN_HEIGHT - 1){
                y = HUB75_COLUMN_HEIGHT - 1;
            }

            if(counter % 2 == 0){
                if(y_peaks[i] > 0) y_peaks[i] -= 1;
            }

            if(y > y_peaks[i]){
                y_peaks[i] = y;
            }

            // horiz_line(i, y, 1);
            vert_line(write_frame, i, 0, y, GRN);
            vert_line(write_frame, i, y_peaks[i], 1, RED);

            vert_line(write_frame, 0,0,1, BLUE);
            // printf("%d %d\n", i, y);
        }

        flip(write_frame);
        frame_idx ^= 1;
        // printf("ft samp: %ld , y: %u\n", samp, y);

        counter += 1;
        uint32_t t1 = get_reference_time();
        if(t1 - t0 >= XS1_TIMER_HZ){
            t0 += XS1_TIMER_HZ;
            printf("rend: %lu\n", counter);
            counter = 0;
        }
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
    
    vnr_feature_state_t vnr_feature_state;
    vnr_input_state_t vnr_input_state;

    vnr_input_state_init(&vnr_input_state);

    while(1){
        ma_frame_rx((int32_t *) ma_frame, c_ma, appconfMIC_COUNT, appconfAUDIO_FRAME_LENGTH);

        // int32_t new_frame[VNR_FRAME_ADVANCE];
        int32_t *new_frame = ma_frame[0];

        complex_s32_t DWORD_ALIGNED input_frame[VNR_FD_FRAME_LENGTH];
        
        bfp_complex_s32_t X;
        vnr_form_input_frame(&vnr_input_state, &X, input_frame, new_frame);

        bfp_s32_t feature_patch;
        int32_t feature_patch_data[VNR_PATCH_WIDTH*VNR_MEL_FILTERS];
        vnr_extract_features(&vnr_feature_state, &feature_patch, feature_patch_data, &X);

        int32_t *features = vnr_feature_state.feature_buffers[VNR_PATCH_WIDTH - 1];

        // printf("%ld\n", features[10]);

        chan_out_buf_word(c_samp, (uint32_t*)features, VNR_MEL_FILTERS);
    }
}


void main_tile1(chanend_t c0, chanend_t c1, chanend_t c2, chanend_t c3){
    printf("Hellord 1\n");
 
    channel_t c_ma = chan_alloc();

    app_pll_init();

    PAR_JOBS (
        PJOB(mic_array_task, (c_ma.end_a)),
        PJOB(ma_servicer, (c_ma.end_b, c0))
        );
    printf("Exit 1\n");

 }