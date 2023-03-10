
## Create custom board targets for application
add_library(sw_xvf3800_board_support_xvf3600_evk INTERFACE)
target_sources(sw_xvf3800_board_support_xvf3600_evk
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/platform/driver_instances.c
        ${CMAKE_CURRENT_LIST_DIR}/platform/app_pll_ctrl.c
        ${CMAKE_CURRENT_LIST_DIR}/platform/platform_init.c
        ${CMAKE_CURRENT_LIST_DIR}/platform/platform_start.c
        ${CMAKE_CURRENT_LIST_DIR}/platform/app_pll_ctrl.c
        ${CMAKE_CURRENT_LIST_DIR}/platform/dac_port.c
)
target_include_directories(sw_xvf3800_board_support_xvf3600_evk
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(sw_xvf3800_board_support_xvf3600_evk
    INTERFACE
        core::general
        rtos::freertos
        rtos::drivers::general
        rtos::drivers::audio
        rtos::drivers::usb
        rtos::freertos_usb
        rtos::sw_services::device_control
)
target_compile_options(sw_xvf3800_board_support_xvf3600_evk
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/xvf3800_qf60.xn
)
target_link_options(sw_xvf3800_board_support_xvf3600_evk
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/xvf3800_qf60.xn
)
target_compile_definitions(sw_xvf3800_board_support_xvf3600_evk
    INTERFACE
        EVK_3600=1
        PLATFORM_SUPPORTS_TILE_0=1
        PLATFORM_SUPPORTS_TILE_1=1
        PLATFORM_SUPPORTS_TILE_2=0
        PLATFORM_SUPPORTS_TILE_3=0
        PLATFORM_USES_TILE_0=1
        PLATFORM_USES_TILE_1=1

        MIC_ARRAY_CONFIG_MCLK_FREQ=24576000
        MIC_ARRAY_CONFIG_PDM_FREQ=3072000
        MIC_ARRAY_CONFIG_SAMPLES_PER_FRAME=240
        MIC_ARRAY_CONFIG_MIC_COUNT=2
        MIC_ARRAY_CONFIG_CLOCK_BLOCK_A=XS1_CLKBLK_1
        MIC_ARRAY_CONFIG_CLOCK_BLOCK_B=XS1_CLKBLK_2
        MIC_ARRAY_CONFIG_PORT_MCLK=PORT_MCLK_IN
        MIC_ARRAY_CONFIG_PORT_PDM_CLK=PORT_PDM_CLK
        MIC_ARRAY_CONFIG_PORT_PDM_DATA=PORT_PDM_DATA
)

## Create an alias
add_library(sw_xvf3800::bsp_config::xvf3600_evk ALIAS sw_xvf3800_board_support_xvf3600_evk)
