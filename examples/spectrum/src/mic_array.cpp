// Copyright 2022-2023 XMOS LIMITED.
// This Software is subject to the terms of the XCORE VocalFusion Licence.

#include <stdint.h>
#include <xcore/channel_streaming.h>
#include <xcore/interrupt.h>

#include "mic_array/cpp/Prefab.hpp"
#include "mic_array/cpp/MicArray.hpp"
#include "mic_array.h"
#include "mic_array/etc/filters_default.h"
#include "mic_array_task.h"

#include "app_conf.h"


////// Check that all the required config macros have been defined. 

#ifndef MIC_ARRAY_CONFIG_MCLK_FREQ
# error Application must specify the master clock frequency by defining MIC_ARRAY_CONFIG_MCLK_FREQ.
#endif

#ifndef MIC_ARRAY_CONFIG_PDM_FREQ
# error Application must specify the PDM clock frequency by defining MIC_ARRAY_CONFIG_PDM_FREQ.
#endif

////// Provide default values for optional config macros

# if ((MIC_ARRAY_CONFIG_SAMPLES_PER_FRAME) < 1)
#  error MIC_ARRAY_CONFIG_SAMPLES_PER_FRAME must be positive.
# endif

////// Additional macros derived from others

#define MIC_ARRAY_CONFIG_MCLK_DIVIDER     ((MIC_ARRAY_CONFIG_MCLK_FREQ)       \
                                              /(MIC_ARRAY_CONFIG_PDM_FREQ))
#define MIC_ARRAY_CONFIG_OUT_SAMPLE_RATE    ((MIC_ARRAY_CONFIG_PDM_FREQ)      \
                                              /(STAGE2_DEC_FACTOR))

////// Any Additional correctness checks



////// Allocate needed objects

#if (!(MIC_ARRAY_CONFIG_USE_DDR))
pdm_rx_resources_t pdm_res = PDM_RX_RESOURCES_SDR(
                                MIC_ARRAY_CONFIG_PORT_MCLK,
                                MIC_ARRAY_CONFIG_PORT_PDM_CLK,
                                MIC_ARRAY_CONFIG_PORT_PDM_DATA,
                                MIC_ARRAY_CONFIG_CLOCK_BLOCK_A);
#else
pdm_rx_resources_t pdm_res = PDM_RX_RESOURCES_DDR(
                                MIC_ARRAY_CONFIG_PORT_MCLK,
                                MIC_ARRAY_CONFIG_PORT_PDM_CLK,
                                MIC_ARRAY_CONFIG_PORT_PDM_DATA,
                                MIC_ARRAY_CONFIG_CLOCK_BLOCK_A,
                                MIC_ARRAY_CONFIG_CLOCK_BLOCK_B);
#endif


#if (appconfPIPELINE_AUDIO_SAMPLE_RATE == 32000)

// Designed from https://github.com/xmos/lib_mic_array/tree/develop/script/filter_design
// python3 design_filter.py
// python3 ../stage1.py good_32k_filter_int.pkl 
// python3 ../stage2.py good_32k_filter_int.pkl 

#define MIC_ARRAY_32K_STAGE_1_TAP_COUNT 148
#define MIC_ARRAY_32K_STAGE_1_FILTER_WORD_COUNT 128
static const uint32_t WORD_ALIGNED stage1_32k_coefs[MIC_ARRAY_32K_STAGE_1_FILTER_WORD_COUNT]
{
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFF2DBBA, 0x1E443FC2, 0x2788F9F1, 0x1E443FC2, 0x2785DDB4, 
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFF86BEB, 0x1C91CEC9, 0x8DC6F6F6, 0x3B193738, 0x938D7D61, 
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFDBC29, 0x211BF8E9, 0x323BF6FD, 0xC4C971FD, 0x884943DB, 
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFE89A2, 0x721D515E, 0x02D0A650, 0xB407A8AB, 0x84E45917, 
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF26BF, 0x614B35F7, 0xE678C631, 0xE67EFACD, 0x286FD64F, 
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFCA48, 0x0C0BC045, 0x42E8F9F1, 0x742A203D, 0x0301253F, 
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFF358, 0x5EE51139, 0x80C16668, 0x3019C88A, 0x77A1ACFF, 
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFC6D, 0x3F5E4E54, 0xAB2F696F, 0x4D52A727, 0xAFCB63FF, 
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFF8E, 0x553F9533, 0x994F30CF, 0x299CCA9F, 0xCAA71FFF, 
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFF0, 0x66554CF0, 0x78DA4025, 0xB1E0F32A, 0xA660FFFF, 
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x879996A5, 0x5293801C, 0x94AA5699, 0x9E1FFFFF, 
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF81E18C6, 0x631C0003, 0x8C663187, 0x81FFFFFF, 
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFE01F07, 0x83E00000, 0x7C1E0F80, 0x7FFFFFFF, 
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFE007, 0xFC000000, 0x03FE007F, 0xFFFFFFFF, 
  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFF8, 0x00000000, 0x0001FFFF, 0xFFFFFFFF, 
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
};

#define MIC_ARRAY_32K_STAGE_2_TAP_COUNT 96
static constexpr right_shift_t stage2_32k_shift = 3;

static const int32_t WORD_ALIGNED stage2_32k_coefs[MIC_ARRAY_32K_STAGE_2_TAP_COUNT] = {
    0x48e57, 0xb911, -0x9100f, -0x102365, -0x85d06, 0xfaf77, 0x259e6e, 0x1df9e6, -0xfb569,
    -0x449a1c, -0x49f7b9, -0x34541, 0x665938, 0x929af0, 0x3a71ad, -0x7ae7c5, -0xf74e13,
    -0xa8bff5, 0x67bd75, 0x16b4c5c, 0x15d5aff, -0x8f1a6, -0x1d0fe39, -0x25c57fc, -0xca944c,
    0x1f7447a, 0x396ea71, 0x23a9ef6, -0x1990463, -0x4e476ba, -0x466f3b6, 0x5d0f5c, 0x5fc9168,
    0x7642af1, 0x2307152, -0x66d87f5, -0xb42d9e1, -0x6bff060, 0x57ba244, 0x1031600e, 0xeca7b53
     -0x189fb39, -0x16f582c1, -0x1f464a53, -0xbd1d299, 0x22e3a091, 0x5a7762f2, 0x7fffffff,
     0x7fffffff, 0x5a7762f2, 0x22e3a091, -0xbd1d299, -0x1f464a53, -0x16f582c1, -0x189fb39,
     0xeca7b53, 0x1031600e, 0x57ba244, -0x6bff060, -0xb42d9e1, -0x66d87f5, 0x2307152, 0x7642af1,
     0x5fc9168, 0x5d0f5c, -0x466f3b6, -0x4e476ba, -0x1990463, 0x23a9ef6, 0x396ea71, 0x1f7447a,
     -0xca944c, -0x25c57fc, -0x1d0fe39, -0x8f1a6, 0x15d5aff, 0x16b4c5c, 0x67bd75, -0xa8bff5,
     -0xf74e13, -0x7ae7c5, 0x3a71ad, 0x929af0, 0x665938, -0x34541, -0x49f7b9, -0x449a1c, -0xfb569,
     0x1df9e6, 0x259e6e, 0xfaf77, -0x85d06, -0x102365, -0x9100f, 0xb911, 0x48e57
};

constexpr int mic_count = MIC_ARRAY_CONFIG_MIC_COUNT;
constexpr int decimation_factor() {
    if(true) // TODO 32kHz
        return 3;
    // 16kHz
    return 6;
}


using TMicArray = mic_array::MicArray<mic_count,
                          mic_array::TwoStageDecimator<mic_count, 
                                                       decimation_factor(), 
                                                       MIC_ARRAY_32K_STAGE_2_TAP_COUNT>,
                          mic_array::StandardPdmRxService<MIC_ARRAY_CONFIG_MIC_IN_COUNT,
                                                          mic_count,
                                                          decimation_factor()>, 
                          // std::conditional uses USE_DCOE to determine which 
                          // sample filter is used.
                          typename std::conditional<MIC_ARRAY_CONFIG_USE_DC_ELIMINATION,
                                              mic_array::DcoeSampleFilter<mic_count>,
                                              mic_array::NopSampleFilter<mic_count>>::type,
                          mic_array::FrameOutputHandler<mic_count, 
                                                        MIC_ARRAY_CONFIG_SAMPLES_PER_FRAME, 
                                                        mic_array::ChannelFrameTransmitter>>;

#else // appconfPIPELINE_AUDIO_SAMPLE_RATE

using TMicArray = mic_array::prefab::BasicMicArray<
                        MIC_ARRAY_CONFIG_MIC_COUNT,
                        MIC_ARRAY_CONFIG_SAMPLES_PER_FRAME,
                        MIC_ARRAY_CONFIG_USE_DC_ELIMINATION,
                        MIC_ARRAY_CONFIG_MIC_IN_COUNT>;

#endif // appconfPIPELINE_AUDIO_SAMPLE_RATE


TMicArray mics;


void ma_init()
{
#if (appconfPIPELINE_AUDIO_SAMPLE_RATE == 32000)
  mics.Decimator.Init(stage1_32k_coefs, stage2_32k_coefs, stage2_32k_shift);
  mics.PdmRx.Init(pdm_res.p_pdm_mics);
#else // appconfPIPELINE_AUDIO_SAMPLE_RATE
  mics.Init();
  mics.SetPort(pdm_res.p_pdm_mics);
#endif // appconfPIPELINE_AUDIO_SAMPLE_RATE

  // unsigned channel_map[MIC_ARRAY_CONFIG_MIC_COUNT] = {4, 5, 6, 7};
  // mics.PdmRx.MapChannels(channel_map);
  mic_array_resources_configure(&pdm_res, MIC_ARRAY_CONFIG_MCLK_DIVIDER);
  mic_array_pdm_clock_start(&pdm_res);
}


void ma_task(
    chanend_t c_frames_out)
{
#if (appconfPIPELINE_AUDIO_SAMPLE_RATE == 32000)
  mics.OutputHandler.FrameTx.SetChannel(c_frames_out);

  mics.PdmRx.InstallISR();
  mics.PdmRx.UnmaskISR();
#else // appconfPIPELINE_AUDIO_SAMPLE_RATE
  mics.SetOutputChannel(c_frames_out);

  mics.InstallPdmRxISR();
  mics.UnmaskPdmRxISR();

#endif // appconfPIPELINE_AUDIO_SAMPLE_RATE

  mics.ThreadEntry();
}