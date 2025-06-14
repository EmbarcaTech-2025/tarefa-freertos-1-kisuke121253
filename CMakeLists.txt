# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
   set(USERHOME $ENV{USERPROFILE})
else()
   set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
   include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.12)

# Name project
SET(ProjectName blink)

# Set any variables required for importing libraries
SET(FREERTOS_PATH ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS)

message("FreeRTOS Kernel located in ${FREERTOS_PATH}")

# Import those libraries
include(pico_sdk_import.cmake)
include(${FREERTOS_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Define project
project(blink C CXX ASM)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(blink
   blink.c
)

target_include_directories(blink PRIVATE
   ${CMAKE_CURRENT_LIST_DIR}
   ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(blink
   pico_stdlib
   hardware_i2c
   FreeRTOS-Kernel-Heap4
   )

pico_add_extra_outputs(blink)