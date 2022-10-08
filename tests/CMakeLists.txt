set(TEST_NAME CPP_Test_Reverse_UnitTest)

set(SRC_DIR src)
set(RESOURCES_DIR resources)
file(GLOB SRC_FILES ${SRC_DIR}/*)
file(GLOB RESOURCES_FILES ${RESOURCES_DIR}/*)

add_executable(${TEST_NAME} ${SRC_FILES} ${RESOURCES_FILES})

target_link_libraries(${TEST_NAME} PRIVATE 
						ReverseLib
						GTest::gtest
						)

target_compile_definitions(${TEST_NAME} PRIVATE
							SAMPLE_FILE="${RESOURCES_DIR}/sample.txt"
							BAD_SAMPLE_FILE="${RESOURCES_DIR}/bad_sample.txt"
							SAMPLE_TABLE_FILE="${RESOURCES_DIR}/sample.table.txt"
							EXPECTED_TABLE_FILE="${RESOURCES_DIR}/expected.table.txt"
							SAMPLE_REVERSE_FILE="${RESOURCES_DIR}/sample.reverse.txt"
							EXPECTED_REVERSE_FILE="${RESOURCES_DIR}/expected.reverse.txt"
						  )

add_custom_command(TARGET ${TEST_NAME} POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_DIR} $<TARGET_FILE_DIR:${TEST_NAME}>
				  )	

add_test(NAME ${TEST_NAME}
		 COMMAND $<TARGET_FILE:${TEST_NAME}> --gtest_output=xml:${TEST_NAME}.xml
		 WORKING_DIRECTORY $<TARGET_FILE_DIR:${TEST_NAME}>
		 )