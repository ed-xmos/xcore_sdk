#**********************
# Gather Sources
#**********************
file(GLOB_RECURSE APP_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.c )
set(APP_INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/src/vnr_features
)

#**********************
# Flags
#**********************
set(APP_COMPILER_FLAGS
    -Os
    -g
    -report
    -fxscope
    -mcmodel=large
    -Wno-xcore-fptrgroup
    ${CMAKE_CURRENT_LIST_DIR}/src/config.xscope
    ${CMAKE_CURRENT_LIST_DIR}/xvf3610_qf60a.xn
)
set(APP_COMPILE_DEFINITIONS
    DEBUG_PRINT_ENABLE=1
    PLATFORM_SUPPORTS_TILE_0=1
    PLATFORM_SUPPORTS_TILE_1=1
    PLATFORM_SUPPORTS_TILE_2=0
    PLATFORM_SUPPORTS_TILE_3=0
    PLATFORM_USES_TILE_0=1
    PLATFORM_USES_TILE_1=1

    MIC_ARRAY_CONFIG_CLOCK_BLOCK_A=XS1_CLKBLK_1
    MIC_ARRAY_CONFIG_CLOCK_BLOCK_B=XS1_CLKBLK_2
    MIC_ARRAY_CONFIG_PORT_MCLK=PORT_MCLK_IN
    MIC_ARRAY_CONFIG_PORT_PDM_CLK=PORT_PDM_CLK
    MIC_ARRAY_CONFIG_PORT_PDM_DATA=PORT_PDM_DATA
    XUD_CORE_CLOCK=600
)

set(APP_LINK_OPTIONS
    -lquadflash
    -report
    ${CMAKE_CURRENT_LIST_DIR}/xvf3610_qf60a.xn
    ${CMAKE_CURRENT_LIST_DIR}/src/config.xscope
)

#**********************
# Tile Targets
#**********************
add_executable(spectrum)
target_sources(spectrum PUBLIC ${APP_SOURCES})
target_include_directories(spectrum PUBLIC ${APP_INCLUDES})
target_compile_definitions(spectrum PRIVATE ${APP_COMPILE_DEFINITIONS})
target_compile_options(spectrum PRIVATE ${APP_COMPILER_FLAGS})
target_link_libraries(spectrum PUBLIC core::general io::all framework_core_multitile_support)
target_link_options(spectrum PRIVATE ${APP_LINK_OPTIONS})

# MCLK_FREQ,  PDM_FREQ, MIC_COUNT,  SAMPLES_PER_FRAME
mic_array_vanilla_add( spectrum
    24576000  3072000   2           512 )

#**********************
# Create run and debug targets
#**********************
create_run_target(spectrum)
create_debug_target(spectrum)
create_flash_app_target(spectrum)
create_install_target(spectrum)
