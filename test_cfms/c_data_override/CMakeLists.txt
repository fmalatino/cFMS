cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH PARENT_DIR)
list(APPEND TEST_C_DATA_OVERRIDE_SRC
    test_data_override_2d.c
    test_data_override_3d.c
    test_data_override_scalar.c
)

foreach (testfile ${TEST_C_DATA_OVERRIDE_SRC})
    get_filename_component(testname ${testfile} NAME_WE)
    add_executable(${testname} ${testfile} ${PARENT_DIR}/c_fms/c_mpp_domains_helper.c)
    target_link_libraries(${testname} PUBLIC cFMS::cFMS)
    target_include_directories(${testname} PUBLIC ${PARENT_DIR}/c_fms)
endforeach()