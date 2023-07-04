#include <stdio.h>
#include <stdlib.h>
#include <xcore/parallel.h>
#include "platform_init.h"
#include "mic_array.h"
#include "mic_array_vanilla.h"
#include "hub75.h"
#include "vnr_features_api.h"

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
        int32_t features[VNR_MEL_FILTERS];
        chan_in_buf_word(c_samp, (uint32_t*)features, VNR_MEL_FILTERS);

        clear_screen();

        int32_t samp = features[10];

        unsigned val = abs(samp) >> 13;
        int y = HUB75_COLUMN_HEIGHT - val - 1;
        if(y < 0){
            y = 0;
        }

        horiz_line(0, y, 5);
        printf("ft rx: %ld , y: %u\n", samp, y);
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

        printf("%ld\n", features[10]);

        chan_out_buf_word(c_samp, (uint32_t*)features, VNR_MEL_FILTERS);
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