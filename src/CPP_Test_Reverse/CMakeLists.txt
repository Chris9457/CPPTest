set(APP_NAME CPP_Test_Reverse)

set(SRC_DIR src)
file(GLOB SRC_FILES ${SRC_DIR}/*)

add_executable(${APP_NAME} ${SRC_FILES})

target_link_libraries(${APP_NAME} PRIVATE ReverseLib)
