cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(fire_detection C CXX)

pico_sdk_init()

add_executable(fire_detection
    source/main.cpp
    tflite-model/tflite_learn_1037875_4_compiled.cpp
    edge-impulse-sdk/porting/raspberry/ei_classifier_porting.cpp
)

target_include_directories(fire_detection PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/edge-impulse-sdk
    ${CMAKE_CURRENT_SOURCE_DIR}/model-parameters
    ${CMAKE_CURRENT_SOURCE_DIR}/tflite-model
)

target_link_libraries(fire_detection
    pico_stdlib
    hardware_i2c
    hardware_adc
    hardware_gpio
    hardware_timer
)

pico_add_extra_outputs(fire_detection)
