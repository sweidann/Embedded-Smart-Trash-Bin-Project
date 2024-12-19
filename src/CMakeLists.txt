add_executable(mokh4
    main.c
ir_sensor.c
ir_sensor.h
Flame_Sensor.h
Flame_Sensor.c
Servo_Motor.h
Servo_Motor.c
Buzzer.h
Buzzer.c
ultra_sonic_sensor.c
${CMAKE_CURRENT_SOURCE_DIR}/../lib/FreeRTOS-Kernel/portable/MemMang/heap_4.c
)

target_include_directories(mokh4 PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/FreeRTOS-Kernel/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040
)

target_link_libraries(${ProjectName} 
    pico_stdlib 
    hardware_adc
    hardware_pwm
    FreeRTOS-Kernel-Heap4 
    )
pico_enable_stdio_usb(mokh4 1)
pico_enable_stdio_uart(mokh4 1)

pico_add_extra_outputs(mokh4)