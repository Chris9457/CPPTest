set(LIB_NAME ReverseLib)

set(INCLUDE_DIR include)
set(SRC_DIR src)
file(GLOB INCLUDE_FILES ${INCLUDE_DIR}/*)
file(GLOB SRC_FILES ${SRC_DIR}/*)

add_library(${LIB_NAME} ${INCLUDE_FILES} ${SRC_FILES})

target_include_directories(${LIB_NAME} PUBLIC ${INCLUDE_DIR})
