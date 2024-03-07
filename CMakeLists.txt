include_guard(GLOBAL)
message("FreeRTOS component is included.")

set(FREERTOS_SOURCE_FILES_LIST 
    "${CMAKE_CURRENT_LIST_DIR}/Source/croutine.c"
    "${CMAKE_CURRENT_LIST_DIR}/Source/event_groups.c"
    "${CMAKE_CURRENT_LIST_DIR}/Source/list.c"
    "${CMAKE_CURRENT_LIST_DIR}/Source/queue.c"
    "${CMAKE_CURRENT_LIST_DIR}/Source/stream_buffer.c"
    "${CMAKE_CURRENT_LIST_DIR}/Source/tasks.c"
    "${CMAKE_CURRENT_LIST_DIR}/Source/timers.c"
)

if(FREERTOS_HEAP_4 AND FREERTOS_HEAP_5)
    message(FATAL_ERROR "It's not possibile to enable multiple Heap! (FreeRTOS)")
endif()

if(FREERTOS_HEAP_4)
    message("FreeRTOS Heap 4 component is included.")
    file(GLOB FREERTOS_SOURCE_FILES 
        ${FREERTOS_SOURCE_FILES_LIST}
        "${CMAKE_CURRENT_LIST_DIR}/Source/portable/MemMang/heap_4.c"
    )
elseif(FREERTOS_HEAP_5)
message("FreeRTOS Heap 5 component is included.")
file(GLOB FREERTOS_SOURCE_FILES 
    ${FREERTOS_SOURCE_FILES_LIST}
    "${CMAKE_CURRENT_LIST_DIR}/Source/portable/MemMang/heap_5.c"
)
else()
    file(GLOB FREERTOS_SOURCE_FILES 
        ${FREERTOS_SOURCE_FILES_LIST}
    )
    message("FreeRTOS Heap management component not included.")
endif()


# Register core library
add_library(freertos INTERFACE)
target_sources(freertos PUBLIC ${FREERTOS_SOURCE_FILES})
target_include_directories(freertos INTERFACE ${CMAKE_CURRENT_LIST_DIR}/Source/include)

if(FREERTOS_PORT_ARM_CM4F)
    target_sources(freertos PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Source/portable/GCC/ARM_CM4F/port.c)
    target_include_directories(freertos INTERFACE ${CMAKE_CURRENT_LIST_DIR}/Source/portable/GCC/ARM_CM4F)
    message("FreeRTOS porting component for ARM CM4F included.")
elseif(FREERTOS_PORT_ARM_CM7)
    target_sources(freertos PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Source/portable/GCC/ARM_CM7/r0p1/port.c)
    target_include_directories(freertos INTERFACE ${CMAKE_CURRENT_LIST_DIR}/Source/portable/GCC/ARM_CM7/r0p1)
    message("FreeRTOS porting component for ARM CM7 included.")
else()
    message(FATAL_ERROR "It's not possibile don't add any portable! (FreeRTOS)")
endif()
