// Copyright 2021 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

#ifndef APP_CONF_H_
#define APP_CONF_H_

/* Audio Pipeline Configuration */
#define MIC_ARRAY_CONFIG_MIC_COUNT              2
#define MIC_ARRAY_CONFIG_USE_DC_ELIMINATION     1
#define MIC_ARRAY_CONFIG_SAMPLES_PER_FRAME      512
#define appconfAUDIO_FRAME_LENGTH            	MIC_ARRAY_CONFIG_SAMPLES_PER_FRAME
#define appconfMIC_COUNT                        MIC_ARRAY_CONFIG_MIC_COUNT
#define appconfFRAMES_IN_ALL_CHANS              (appconfAUDIO_FRAME_LENGTH * appconfMIC_COUNT)
#define appconfAUDIO_CLOCK_FREQUENCY            24576000
#define appconfPDM_CLOCK_FREQUENCY              3072000
#define appconfPIPELINE_AUDIO_SAMPLE_RATE       32000
#define MIC_ARRAY_CONFIG_USE_DC_ELIMINATION     1
#define MIC_ARRAY_CONFIG_MIC_IN_COUNT           2
#define MIC_ARRAY_CONFIG_USE_DDR                1
#define MIC_ARRAY_CONFIG_MCLK_FREQ              appconfAUDIO_CLOCK_FREQUENCY
#define MIC_ARRAY_CONFIG_PDM_FREQ               appconfPDM_CLOCK_FREQUENCY

#define SETSR(c)                asm volatile("setsr %0" : : "n"(c));   
#define CLRSR(c)                asm volatile("clrsr %0" : : "n"(c));
#define SET_HIGH_PRIORITY()     SETSR(XS1_SR_QUEUE_MASK)    // Force the xcore to schedule once every 5 processor clocks
#define SET_FAST_MODE()         SETSR(XS1_SR_FAST_MASK)     // Force the xcore to schedule even if blocked on event
#define CLEAR_KEDI()            CLRSR(XS1_SR_KEDI_MASK)

#endif /* APP_CONF_H_ */
