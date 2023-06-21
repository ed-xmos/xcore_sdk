
## Create custom board targets for dacs
add_library(sw_xvf3800_board_support_xvf3600_evk_dac_dac3101 INTERFACE)
target_sources(sw_xvf3800_board_support_xvf3600_evk_dac_dac3101
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/dac3101/dac3101.c
)
target_include_directories(sw_xvf3800_board_support_xvf3600_evk_dac_dac3101
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/dac3101
)
target_compile_definitions(sw_xvf3800_board_support_xvf3600_evk_dac_dac3101
    INTERFACE
        DAC3101=1
)

## Create an alias
add_library(xcore_iot::example::audio_mux::dac::dac3101 ALIAS sw_xvf3800_board_support_xvf3600_evk_dac_dac3101)
