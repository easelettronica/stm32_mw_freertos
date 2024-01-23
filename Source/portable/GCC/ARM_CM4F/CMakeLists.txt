include_guard(GLOBAL)
message("FreeRTOS porting CM4F component is included.")

file(GLOB FREERTOS_PORT_SOURCE_FILES 
    "${CMAKE_CURRENT_LIST_DIR}/port.c"
)

target_sources(${PROJECT_NAME} PRIVATE
	${FREERTOS_PORT_SOURCE_FILES}
)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/.
)

