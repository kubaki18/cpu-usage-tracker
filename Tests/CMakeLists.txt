enable_testing()
add_executable(queue_test queue_test.c)
target_link_libraries(queue_test PRIVATE Queue)
add_test(test_build
  "${CMAKE_COMMAND}"
  --build "${CMAKE_BINARY_DIR}"
  --config "$<CONFIG>"
  --target queue_test 
)
set_tests_properties(test_build PROPERTIES FIXTURES_SETUP    test_fixture)
add_test(queue_float_test queue_test 1)
add_test(queue_cpu_snapshot_test queue_test 2)
set_tests_properties(queue_float_test PROPERTIES FIXTURES_REQUIRED test_fixture)
set_tests_properties(queue_cpu_snapshot_test PROPERTIES FIXTURES_REQUIRED test_fixture)
