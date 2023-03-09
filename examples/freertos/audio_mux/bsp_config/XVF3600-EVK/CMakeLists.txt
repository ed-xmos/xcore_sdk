
## Create custom board targets for application
add_library(sw_xvf3800_board_support_xvf3600_evk INTERFACE)
target_sources(sw_xvf3800_board_support_xvf3600_evk
    INTERFACE
        platform/driver_instances.c
        platform/platform_init.c
        platform/platform_start.c
        platform/app_pll_ctrl.c
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
        XCOREAI_EXPLORER=1
        PLATFORM_SUPPORTS_TILE_0=1
        PLATFORM_SUPPORTS_TILE_1=1
        PLATFORM_SUPPORTS_TILE_2=0
        PLATFORM_SUPPORTS_TILE_3=0
        PLATFORM_USES_TILE_0=1
        PLATFORM_USES_TILE_1=1
)

## Create an alias
add_library(sw_xvf3800::bsp_config::xvf3600_evk ALIAS sw_xvf3800_board_support_xvf3600_evk)
