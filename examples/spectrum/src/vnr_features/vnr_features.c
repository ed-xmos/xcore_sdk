// Copyright 2021 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "vnr_features_api.h"
#include "vnr_features_priv.h"

#include "hanning_1024.h"


// Using scalar unit but works and is way fast enough
void apply_window(int32_t audio[VNR_PROC_FRAME_LENGTH], const int32_t window[VNR_PROC_FRAME_LENGTH/2]){
#if ((VNR_PROC_FRAME_LENGTH / 2) % 8)
#error Only window size multiples of 8 allowed
#endif

  int32_t vl = VNR_PROC_FRAME_LENGTH / 2;
  int32_t ah, x1, x0, y1, y0; uint32_t al;
  int32_t *input_vector_X = audio;
  int32_t *input_vector_Y;
  input_vector_Y = (int32_t *)window;
  const uint32_t q_format = 31;

  //First half is an element-wise mul
  while( vl >= 8 ) {
    asm("ldd %0,%1,%2[0]":"=r"(x1),"=r"(x0):"r"(input_vector_X));
    asm("ldd %0,%1,%2[0]":"=r"(y1),"=r"(y0):"r"(input_vector_Y));
    asm("maccs %0,%1,%2,%3":"=r"(ah),"=r"(al):"r"(x0),"r"(y0),"0"(0),"1"(0));
    asm("lextract %0,%1,%2,%3,32": "=r"(x0):"r"(ah),"r"(al),"r"(q_format));
    asm("maccs %0,%1,%2,%3":"=r"(ah),"=r"(al):"r"(x1),"r"(y1),"0"(0),"1"(0));
    asm("lextract %0,%1,%2,%3,32": "=r"(x1):"r"(ah),"r"(al),"r"(q_format));
    asm("std %0,%1,%2[0]"::"r"(x1), "r"(x0),"r"(input_vector_X));

    asm("ldd %0,%1,%2[1]":"=r"(x1),"=r"(x0):"r"(input_vector_X));
    asm("ldd %0,%1,%2[1]":"=r"(y1),"=r"(y0):"r"(input_vector_Y));
    asm("maccs %0,%1,%2,%3":"=r"(ah),"=r"(al):"r"(x0),"r"(y0),"0"(0),"1"(0));
    asm("lextract %0,%1,%2,%3,32": "=r"(x0):"r"(ah),"r"(al),"r"(q_format));
    asm("maccs %0,%1,%2,%3":"=r"(ah),"=r"(al):"r"(x1),"r"(y1),"0"(0),"1"(0));
    asm("lextract %0,%1,%2,%3,32":"=r"(x1):"r"(ah),"r"(al),"r"(q_format));
    asm("std %0,%1,%2[1]"::"r"(x1), "r"(x0),"r"(input_vector_X));

    asm("ldd %0,%1,%2[2]":"=r"(x1),"=r"(x0):"r"(input_vector_X));
    asm("ldd %0,%1,%2[2]":"=r"(y1),"=r"(y0):"r"(input_vector_Y));
    asm("maccs %0,%1,%2,%3":"=r"(ah),"=r"(al):"r"(x0),"r"(y0),"0"(0),"1"(0));
    asm("lextract %0,%1,%2,%3,32": "=r"(x0):"r"(ah),"r"(al),"r"(q_format));
    asm("maccs %0,%1,%2,%3":"=r"(ah),"=r"(al):"r"(x1),"r"(y1),"0"(0),"1"(0));
    asm("lextract %0,%1,%2,%3,32": "=r"(x1):"r"(ah),"r"(al),"r"(q_format));
    asm("std %0,%1,%2[2]"::"r"(x1), "r"(x0),"r"(input_vector_X));

    asm("ldd %0,%1,%2[3]":"=r"(x1),"=r"(x0):"r"(input_vector_X));
    asm("ldd %0,%1,%2[3]":"=r"(y1),"=r"(y0):"r"(input_vector_Y));
    asm("maccs %0,%1,%2,%3":"=r"(ah),"=r"(al):"r"(x0),"r"(y0),"0"(0),"1"(0));
    asm("lextract %0,%1,%2,%3,32": "=r"(x0):"r"(ah),"r"(al),"r"(q_format));
    asm("maccs %0,%1,%2,%3":"=r"(ah),"=r"(al):"r"(x1),"r"(y1),"0"(0),"1"(0));
    asm("lextract %0,%1,%2,%3,32": "=r"(x1):"r"(ah),"r"(al),"r"(q_format));
    asm("std %0,%1,%2[3]"::"r"(x1), "r"(x0),"r"(input_vector_X));
     
    vl -= 8;
    input_vector_X += 8; input_vector_Y += 8;
   }

   //second half is an element-wise mul but with window reversed
   vl = VNR_PROC_FRAME_LENGTH / 2;
   input_vector_Y -= 8;
   while( vl >= 8 ) {
      asm("ldd %0,%1,%2[0]":"=r"(x1),"=r"(x0):"r"(input_vector_X));
      asm("ldd %0,%1,%2[3]":"=r"(y0),"=r"(y1):"r"(input_vector_Y));
      asm("maccs %0,%1,%2,%3":"=r"(ah),"=r"(al):"r"(x0),"r"(y0),"0"(0),"1"(0));
      asm("lextract %0,%1,%2,%3,32": "=r"(x0):"r"(ah),"r"(al),"r"(q_format));
      asm("maccs %0,%1,%2,%3":"=r"(ah),"=r"(al):"r"(x1),"r"(y1),"0"(0),"1"(0));
      asm("lextract %0,%1,%2,%3,32": "=r"(x1):"r"(ah),"r"(al),"r"(q_format));
      asm("std %0,%1,%2[0]"::"r"(x1), "r"(x0),"r"(input_vector_X));

      asm("ldd %0,%1,%2[1]":"=r"(x1),"=r"(x0):"r"(input_vector_X));
      asm("ldd %0,%1,%2[2]":"=r"(y0),"=r"(y1):"r"(input_vector_Y));
      asm("maccs %0,%1,%2,%3":"=r"(ah),"=r"(al):"r"(x0),"r"(y0),"0"(0),"1"(0));
      asm("lextract %0,%1,%2,%3,32": "=r"(x0):"r"(ah),"r"(al),"r"(q_format));
      asm("maccs %0,%1,%2,%3":"=r"(ah),"=r"(al):"r"(x1),"r"(y1),"0"(0),"1"(0));
      asm("lextract %0,%1,%2,%3,32":"=r"(x1):"r"(ah),"r"(al),"r"(q_format));
      asm("std %0,%1,%2[1]"::"r"(x1), "r"(x0),"r"(input_vector_X));
      
      asm("ldd %0,%1,%2[2]":"=r"(x1),"=r"(x0):"r"(input_vector_X));
      asm("ldd %0,%1,%2[1]":"=r"(y0),"=r"(y1):"r"(input_vector_Y));
      asm("maccs %0,%1,%2,%3":"=r"(ah),"=r"(al):"r"(x0),"r"(y0),"0"(0),"1"(0));
      asm("lextract %0,%1,%2,%3,32": "=r"(x0):"r"(ah),"r"(al),"r"(q_format));
      asm("maccs %0,%1,%2,%3":"=r"(ah),"=r"(al):"r"(x1),"r"(y1),"0"(0),"1"(0));
      asm("lextract %0,%1,%2,%3,32": "=r"(x1):"r"(ah),"r"(al),"r"(q_format));
      asm("std %0,%1,%2[2]"::"r"(x1), "r"(x0),"r"(input_vector_X));
      
      asm("ldd %0,%1,%2[3]":"=r"(x1),"=r"(x0):"r"(input_vector_X));
      asm("ldd %0,%1,%2[0]":"=r"(y0),"=r"(y1):"r"(input_vector_Y));
      asm("maccs %0,%1,%2,%3":"=r"(ah),"=r"(al):"r"(x0),"r"(y0),"0"(0),"1"(0));
      asm("lextract %0,%1,%2,%3,32": "=r"(x0):"r"(ah),"r"(al),"r"(q_format));
      asm("maccs %0,%1,%2,%3":"=r"(ah),"=r"(al):"r"(x1),"r"(y1),"0"(0),"1"(0));
      asm("lextract %0,%1,%2,%3,32": "=r"(x1):"r"(ah),"r"(al),"r"(q_format));
      asm("std %0,%1,%2[3]"::"r"(x1), "r"(x0),"r"(input_vector_X));
      
      vl -= 8;
      input_vector_X += 8; input_vector_Y -= 8;
    }
}


void vnr_input_state_init(vnr_input_state_t *input_state) {
    memset(input_state, 0, sizeof(vnr_input_state_t));
}


void vnr_form_input_frame(vnr_input_state_t *input_state, bfp_complex_s32_t *X, complex_s32_t X_data[VNR_FD_FRAME_LENGTH], const int32_t *new_x_frame) {
    int32_t *x_data = (int32_t*)X_data;
    // Update current frame
    memcpy(x_data, input_state->prev_input_samples, (VNR_PROC_FRAME_LENGTH - VNR_FRAME_ADVANCE)*sizeof(int32_t));
    memcpy(&x_data[VNR_PROC_FRAME_LENGTH - VNR_FRAME_ADVANCE], new_x_frame, VNR_FRAME_ADVANCE*sizeof(int32_t));

    // Update previous samples
    memcpy(input_state->prev_input_samples, &x_data[VNR_FRAME_ADVANCE], (VNR_PROC_FRAME_LENGTH - VNR_FRAME_ADVANCE)*sizeof(int32_t));
    
    apply_window(x_data, window);

    // Calculate forward FFT
    vnr_priv_forward_fft(X, x_data);
}

void vnr_feature_state_init(vnr_feature_state_t *feature_state) {
    memset(feature_state, 0, sizeof(vnr_feature_state_t));
    feature_state->config.enable_highpass = 0;
}

void vnr_extract_features(vnr_feature_state_t *vnr_feature_state,
        bfp_s32_t *feature_patch,
        int32_t feature_patch_data[VNR_PATCH_WIDTH * VNR_MEL_FILTERS],
        const bfp_complex_s32_t *X)
{
    uq8_24 new_slice[VNR_MEL_FILTERS];
    vnr_priv_make_slice(new_slice, X, vnr_feature_state->config.enable_highpass);
    vnr_priv_add_new_slice(vnr_feature_state->feature_buffers, new_slice);
    // Don't need this for the spectrum app
    // vnr_priv_normalise_patch(feature_patch, feature_patch_data, (const vnr_feature_state_t*)vnr_feature_state);
}
