set(TEST_NAME CPP_Test_Reverse_UnitTest)

set(SRC_DIR src)
file(GLOB SRC_FILES ${SRC_DIR}/*)

add_executable(${TEST_NAME} ${SRC_FILES})

target_link_libraries(${TEST_NAME} PRIVATE 
						ReverseLib
						GTest::gtest
						)

add_test(NAME ${TEST_NAME}
		 COMMAND $<TARGET_FILE:${TEST_NAME}> --gtest_output=xml:${TEST_NAME}.xml
		 WORKING_DIRECTORY $<TARGET_FILE_DIR:${TEST_NAME}>
		 )